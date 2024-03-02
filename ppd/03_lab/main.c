#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * MPI_Gatherv and MPI_Scatterv
 */

int main(int argc, char **argv) {
  const int N = 10;
  int a[N];
  int b[N];
  int c[N];

  MPI_Status status;

  int start = 0;
  int end = 0;
  
  int id;
  int procs_no;
  int name_len;
  char name[MPI_MAX_PROCESSOR_NAME];

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Comm_size(MPI_COMM_WORLD, &procs_no);
  MPI_Get_processor_name(name, &name_len);

  // gather and scatter setup
  int *counts = malloc(procs_no * sizeof(int));
  int *displacements = malloc(procs_no * sizeof(int));

  int q = N / procs_no;
  int r = N % procs_no;

  for (int p = 0; p < procs_no; ++p) {
    end = start + q;
    if (r > 0) {
      end += 1;
      r -= 1;
    }

    displacements[p] = start;
    counts[p] = end-start+1;

    start = end;
  }

  // allocate thy buffers
  int aux_len = counts[id];
  int aux_size = aux_len * sizeof(int);
  int *aux_a = malloc(aux_size);
  int *aux_b = malloc(aux_size);
  int *aux_c = malloc(aux_size);

  // initialize thy vectors
  if (id == 0) {
    for (int i = 0; i < N; ++i) {
      a[i] = rand() % 10;
      b[i] = rand() % 10;
    }
  }

  MPI_Scatterv(a, counts, displacements, MPI_INT, aux_a, aux_len, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatterv(b, counts, displacements, MPI_INT, aux_b, aux_len, MPI_INT, 0, MPI_COMM_WORLD);

  for (int i = 0; i < aux_len; ++i) {
    aux_c[i] = aux_a[i] + aux_b[i];
  }

  MPI_Gatherv(aux_c, aux_len, MPI_INT, c, counts, displacements, MPI_INT, 0, MPI_COMM_WORLD);

  if (id == 0) {
    printf("a = ");
    for (int i = 0; i < N; ++i) {
      printf("%d ", a[i]);
    }
    printf("\n");

    printf("b = ");
    for (int i = 0; i < N; ++i) {
      printf("%d ", b[i]);
    }
    printf("\n");

    printf("c = ");
    for (int i = 0; i < N; ++i) {
      printf("%d ", c[i]);
    }
    printf("\n");
  }

  free(aux_a);
  free(aux_b);
  free(aux_c);

  free(counts);
  free(displacements);
  
  MPI_Finalize();
  return 0;
}

/*
 * MPI_Gather and MPI_Scatter
 */

int main_1(int argc, char **argv) {
  const int N = 10;
  int a[N];
  int b[N];
  int c[N];

  MPI_Status status;

  int start = 0;
  int end = 0;
  
  int id;
  int procs_no;
  int name_len;
  char name[MPI_MAX_PROCESSOR_NAME];

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Comm_size(MPI_COMM_WORLD, &procs_no);
  MPI_Get_processor_name(name, &name_len);

  int aux_len = N / procs_no;
  int aux_size = aux_len * sizeof(int);
  int *aux_a = malloc(aux_size);
  int *aux_b = malloc(aux_size);
  int *aux_c = malloc(aux_size);

  if (id == 0) {
    for (int i = 0; i < N; ++i) {
      a[i] = rand() % 10;
      b[i] = rand() % 10;
    }
  }

  MPI_Scatter(a, aux_len, MPI_INT, aux_a, aux_len, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter(b, aux_len, MPI_INT, aux_b, aux_len, MPI_INT, 0, MPI_COMM_WORLD);

  for (int i = 0; i < aux_len; ++i) {
    aux_c[i] = aux_a[i] + aux_b[i];
  }

  MPI_Gather(aux_c, aux_len, MPI_INT, c, aux_len, MPI_INT, 0, MPI_COMM_WORLD);

  if (id == 0) {
    printf("a = ");
    for (int i = 0; i < N; ++i) {
      printf("%d ", a[i]);
    }
    printf("\n");

    printf("b = ");
    for (int i = 0; i < N; ++i) {
      printf("%d ", b[i]);
    }
    printf("\n");

    printf("c = ");
    for (int i = 0; i < N; ++i) {
      printf("%d ", c[i]);
    }
    printf("\n");
  }

  free(aux_a);
  free(aux_b);
  free(aux_c);
  
  MPI_Finalize();
  return 0;
}

/*
 * MPI_Send and MPI_Recv
 */

int main_0(int argc, char **argv) {
  const int N = 10;
  int a[N];
  int b[N];
  int c[N];

  MPI_Status status;

  int start = 0;
  int end = 0;
  
  int id;
  int procs_no;
  int name_len;
  char name[MPI_MAX_PROCESSOR_NAME];

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Comm_size(MPI_COMM_WORLD, &procs_no);
  MPI_Get_processor_name(name, &name_len);

  if (id == 0) {
    for (int i = 0; i < N; ++i) {
      a[i] = rand() % 10;
      b[i] = rand() % 10;
    }

    int q = N / (procs_no - 1);
    int r = N % (procs_no - 1);

    for (int p = 1; p < procs_no; ++p) {
      end = start + q;
      if (r > 0) {
        end += 1;
        r -= 1;
      }

      MPI_Send(&start, 1, MPI_INT, p, 0, MPI_COMM_WORLD);
      MPI_Send(&end, 1, MPI_INT, p, 0, MPI_COMM_WORLD);

      MPI_Send(a + start, end-start+1, MPI_INT, p, 0, MPI_COMM_WORLD);
      MPI_Send(b + start, end-start+1, MPI_INT, p, 0, MPI_COMM_WORLD);

      start = end;
    }

    for (int p = 1; p < procs_no; ++p) {
      MPI_Recv(&start, 1, MPI_INT, p, 0, MPI_COMM_WORLD, &status);
      MPI_Recv(&end, 1, MPI_INT, p, 0, MPI_COMM_WORLD, &status);
      MPI_Recv(c + start, end-start+1, MPI_INT, p, 0, MPI_COMM_WORLD, &status);
    }

    printf("a = ");
    for (int i = 0; i < N; ++i) {
      printf("%d ", a[i]);
    }
    printf("\n");

    printf("b = ");
    for (int i = 0; i < N; ++i) {
      printf("%d ", b[i]);
    }
    printf("\n");

    printf("c = ");
    for (int i = 0; i < N; ++i) {
      printf("%d ", c[i]);
    }
    printf("\n");

  } else {
    MPI_Recv(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    MPI_Recv(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

    MPI_Recv(a + start, end-start+1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    MPI_Recv(b + start, end-start+1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

    // printf("id: %d\n", id);
    // for (int i = start; i < end; ++i) {
    //   printf("%d ", a[i]);
    // }
    // printf("\n");

    // for (int i = start; i < end; ++i) {
    //   printf("%d ", b[i]);
    // }
    // printf("\n");

    for (int i = start; i < end; ++i) {
      c[i] = a[i] + b[i];
    }
    MPI_Send(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Send(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Send(c + start, end-start+1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    printf("%d: start: %d; end: %d\n", id, start, end);
  }

  // if (id == 0) {
  //   printf("Number of processes: %d\n", procs_no);
  // }
  // printf("%s: Hello from process %d\n", name, id);

  MPI_Finalize();
  return 0;
}
