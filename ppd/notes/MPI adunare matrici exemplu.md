```c
// run {"compiler": "mpi"}
#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv) {
	const int boss_rank = 0;
	const int n = 5;
	
	MPI_Init(&argc, &argv);
	int mpi_size; MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
	int mpi_rank; MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

	int *mat0 = NULL;
	int *mat1 = NULL;
	if (mpi_rank == boss_rank) {
		mat0 = malloc(sizeof(int) * n * n);
		mat1 = malloc(sizeof(int) * n * n);
		for (int i = 0; i < n*n; ++i) {
			mat0[i] = i;
			mat1[i] = i+1;
		}
	}

	int *sizes = NULL;
	int *displs = NULL;
	if (mpi_rank == boss_rank) {
		sizes = malloc(sizeof(int) * mpi_size);
		displs = malloc(sizeof(int) * mpi_size);
		for (int i = 0; i < mpi_size; ++i) {
			sizes[i] = (n*n) / mpi_size;
			if (i < (n*n) % mpi_size) {
				sizes[i] += 1;
			}
			
			if (i == 0) {
				displs[i] = 0;
			} else {
				displs[i] = displs[i-1] + sizes[i-1];
			}
		}
	}

	int buf_len = (n*n) / mpi_size;
	if (mpi_rank < (n*n) % mpi_size) {
		buf_len += 1;
	}
	int *buf0 = malloc(sizeof(int) * buf_len);
	int *buf1 = malloc(sizeof(int) * buf_len);

	MPI_Scatterv(
		mat0, sizes, displs, MPI_INT,
		buf0, buf_len, MPI_INT,
		boss_rank, MPI_COMM_WORLD
	);
	MPI_Scatterv(
		mat1, sizes, displs, MPI_INT,
		buf1, buf_len, MPI_INT,
		boss_rank, MPI_COMM_WORLD
	);
	if (mpi_rank == boss_rank) {
		free(mat1);
	}

	for (int i = 0; i < buf_len; ++i) {
		buf0[i] += buf1[i];
	}
	MPI_Gatherv(
		buf0, buf_len, MPI_INT,
		mat0, sizes, displs, MPI_INT,
		boss_rank, MPI_COMM_WORLD
	);

	free(buf0);
	free(buf1);

	if (mpi_rank == boss_rank) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				printf("mat[%d][%d] = %d\n", i, j, mat0[i*n + j]);
			}
		}
		
		free(sizes);
		free(displs);
		
		free(mat0);
	}

	MPI_Finalize();

	return 0;
}
```