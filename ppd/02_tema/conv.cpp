#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cwchar>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <istream>
#include <latch>
#include <ratio>
#include <string>
#include <thread>
#include <vector>

using namespace std;

const int convRowNo = 3;
const int convColNo = 3;

struct Matrix {
  double *buf;
  int rowNo;
  int colNo;

  static Matrix readFromFile(double *buf, char *path, int rowNo, int colNo) {
    Matrix matrix = Matrix {};
    matrix.rowNo = rowNo;
    matrix.colNo = colNo;
    matrix.buf = buf;

    ifstream fin(path, ios::binary);
    fin.read(reinterpret_cast<char*>(matrix.buf), rowNo * colNo * sizeof(double));
    fin.close();
  
    return matrix;
  }

  static Matrix newUnset(double *buf, int rowNo, int colNo) {
    Matrix matrix = Matrix {};
    matrix.rowNo = rowNo;
    matrix.colNo = colNo;
    matrix.buf = buf;
    return matrix;
  }

  double convolveAt(Matrix &conv, int row, int col) {
    double result = 0;
    for (int cRow = 0; cRow < conv.rowNo; ++cRow) {
      for (int cCol = 0; cCol < conv.colNo; ++cCol) {
        int tRow = row + cRow - conv.rowNo / 2;
        int tCol = col + cCol - conv.colNo / 2;
        result += this->extendPaddedAt(tRow, tCol) * conv.at(cRow, cCol);
      }
    }
    return result;
  }

  double at(int row, int col) {
    return this->buf[row * this->colNo + col];
  }

  double extendPaddedAt(int row, int col) {
    if (row < 0) row = 0;
    if (row >= this->rowNo) row = this->rowNo - 1;

    if (col < 0) col = 0;
    if (col >= this->colNo) col = this->colNo - 1;

    return this->at(row, col);
  }

  double zeroPaddedAt(int row, int col) {
    if (row < 0) return 0;
    if (row >= this->rowNo) return 0;

    if (col < 0) return 0;
    if (col >= this->colNo) return 0;

    return this->at(row, col);
  }

  void set(int row, int col, double value) {
    this->buf[row * this->colNo + col] = value;
  }

  bool isValidPosition(int row, int col) {
    return (
         row >= 0 && row < this->rowNo
      && col >= 0 && col < this->colNo
    );
  }
};

void runRow(
  latch *canOverwrite,
  Matrix &mat, Matrix &conv,
  int start, int stop, int increment
) {
  double *tmpBuf = new double[mat.colNo * 3];

  bool haveTmp = false;
  int tmpFromRow  = 0;

  double *tmp[3] = {
    tmpBuf + mat.colNo*0,
    tmpBuf + mat.colNo*1,
    tmpBuf + mat.colNo*2,
  };

  int canOverwriteLen = 0;

  for (int row = start; row < stop; row += increment) {
    const int needFromRow = row-1;

    // we don't need any rows that come before needFromRow, so let them get
    // overwritten
    while (canOverwriteLen < needFromRow-1) {
      canOverwrite[canOverwriteLen].count_down();
      canOverwriteLen += 1;
    }

    // shift buffers in tmp, if it's needed
    int leftToCopy = 3;
    if (haveTmp) {
      const int shift = abs(tmpFromRow - needFromRow);
      if (shift < 3) {
        leftToCopy = shift;

        double *newTmp[3] = { nullptr, nullptr, nullptr };
        for (int i = 0; i < 3; ++i) {
          const int srcI = i;
          const int dstI = (i + 3 - shift) % 3;
          newTmp[dstI] = tmp[srcI];
        }

        for (int i = 0; i < 3; ++i) {
          tmp[i] = newTmp[i];
        }
      }
    }

    // copy everything we need
    tmpFromRow = needFromRow;

    const int srcRowOffset = needFromRow + (3 - leftToCopy);
    const int dstRowOffset = 3 - leftToCopy;
    for (int i = 0; i < leftToCopy; ++i) {
      const int dstRow = dstRowOffset + i;
      const int srcRow = srcRowOffset + i;

      for (int copyCol = 0; copyCol < mat.colNo; ++copyCol) {
        tmp[dstRow][copyCol] = mat.extendPaddedAt(srcRow, copyCol);
      }

      // don't need anything up to and including copied row
      while (canOverwriteLen < srcRow) {
        canOverwrite[canOverwriteLen].count_down();
        canOverwriteLen += 1;
      }
    }

    haveTmp = true;

    // wait till we can overwrite the row
    canOverwrite[row].wait();

    // overwrite the row
    for (int col = 0; col < mat.colNo; ++col) {
      double value = 0;
      for (int convRow = 0; convRow < conv.rowNo; ++convRow) {
        for (int convCol = 0; convCol < conv.colNo; ++convCol) {
          int tmpRow = convRow;
          int tmpCol = col - 1 + convCol;

          if (tmpRow < 0 || tmpRow >= 3) assert(false);

          if (tmpCol < 0) tmpCol = 0;
          if (tmpCol >= mat.colNo) tmpCol = mat.colNo-1;

          value += tmp[tmpRow][tmpCol] * conv.at(convRow, convCol);
        }
      }

      mat.set(row, col, value);
    }
  }

  // don't need anything anymore
  while (canOverwriteLen < mat.rowNo) {
    canOverwrite[canOverwriteLen].count_down();
    canOverwriteLen += 1;
  }

  delete[] tmpBuf;
}

