#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
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
  p -= 1;
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

  // printf(
  //   "%d %d %d %s %s %s\n",
  //   p,
  //   mat_row_no,
  //   mat_col_no,
  //   mat_path,
  //   conv_path,
  //   dest_path
  // );

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

  if (id == boss_id) {
    const int rows_per_worker = mat_row_no / p;
    const int rows_leftover = mat_row_no % p;

    // send rows_no to workers
    {
      for (int worker_index = 0; worker_index < p; ++worker_index) {
        const int worker_id = worker_index + 1;

        // compute rows_no
        int rows_no = rows_per_worker;
        if (worker_index < rows_leftover) {
          rows_no += 1;
        }
        rows_no += 2;

        MPI_Send(&rows_no, 1, MPI_INT, worker_id, 0, MPI_COMM_WORLD);
      }
    }

    struct timeval t2_start;
    gettimeofday(&t2_start, NULL);

    // send corresponding rows to workers
    double *row_buf = malloc(sizeof(double) * mat_col_no);
    {
      FILE *f = fopen(mat_path, "r");
      for (int worker_index = 0; worker_index < p; ++worker_index) {
        const int worker_id = worker_index + 1;
        const char is_first_worker = (worker_index == 0);
        const char is_last_worker = (worker_index == p-1);

        // compute rows_no
        int rows_no = rows_per_worker;
        if (worker_index < rows_leftover) {
          rows_no += 1;
        }

        // send middle rows to current worker
        for (int i = 0; i < rows_no; ++i) {
          // read row
          fread(row_buf, sizeof(double), mat_col_no, f);

          // send first row to previous worker
          if (i == 0) {
            if (!is_first_worker) {
              MPI_Send(row_buf, mat_col_no, MPI_DOUBLE, worker_id-1, 0, MPI_COMM_WORLD);
            } else {
              MPI_Send(row_buf, mat_col_no, MPI_DOUBLE, worker_id, 0, MPI_COMM_WORLD);
            }
          }
          MPI_Send(row_buf, mat_col_no, MPI_DOUBLE, worker_id, 0, MPI_COMM_WORLD);
        }

        // send last row to next worker
        if (!is_last_worker) {
          MPI_Send(row_buf, mat_col_no, MPI_DOUBLE, worker_id+1, 0, MPI_COMM_WORLD);
        } else {
          MPI_Send(row_buf, mat_col_no, MPI_DOUBLE, worker_id, 0, MPI_COMM_WORLD);
        }
      }

      fclose(f);
    }

    // receive and write results
    {
      FILE *f = fopen(dest_path, "w");
      for (int worker_index = 0; worker_index < p; ++worker_index) {
        const int worker_id = worker_index+1;

        int rows_recv_no;
        MPI_Recv(&rows_recv_no, 1, MPI_INT, worker_id, 0, MPI_COMM_WORLD, &status);
        for (int row = 0; row < rows_recv_no; ++row) {
          MPI_Recv(row_buf, mat_col_no, MPI_DOUBLE, worker_id, 0, MPI_COMM_WORLD, &status);
          fwrite(row_buf, sizeof(double), mat_col_no, f);
        }
      }
      fclose(f);
    }
    free(row_buf);

    // t2
    struct timeval t2_end;
    gettimeofday(&t2_end, NULL);

    struct timeval t2_elapsed;
    timersub(&t2_end, &t2_start, &t2_elapsed);

    // t1
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

    {
      FILE *f = fopen(t2_path, "w");
      fprintf(f, "%ld.%06ld\n",
        (long int) t2_elapsed.tv_sec,
        (long int) t2_elapsed.tv_usec);
      fclose(f);
    }
  } else {
    int rows_no;
    MPI_Recv(&rows_no, 1, MPI_INT, boss_id, 0, MPI_COMM_WORLD, &status);
    // printf("%d says: %d\n", id, rows_no);

    // Allocate on extra line, so that the result can be written into the same
    // buffer. Yes, this is, indeed, cursed.
    double *buf = malloc(sizeof(double) * (rows_no+1) * mat_col_no);
    double *rows_buf = buf + 1*mat_col_no;
    for (int row = 0; row < rows_no; ++row) {
      MPI_Recv(
        rows_buf + row*mat_col_no, mat_col_no,
        MPI_DOUBLE, boss_id, 0, MPI_COMM_WORLD, &status);
    }

    // for (int row = 0; row < rows_no; ++row) {
    //   printf("%d says: ", id);
    //   for (int col = 0; col < mat_col_no; ++col) {
    //     printf("%f ", rows_buf[row*mat_col_no + col]);
    //   }
    //   printf("\n");
    // }
    // printf("\n");

    for (int calc_row = 1; calc_row < rows_no-1; ++calc_row) {
      double *dest_row = buf + (calc_row-1)*mat_col_no;

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

    int rows_send_no = rows_no-2;
    MPI_Send(&rows_send_no, 1, MPI_INT, boss_id, 0, MPI_COMM_WORLD);
    for (int row = 0; row < rows_send_no; ++row) {
      MPI_Send(buf + row*mat_col_no, mat_col_no, MPI_DOUBLE, boss_id, 0, MPI_COMM_WORLD);
    }
    
    free(buf);
  }

  free(conv_buf);

  MPI_Finalize();
  return 0;
}
