#include <cuda_device_runtime_api.h>
#include <chrono>
#include <cuda_runtime_api.h>
#include <driver_types.h>
#include <fstream>
#include <algorithm>
#include <iostream>

#include <cuda.h>

struct PaddedMat {
  int row_no;
  int col_no;

  double *buf;
  double *padding_buf;

  __device__ PaddedMat() { }

  __device__ PaddedMat(
    int row_no,
    int col_no,
    double *buf,
    double *padding_buf
  )
  : row_no(row_no)
  , col_no(col_no)
  , buf(buf)
  , padding_buf(padding_buf)
  {
    
  }

  __device__ double at_wrapped_copy(int row, int col) {
    if (row < 0)             row = 0;
    if (row >= this->row_no) row = this->row_no-1;
    if (col < 0)             col = 0;
    if (col >= this->col_no) col = this->col_no-1;

    if (row == 0) {
      return this->padding_buf[(0       * this->col_no) + col];
    } else if (row == this->row_no - 1) {
      return this->padding_buf[(1       * this->col_no) + col];
    } else {
      return this->buf[((row-1) * this->col_no) + col];
    }
  }
};

struct Mat {
  int row_no;
  int col_no;

  double *buf;

  __device__ Mat() {}

  __device__ Mat(
    int row_no,
    int col_no,

    double *buf
  )
  : row_no(row_no)
  , col_no(col_no)
  , buf(buf)
  {
    
  }

  __device__ double at_wrapped_copy(int row, int col) {
    if (row < 0)             row = 0;
    if (row >= this->row_no) row = this->row_no-1;
    if (col < 0)             col = 0;
    if (col >= this->col_no) col = this->col_no-1;

    return this->buf[row*this->col_no + col];
  }

  __device__ double at_copy(int row, int col) {
    return this->buf[row*this->col_no + col];
  }

  __device__ double *at(int row, int col) {
    if (row < 0 || row >= this->row_no || col < 0 || col >= this->col_no) {
      return nullptr;
    }

    return &this->buf[row*this->col_no + col];
  }
};

__global__ void cuda_worker(
  int mat_row_no,
  int mat_col_no,
  double *mat_buf,

  int conv_row_no,
  int conv_col_no,
  double *conv_buf,

  double *padding_buf,
  double *inter_buf
) {
  int p = blockDim.x;
  int thread_i = threadIdx.x;

  // intermediate
  inter_buf = inter_buf + thread_i * 2 * mat_col_no;
  Mat inter = Mat(
    2,
    mat_col_no,
    inter_buf
  );

  int inter_curr = 0;
  
  // mat
  int row_quot = mat_row_no / p;
  int row_rem = mat_row_no % p;

  int row_start = row_quot*(thread_i  ) + std::min((thread_i  ), row_rem);
  int row_end   = row_quot*(thread_i+1) + std::min((thread_i+1), row_rem)-1;

  padding_buf = padding_buf + thread_i * 2 * mat_col_no;
  PaddedMat mat_padded = PaddedMat(
    row_end-row_start+1 + 2,
    mat_col_no,
    mat_buf + row_start * mat_col_no,
    padding_buf
  );
  Mat mat = Mat(
    mat_row_no,
    mat_col_no,
    mat_buf
  );

  // conv
  Mat conv = Mat(
    conv_row_no,
    conv_col_no,
    conv_buf
  );

  int row_i = 1;
  for (; row_i < mat_padded.row_no-1; ++row_i) {
    // write past result into mat
    bool can_write = (row_i >= 3);
    if (can_write) {
      for (int col_i = 0; col_i < mat_col_no; ++col_i) {
        *mat.at(row_start+row_i-1-2, col_i) = *inter.at(inter_curr, col_i);
      }
    }

    // compute convolution
    for (int col_i = 0; col_i < mat_padded.col_no; ++col_i) {
      double result = 0;
      for (int conv_row_i = 0; conv_row_i < conv_row_no; ++conv_row_i) {
        for (int conv_col_i = 0; conv_col_i < conv_col_no; ++conv_col_i) {
          result += mat_padded.at_wrapped_copy(row_i-1 + conv_row_i, col_i-1 + conv_col_i) * conv.at_copy(conv_row_i, conv_col_i);
        }
      }

      *inter.at(inter_curr, col_i) = result;
    }
    
    // update intermediate mat row indices
    inter_curr = (inter_curr+1) % 2;
  }

  // write final intermediate stuff
  if (mat_padded.row_no-2 >= 1) {
    for (int col_i = 0; col_i < mat_col_no; ++col_i) {
      *mat.at(row_start+row_i-1-2, col_i) = *inter.at(inter_curr, col_i);
    }
    inter_curr = (inter_curr+1) % 2;
    row_i++;
  }

  if (mat_padded.row_no-2 >= 2) {
    for (int col_i = 0; col_i < mat_col_no; ++col_i) {
      *mat.at(row_start+row_i-1-2, col_i) = *inter.at(inter_curr, col_i);
    }
    inter_curr = (inter_curr+1) % 2;
    row_i++;
  }
}