int main(int argc, char **argv) {
  int p = std::stoi(argv[1]);

  int matRowNo = std::stoi(argv[2]); // N
  int matColNo = std::stoi(argv[3]); // M
  char *matPath = argv[4];

  char *convPath = argv[5];

  char *dstPath = argv[6];

  // allocate buffers
  double *matBuf = new double[matRowNo * matColNo];
  double *convBuf = new double[convRowNo * convColNo];

  // set up matrices
  Matrix mat = Matrix::readFromFile(matBuf, matPath, matRowNo, matColNo);
  Matrix conv = Matrix::readFromFile(convBuf, convPath, convRowNo, convColNo);

  chrono::steady_clock::time_point begin;
  chrono::steady_clock::time_point end;
  if (p == 0) {
    begin = chrono::steady_clock::now();

    double *tmpBuf = new double[mat.colNo * 3];

    double *tmp[3] = {
      tmpBuf + mat.colNo*0,
      tmpBuf + mat.colNo*1,
      tmpBuf + mat.colNo*2,
    };
    for (int row = 1; row < 3; ++row) {
      for (int col = 0; col < mat.colNo; ++col) {
        tmp[row][col] = mat.extendPaddedAt(row-2, col);
      }
    }

    for (int row = 0; row < mat.rowNo; ++row) {
      double *lastTmp = tmp[0];
      for (int tmpRow = 0; tmpRow < 3; ++tmpRow) {
        if (tmpRow < 2) {
          tmp[tmpRow] = tmp[tmpRow+1];
        } else {
          tmp[tmpRow] = lastTmp;
          for (int col = 0; col < mat.colNo; ++col) {
            tmp[tmpRow][col] = mat.extendPaddedAt(row+1, col);
          }
        }
      }
     
      for (int col = 0; col < mat.colNo; ++col) {
        double value = 0;
        for (int convRow = 0; convRow < conv.rowNo; ++convRow) {
          for (int convCol = 0; convCol < conv.colNo; ++convCol) {
            int tmpRow = convRow;
            int tmpCol = col - 1 + convCol;

            if (tmpRow < 0 || tmpRow >= 3) assert(false);

            if (tmpCol < 0) tmpCol = 0;
            if (tmpCol >= mat.colNo) tmpCol = mat.colNo-1;

            value += tmp[tmpRow][tmpCol] * conv.at(convRow, convCol);
          }
        }
        mat.set(row, col, value);
      }
    }

    delete[] tmpBuf;

    end = chrono::steady_clock::now();
  } else if (p >= 1) {
    int n = matRowNo;

    // - Why not use std::vector??? Because latch doesn't have a move
    //   constructor.
    // - Why not use new??? Because new allocates and initializes, but latch
    //   doesn't have a default constructor.
    // - Why is life suffering??? Who knows???
    latch *canOverwrite = (latch*) malloc(n * sizeof(latch));
    for (int i = 0; i < n; ++i) {
      // Thank the lord at least they came up with construct_at.
      construct_at(&canOverwrite[i], p);
    }

    thread *threads = new thread[p];

    begin = chrono::steady_clock::now();
    for (int i = 0; i < p; ++i) {
      // NOTE: Why use this ref() thingie here? Because idk. Didn't work
      // otherwise. Here's some kinda explanation https://stackoverflow.com/
      // questions/61985888/why-the-compiler-complains-that-stdthread-arguments-
      // must-be-invocable-after-co.

      threads[i] = thread(
        runRow,
        canOverwrite,
        ref(mat), ref(conv),
        i, n, p
      );
    }

    for (int i = 0; i < p; ++i) {
      threads[i].join();
    }
    end = chrono::steady_clock::now();

    delete[] threads;
    free(canOverwrite);
  } else {
    assert(false);
  }

  // write elapsed time to stdout
  double elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
  elapsed /= 1'000'000'000;
  cout << elapsed << endl;

  // write result to file
  ofstream fout(dstPath, ios::binary);
  fout.write(reinterpret_cast<char*>(mat.buf), mat.rowNo * mat.colNo * sizeof(double));
  fout.close();

  delete[] convBuf;
  delete[] matBuf;
  
  return 0;
}
