import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.DoubleBuffer;
import java.util.Scanner;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.CyclicBarrier;

class Main {
  static final int convRowNo = 3;
  static final int convColNo = 3;
  
  // row-major matrix
  private static class Matrix {
    double[] buf;
    int rowNo;
    int colNo;

    public static Matrix readFromFile(String path, int rowNo, int colNo) {
      Matrix matrix = new Matrix();
      matrix.rowNo = rowNo;
      matrix.colNo = colNo;

      ByteBuffer byteBuffer = ByteBuffer.allocate(rowNo * colNo * Double.BYTES);
      byteBuffer.order(ByteOrder.LITTLE_ENDIAN);
      try (DataInputStream f = new DataInputStream(new FileInputStream(path))) {
        f.read(byteBuffer.array(), 0, byteBuffer.capacity());
      } catch (FileNotFoundException ex) {
        
      } catch (IOException ex) {
        
      }

      matrix.buf = new double[rowNo * colNo];
      byteBuffer.asDoubleBuffer().get(matrix.buf);

      return matrix;
    }

    public static Matrix newUnset(int rowNo, int colNo) {
      Matrix matrix = new Matrix();
      matrix.rowNo = rowNo;
      matrix.colNo = colNo;
      matrix.buf = new double[rowNo * colNo];
      return matrix;
    }

    public double convolveAt(Matrix conv, int row, int col) {
      double result = 0;
      for (int cRow = 0; cRow < conv.rowNo; ++cRow) {
        for (int cCol = 0; cCol < conv.colNo; ++cCol) {
          int tRow = row + cRow - conv.rowNo / 2;
          int tCol = col + cCol - conv.colNo / 2;
          result += this.extendPaddedAt(tRow, tCol) * conv.at(cRow, cCol);
        }
      }
      return result;
    }

    public double at(int row, int col) {
      return this.buf[row * this.colNo + col];
    }

    public double extendPaddedAt(int row, int col) {
      if (row < 0) row = 0;
      if (row >= this.rowNo) row = this.rowNo - 1;

      if (col < 0) col = 0;
      if (col >= this.colNo) col = this.colNo - 1;

      return this.at(row, col);
    }

    public double zeroPaddedAt(int row, int col) {
      if (row < 0) return 0;
      if (row >= this.rowNo) return 0;

      if (col < 0) return 0;
      if (col >= this.colNo) return 0;

      return this.at(row, col);
    }

    public void set(int row, int col, double value) {
      this.buf[row * this.colNo + col] = value;
    }

    public boolean isValidPosition(int row, int col) {
      return (
           row >= 0 && row < this.rowNo
        && col >= 0 && col < this.colNo
      );
    }
  }

  private static class MyThreadRow extends Thread {
    CountDownLatch[] canOverwrite;
    
    Matrix mat;
    Matrix conv;
  
    int start;
    int stop;
    int increment;

    public MyThreadRow(
      CountDownLatch[] canOverwrite,
      Matrix mat, Matrix conv,
      int start, int stop, int increment
    ) {
      this.canOverwrite = canOverwrite;
  
      this.mat = mat;
      this.conv = conv;

      this.start = start;
      this.stop = stop;
      this.increment = increment;
    }