int main(int argc, char **argv) {
  // cli
  int p = std::stoi(argv[1]);

  int mat_row_no = std::stoi(argv[2]); // N
  int mat_col_no = std::stoi(argv[3]); // M
  char *mat_path = argv[4];

  int conv_row_no = 3;
  int conv_col_no = 3;
  char *conv_path = argv[5];

  char *dst_path = argv[6];

  char *time_path = argv[7];

  // read mat
  int mat_buf_size = sizeof(double) * mat_row_no * mat_col_no;
  double *mat_buf = (double *) malloc(mat_buf_size);
  {
    std::ifstream fin(mat_path, std::ios::binary);
    fin.read(reinterpret_cast<char*>(mat_buf), mat_buf_size);
    fin.close();
  }

  // read conv
  int conv_buf_size = sizeof(double) * conv_row_no * conv_col_no;
  double *conv_buf = (double *) malloc(conv_buf_size);
  {
    std::ifstream fin(conv_path, std::ios::binary);
    fin.read(reinterpret_cast<char*>(conv_buf), conv_buf_size);
    fin.close();
  }

  // padding buf
  int padding_buf_size = sizeof(double) * p * 2 * mat_col_no;
  double *padding_buf = (double *) malloc(padding_buf_size);
  {
    int row_quot = mat_row_no / p;
    int row_rem = mat_row_no % p;

    int start_row = 0;
    for (int i = 0; i < p; ++i) {
      int buf_offset = i * 2 * mat_col_no;
      
      int len = row_quot;
      if (i < row_rem) {
        len++;
      }
      int end_row = start_row + len - 1;

      {
        int start_row_to_copy = std::max(start_row-1, 0);
        for (int j = 0; j < mat_col_no; ++j) {
          padding_buf[buf_offset + j] = mat_buf[start_row_to_copy * mat_col_no + j];
        }

        int end_row_to_copy = std::min(end_row+1, mat_row_no-1);
        for (int j = 0; j < mat_col_no; ++j) {
          padding_buf[buf_offset + mat_col_no + j] = mat_buf[end_row_to_copy * mat_col_no + j];
        }
      }

      start_row = end_row + 1;
    }
  }
  
  // allocate memory on device
  double *dev_mat_buf     = nullptr; cudaMalloc(&dev_mat_buf    , mat_buf_size    );
  double *dev_conv_buf    = nullptr; cudaMalloc(&dev_conv_buf   , conv_buf_size   );
  double *dev_padding_buf = nullptr; cudaMalloc(&dev_padding_buf, padding_buf_size);
  double *dev_inter_buf   = nullptr; cudaMalloc(&dev_inter_buf  , sizeof(double) * p * 2 * mat_col_no);


  // copy everything to device
  cudaMemcpy(dev_mat_buf    , mat_buf    , mat_buf_size    , cudaMemcpyHostToDevice);
  cudaMemcpy(dev_conv_buf   , conv_buf   , conv_buf_size   , cudaMemcpyHostToDevice);
  cudaMemcpy(dev_padding_buf, padding_buf, padding_buf_size, cudaMemcpyHostToDevice);
  
  // free some stuff
  free(conv_buf);
  free(padding_buf);
  
  // start da workas
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  cuda_worker <<< 1, p >>> (
    mat_row_no,
    mat_col_no,
    dev_mat_buf,

    conv_row_no,
    conv_col_no,
    dev_conv_buf,

    dev_padding_buf,
    dev_inter_buf
  );

  cudaDeviceSynchronize();
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  {
    double elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    elapsed /= 1'000'000'000;

    std::ofstream fout(time_path);
    fout << elapsed << "\n";
    fout.close();
  }

  // copy over result
  cudaMemcpy(mat_buf, dev_mat_buf, mat_buf_size, cudaMemcpyDeviceToHost);

  // free cuda stuff
  cudaFree(dev_mat_buf);
  cudaFree(dev_conv_buf);
  cudaFree(dev_padding_buf);
  cudaFree(dev_inter_buf);

  // write result to file
  std::ofstream fout(dst_path, std::ios::binary);
  fout.write(reinterpret_cast<char*>(mat_buf), mat_buf_size);
  fout.close();

  // free mat
  free(mat_buf);
  
  return 0;
}
