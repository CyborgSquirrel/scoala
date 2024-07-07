#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int main(int argc, char **argv) {
  const int boss_id = 0;
  MPI_Status status;

  int id;
  int p;
  int name_len;
  char name[MPI_MAX_PROCESSOR_NAME];

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Get_processor_name(name, &name_len);

  // cli arguments
  int mat_row_no = atoi(argv[1]);
  int mat_col_no = atoi(argv[2]);
  char *mat_path = argv[3];
  char *conv_path = argv[4];
  char *dest_path = argv[5];
  char *t1_path = argv[6];
  char *t2_path = argv[7];

  int conv_row_no = 3;
  int conv_col_no = 3;
  double *conv_buf = malloc(sizeof(double) * conv_row_no * conv_col_no);

  struct timeval t1_start;
  if (id == boss_id) {
    gettimeofday(&t1_start, NULL);
  }

  // read conv
  if (id == boss_id) {
    FILE *f = fopen(conv_path, "r");
    fread(conv_buf, sizeof(double), conv_row_no*conv_col_no, f);
    fclose(f);
  }
  MPI_Bcast(conv_buf, conv_row_no*conv_col_no, MPI_DOUBLE, boss_id, MPI_COMM_WORLD);

  int rows_no;
  int *rows_nos = NULL;
  {
    if (id == boss_id) {
      const int rows_per_worker_base = mat_row_no / p;
      const int rows_leftover = mat_row_no % p;

      rows_nos = malloc(sizeof(int) * p);
      for (int worker_index = 0; worker_index < p; ++worker_index) {
        // compute rows_no
        int rows_no = rows_per_worker_base;
        if (worker_index < rows_leftover) {
          rows_no += 1;
        }
        rows_no += 2;

        rows_nos[worker_index] = rows_no;
      }
    }

    MPI_Scatter(rows_nos, 1, MPI_INT, &rows_no, 1, MPI_INT, boss_id, MPI_COMM_WORLD);
    // printf("%d says: rows_no %d\n", id, rows_no);
  }

  // """se presupune ca p divide N"""

  int rows_written_per_worker = mat_row_no / p;
  if (rows_written_per_worker % p != 0) {
    rows_written_per_worker += 1;
  }
  
  int rows_per_worker = rows_written_per_worker + 2;

  if (id == boss_id) {
    // printf("rows_per_worker: %d\n", rows_per_worker);
  }

  double *buf = NULL;
  int buf_len = p * rows_per_worker * mat_col_no;
  if (id == boss_id) {
    // buf
    buf = malloc(sizeof(double) * buf_len);
    
    // send corresponding rows to workers
    {
      FILE *f = fopen(mat_path, "r");
      for (int worker_index = 0; worker_index < p; ++worker_index) {
        // printf("worker_index: %d\n", worker_index);
        const char is_first_worker = (worker_index == 0);
        const char is_last_worker = (worker_index == p-1);

        const int worker_first_row = rows_per_worker * worker_index;
        int row = 1;
        // printf("%d\n", worker_index);

        // send middle rows to current worker
        for (int i = 0; i < rows_nos[worker_index]-2; ++i) {
          // read row
          fread(
            buf + (worker_first_row+row) * mat_col_no,
            sizeof(double), mat_col_no,
            f);
          row += 1;

          // send first row to previous worker
          if (i == 0) {
            if (!is_first_worker) {
              memcpy(
                buf + (rows_per_worker*(worker_index-1) + rows_nos[worker_index-1] - 1) * mat_col_no,
                buf + (worker_first_row+row-1) * mat_col_no,
                sizeof(double) * mat_col_no);
            } else {
              memcpy(
                buf + (worker_first_row+row-2) * mat_col_no,
                buf + (worker_first_row+row-1) * mat_col_no,
                sizeof(double) * mat_col_no);
            }
          }
        }

        // send last row to next worker
        if (!is_last_worker) {
          memcpy(
            buf + (rows_per_worker*(worker_index+1)) * mat_col_no,
            buf + (worker_first_row+row-1) * mat_col_no,
            sizeof(double) * mat_col_no);
        } else {
          memcpy(
            buf + (worker_first_row+row) * mat_col_no,
            buf + (worker_first_row+row-1) * mat_col_no,
            sizeof(double) * mat_col_no);
          row += 1;
        }

        // zero out rest
        while (row < rows_per_worker) {
          memset(
            buf + (worker_first_row+row) * mat_col_no,
            0,
            sizeof(double) * mat_col_no
          );
          row += 1;
        }
      }

      fclose(f);
    }

    // printf("buf:\n");
    // for (int row = 0; row < rows_per_worker * p; ++row) {
    //   for (int col = 0; col < mat_col_no; ++col) {
    //     printf("%f ", buf[row*mat_col_no + col]);
    //   }
    //   printf("\n");
    // }
    // printf("\n");
    // printf("\n");
  }

  int work_buf_len = (rows_per_worker+1) * mat_col_no;
  double *work_buf = malloc(sizeof(double) * work_buf_len);

  int rows_buf_len = work_buf_len - mat_col_no;
  double *rows_buf = work_buf + mat_col_no;

  struct timeval t2_start;
  if (id == boss_id) {
    gettimeofday(&t2_start, NULL);
  }

  MPI_Scatter(
    buf     , rows_buf_len, MPI_DOUBLE,
    rows_buf, rows_buf_len, MPI_DOUBLE,
    boss_id, MPI_COMM_WORLD);

  if (id == boss_id) {
    free(buf);
  }

  // for (int row = 0; row < rows_per_worker; ++row) {
  //   printf("%d says: ", id);
  //   for (int col = 0; col < mat_col_no; ++col) {
  //     printf("%f ", rows_buf[row*mat_col_no + col]);
  //   }
  //   printf("\n");
  // }
  // printf("\n");

  // compute convolution
  for (int calc_row = 1; calc_row < rows_no-1; ++calc_row) {
    double *dest_row = work_buf + (calc_row-1)*mat_col_no;

    for (int col = 0; col < mat_col_no; ++col) {
      double result = 0;
      for (int conv_row = 0; conv_row < conv_row_no; ++conv_row) {
        for (int conv_col = 0; conv_col < conv_col_no; ++conv_col) {
          int mat_row = calc_row - 1 + conv_row;

          int mat_col = col - 1 + conv_col;
          if (mat_col < 0) mat_col = 0;
          if (mat_col >= mat_col_no) mat_col = mat_col_no-1;

          result += rows_buf[mat_row*mat_col_no + mat_col] * conv_buf[conv_row*conv_col_no + conv_col];
        }
      }
      dest_row[col] = result;
    }
  }

  if (id == boss_id) {
    struct timeval t2_end;
    gettimeofday(&t2_end, NULL);

    struct timeval t2_elapsed;
    timersub(&t2_end, &t2_start, &t2_elapsed);

    {
      FILE *f = fopen(t2_path, "w");
      fprintf(f, "%ld.%06ld\n",
        (long int) t2_elapsed.tv_sec,
        (long int) t2_elapsed.tv_usec);
      fclose(f);
    }
  }

  free(conv_buf);

  double *dest_buf = NULL;
  if (id == boss_id) {
    dest_buf = malloc(sizeof(double) * p * rows_written_per_worker * mat_col_no);
  }

  MPI_Gather(
    work_buf, rows_written_per_worker*mat_col_no, MPI_DOUBLE,
    dest_buf, rows_written_per_worker*mat_col_no, MPI_DOUBLE,
    boss_id, MPI_COMM_WORLD);
  
  free(work_buf);

  if (id == boss_id) {
    FILE *f = fopen(dest_path, "w");
    for (int worker_index = 0; worker_index < p; ++worker_index) {
      int rows_written_no = rows_nos[worker_index] - 2;
      const int first_row = worker_index*rows_written_per_worker;
      for (int worker_row = 0; worker_row < rows_written_no; ++worker_row) {
        const int row = first_row + worker_row;
        fwrite(dest_buf + row*mat_col_no, sizeof(double), mat_col_no, f);
      }
    }
    fclose(f);

    free(dest_buf);
    free(rows_nos);
  }

  if (id == boss_id) {
    struct timeval t1_end;
    gettimeofday(&t1_end, NULL);

    struct timeval t1_elapsed;
    timersub(&t1_end, &t1_start, &t1_elapsed);

    {
      FILE *f = fopen(t1_path, "w");
      fprintf(f, "%ld.%06ld\n",
        (long int) t1_elapsed.tv_sec,
        (long int) t1_elapsed.tv_usec);
      fclose(f);
    }
  }

  MPI_Finalize();
  return 0;
}