    public void run() {
      double[] tmp0 = new double[mat.colNo];
      double[] tmp1 = new double[mat.colNo];
      double[] tmp2 = new double[mat.colNo];

      double[][] tmp = {
        tmp0,
        tmp1,
        tmp2
      };

      boolean haveTmp = false;
      int tmpFromRow  = 0;

      int canOverwriteLen = 0;

      for (int row = start; row < stop; row += increment) {
        final int needFromRow = row-1;

        // we don't need any rows that come before needFromRow, so let them get
        // overwritten
        while (canOverwriteLen < needFromRow-1) {
          canOverwrite[canOverwriteLen].countDown();
          canOverwriteLen += 1;
        }

        // shift buffers in tmp, if it's needed
        int leftToCopy = 3;
        if (haveTmp) {
          final int shift = Math.abs(tmpFromRow - needFromRow);
          if (shift < 3) {
            leftToCopy = shift;

            double[][] newTmp = { null, null, null };
            for (int i = 0; i < 3; ++i) {
              final int srcI = i;
              final int dstI = (i + 3 - shift) % 3;
              newTmp[dstI] = tmp[srcI];
            }

            for (int i = 0; i < 3; ++i) {
              tmp[i] = newTmp[i];
            }
          }
        }

        // copy everything we need
        tmpFromRow = needFromRow;

        final int srcRowOffset = needFromRow + (3 - leftToCopy);
        final int dstRowOffset = 3 - leftToCopy;
        for (int i = 0; i < leftToCopy; ++i) {
          final int dstRow = dstRowOffset + i;
          final int srcRow = srcRowOffset + i;

          for (int copyCol = 0; copyCol < mat.colNo; ++copyCol) {
            tmp[dstRow][copyCol] = mat.extendPaddedAt(srcRow, copyCol);
          }

          // don't need anything up to and including copied row
          while (canOverwriteLen < srcRow) {
            canOverwrite[canOverwriteLen].countDown();
            canOverwriteLen += 1;
          }
        }

        haveTmp = true;

        // wait till we can overwrite the row
        try {
          canOverwrite[row].await();
        } catch (InterruptedException ex) {
          System.out.println("Press f " + ex);
        }

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
        canOverwrite[canOverwriteLen].countDown();
        canOverwriteLen += 1;
      }
    }
  }

  public static void main(String[] args) {
    int p = Integer.valueOf(args[0]);

    int matRowNo = Integer.valueOf(args[1]); // N
    int matColNo = Integer.valueOf(args[2]); // M
    String matPath = args[3];
    
    String convPath = args[4];

    String dstPath = args[5];

    // read matrices
    Matrix mat = Matrix.readFromFile(matPath, matRowNo, matColNo);
    Matrix conv = Matrix.readFromFile(convPath, convRowNo, convColNo);

    long beginMs;
    long endMs;
    if (p == 0) {
      beginMs = System.currentTimeMillis();
      
      double[] tmp0 = new double[mat.colNo];
      double[] tmp1 = new double[mat.colNo];
      double[] tmp2 = new double[mat.colNo];

      double[][] tmp = {
        tmp0,
        tmp1,
        tmp2
      };
      for (int row = 1; row < 3; ++row) {
        for (int col = 0; col < mat.colNo; ++col) {
          tmp[row][col] = mat.extendPaddedAt(row-2, col);
        }
      }

      for (int row = 0; row < mat.rowNo; ++row) {
        double[] lastTmp = tmp[0];
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

      endMs = System.currentTimeMillis();
    } else {
      int n = matRowNo;

      // Even in java you can easily allocate without initializing. Smh C++.
      CountDownLatch[] canOverwrite = new CountDownLatch[n];
      for (int i = 0; i < n; ++i) {
        canOverwrite[i] = new CountDownLatch(p);
      }

      Thread[] threads = new Thread[p];

      beginMs = System.currentTimeMillis();
      for (int i = 0; i < p; ++i) {
        threads[i] = new MyThreadRow(canOverwrite, mat, conv, i, n, p);
        threads[i].start();
      }

      for (int i = 0; i < p; ++i) {
        try {
          threads[i].join();
        } catch (InterruptedException ex) {
      
        }
      }
      endMs = System.currentTimeMillis();
    }

    long elapsedMs = endMs - beginMs;
    double elapsedSecs = ((double) elapsedMs) / 1000;
    System.out.println(elapsedSecs);

    ByteBuffer byteBuffer = ByteBuffer.allocate(mat.rowNo * mat.colNo * Double.BYTES);
    byteBuffer.order(ByteOrder.LITTLE_ENDIAN);
    DoubleBuffer doubleBuffer = byteBuffer.asDoubleBuffer();
    doubleBuffer.put(mat.buf);
    try (DataOutputStream f = new DataOutputStream(new FileOutputStream(dstPath))) {
      f.write(byteBuffer.array());
    } catch (FileNotFoundException ex) {
      
    } catch (IOException ex) {
      
    }
  }
}
