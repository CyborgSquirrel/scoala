#include <functional>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <cassert>

using namespace std;

// #define isStatic
// #define isDynamic

const int matBufLimit = 1000 * 1000;
const int convBufLimit = 5 * 5;
const int dstBufLimit = 1000 * 1000;

#ifdef isStatic
  double matBufG[matBufLimit];
  double convBufG[convBufLimit];
  double dstBufG[dstBufLimit];
#endif

struct Matrix {
  double *buf;
  int rowNo;
  int colNo;

  static Matrix readFromFile(double *buf, char *path, int rowNo, int colNo) {
    Matrix matrix = Matrix {};
    matrix.rowNo = rowNo;
    matrix.colNo = colNo;
    matrix.buf = buf;

    {
      ifstream fin(path);
      int i = 0;
      for (int row = 0; row < rowNo; ++row) {
        for (int col = 0; col < colNo; ++col) {
          fin >> matrix.buf[i];
          i += 1;
        }
      }
    }
  
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
        int tRow = row + cRow;
        int tCol = col + cCol;

        double tValue = 0;
        if (this->isValidPosition(tRow, tCol)) {
          tValue = this->at(tRow, tCol);
        }
        result += tValue * conv.at(cRow, cCol);
      }
    }
    return result;
  }

  double at(int row, int col) {
    return this->buf[row * this->colNo + col];
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

void runRow(Matrix &src, Matrix &conv, Matrix &dst, int start, int stop) {
  for (int row = start; row < stop; ++row) {
    for (int col = 0; col < src.colNo; ++col) {
      double value = src.convolveAt(conv, row, col);
      dst.set(row, col, value);
    }
  }
}

void runCol(Matrix &src, Matrix &conv, Matrix &dst, int start, int stop) {
  for (int col = start; col < stop; ++col) {
    for (int row = 0; row < src.rowNo; ++row) {
      double value = src.convolveAt(conv, row, col);
      dst.set(row, col, value);
    }
  }
}

void runBlock(Matrix &src, Matrix &conv, Matrix &dst, int start, int stop) {
  for (int i = start; i < stop; ++i) {
    int row = i / src.colNo;
    int col = i % src.colNo;

    double value = src.convolveAt(conv, row, col);
    dst.set(row, col, value);
  }
}

int main(int argc, char **argv) {
  int p = std::stoi(argv[1]);
  string method = argv[2]; // looks cursed but apparently is fine

  int matRowNo = std::stoi(argv[3]); // N
  int matColNo = std::stoi(argv[4]); // M
  char *matPath = argv[5];

  int convRowNo = std::stoi(argv[6]); // n
  int convColNo = std::stoi(argv[7]); // m
  char *convPath = argv[8];

  #ifdef isStatic
    double *matBuf = matBufG;
    double *convBuf = convBufG;
    double *dstBuf = dstBufG;
  #endif

  #ifdef isDynamic
    double *matBuf = new double[matBufLimit];
    double *convBuf = new double[convBufLimit];
    double *dstBuf = new double[dstBufLimit];
  #endif

  Matrix mat = Matrix::readFromFile(matBuf, matPath, matRowNo, matColNo);
  Matrix conv = Matrix::readFromFile(convBuf, convPath, convRowNo, convColNo);
  Matrix dst = Matrix::newUnset(dstBuf, matRowNo, matColNo);

  void (*f)(Matrix &src, Matrix &conv, Matrix &dst, int start, int stop) = nullptr;
  int n;
  if (method == "row") {
    f = runRow;
    n = matRowNo;
  } else if (method == "col") {
    f = runCol;
    n = matColNo;
  } else if (method == "block") {
    f = runBlock;
    n = matRowNo * matColNo;
  } else {
    assert(false);
  }

  {
    int start = 0;
    int stop = 0;
    thread *threads = new thread[p];

    for (int i = 0; i < p; ++i) {
      int len = n/p;
      if (i < n%p) {
        len += 1;
      }

      // NOTE: Why use this ref() thingie here? Because idk. Didn't work
      // otherwise. Here's some kinda explanation https://stackoverflow.com/
      // questions/61985888/why-the-compiler-complains-that-stdthread-arguments-
      // must-be-invocable-after-co.

      stop += len;
      threads[i] = thread(f, ref(mat), ref(conv), ref(dst), start, stop);
      start += len;
    }

    for (int i = 0; i < p; ++i) {
      threads[i].join();
    }

    delete[] threads;
  }

  // {
  //   int size = matRowNo * matColNo;
  //   for (int i = 0; i < size; ++i) {
  //     cout << dst.buf[i] << " ";
  //   }
  // }
  
  return 0;
}
