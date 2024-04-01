import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;

class Main {
  // row-major matrix
  private static class Matrix {
    double[] buf;
    int rowNo;
    int colNo;

    public static Matrix readFromFile(String path, int rowNo, int colNo) {
      Matrix matrix = new Matrix();
      matrix.rowNo = rowNo;
      matrix.colNo = colNo;

      int bufSize = rowNo * colNo;
      matrix.buf = new double[bufSize];
    
      try (Scanner s = new Scanner(new File(path))) {
        int i = 0;
        for (int row = 0; row < rowNo; ++row) {
          for (int col = 0; col < colNo; ++col) {
            matrix.buf[i] = s.nextDouble();
            i += 1;
          }
        }
      } catch (FileNotFoundException ex) {
        
      }

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
          int tRow = row + cRow;
          int tCol = col + cCol;
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
    Matrix src;
    Matrix conv;
    Matrix dst;
  
    int start;
    int stop;

    public MyThreadRow(Matrix src, Matrix conv, Matrix dst, int start, int stop) {
      this.src = src;
      this.conv = conv;
      this.dst = dst;
  
      this.start = start;
      this.stop = stop;
    }

    public void run() {
      for (int row = this.start; row < this.stop; ++row) {
        for (int col = 0; col < this.src.colNo; ++col) {
          double value = this.src.convolveAt(this.conv, row, col);
          this.dst.set(row, col, value);
        }
      }
    }
  }

  private static class MyThreadCol extends Thread {
    Matrix src;
    Matrix conv;
    Matrix dst;
  
    int start;
    int stop;

    public MyThreadCol(Matrix src, Matrix conv, Matrix dst, int start, int stop) {
      this.src = src;
      this.conv = conv;
      this.dst = dst;
  
      this.start = start;
      this.stop = stop;
    }

    public void run() {
      for (int col = this.start; col < this.stop; ++col) {
        for (int row = 0; row < this.src.rowNo; ++row) {
          double value = this.src.convolveAt(this.conv, row, col);
          this.dst.set(row, col, value);
        }
      }
    }
  }

  private static class MyThreadLinear extends Thread {
    Matrix src;
    Matrix conv;
    Matrix dst;
  
    int start;
    int stop;

    public MyThreadLinear(Matrix src, Matrix conv, Matrix dst, int start, int stop) {
      this.src = src;
      this.conv = conv;
      this.dst = dst;
  
      this.start = start;
      this.stop = stop;
    }

    public void run() {
      for (int i = this.start; i < this.stop; ++i) {
        int row = i / this.src.colNo;
        int col = i % this.src.colNo;

        double value = this.src.convolveAt(this.conv, row, col);
        this.dst.set(row, col, value);
      }
    }
  }

  public static void main(String[] args) {
    // TODO: cli args

    int p = Integer.valueOf(args[0]);
    // - row
    // - col
    // - block
    String method = args[1];

    int matRowNo = Integer.valueOf(args[2]); // N
    int matColNo = Integer.valueOf(args[3]); // M
    String matPath = args[4];

    int convRowNo = Integer.valueOf(args[5]); // n
    int convColNo = Integer.valueOf(args[6]); // m
    String convPath = args[7];

    Matrix mat = Matrix.readFromFile(matPath, matRowNo, matColNo);
    Matrix conv = Matrix.readFromFile(convPath, convRowNo, convColNo);

    Matrix dst = Matrix.newUnset(matRowNo, matColNo);

    Thread[] threads = new Thread[p];

    if (method.equals("row")) {
      int n = matRowNo;
      int start = 0;
      int stop = 0;
      for (int i = 0; i < p; ++i) {
        int len = n/p;
        if (i < n%p) {
          len += 1;
        }

        stop += len;
        threads[i] = new MyThreadRow(mat, conv, dst, start, stop);
        start += len;
      }
    } else if (method.equals("col")) {
      int n = matColNo;
      int start = 0;
      int stop = 0;
      for (int i = 0; i < p; ++i) {
        int len = n/p;
        if (i < n%p) {
          len += 1;
        }

        stop += len;
        threads[i] = new MyThreadCol(mat, conv, dst, start, stop);
        start += len;
      }
    } else if (method.equals("block")) {
      int n = matRowNo * matColNo;
      int start = 0;
      int stop = 0;
      for (int i = 0; i < p; ++i) {
        int len = n/p;
        if (i < n%p) {
          len += 1;
        }

        stop += len;
        threads[i] = new MyThreadLinear(mat, conv, dst, start, stop);
        start += len;
      }
    } else {
      System.out.println("Invalid method");
      System.exit(1);
    }

    for (int i = 0; i < p; ++i) {
      threads[i].start();
    }

    for (int i = 0; i < p; ++i) {
      try {
        threads[i].join();
      } catch (InterruptedException ex) {
        
      }
    }

    // int size = dst.rowNo * dst.colNo;
    // for (int i = 0; i < size; ++i) {
    //   System.out.print(dst.buf[i]);
    //   System.out.print(" ");
    // }
  }
}
