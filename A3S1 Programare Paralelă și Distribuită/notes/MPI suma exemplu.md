```c
// run {"compiler": "mpi"}

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

const int NUMBERS_PER_THREAD = 100;

int main(int argc, char **argv) {
	const int boss_rank = 0;

	MPI_Init(&argc, &argv);

	// mpi stuff
	int mpi_rank;
	int mpi_size;
	
	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

	printf("rank: %d\n", mpi_rank);
	printf("size: %d\n", mpi_size);

	// compute the array
	int *boss_array = NULL;
	int boss_array_len = NUMBERS_PER_THREAD * mpi_size;
	if (mpi_rank == boss_rank) {
		boss_array = malloc(sizeof(int) * boss_array_len);
		for (int i = 0; i < boss_array_len; ++i) {
			boss_array[i] = i;
		}
	}

	// worker sum
	int *worker_array = malloc(sizeof(int) * NUMBERS_PER_THREAD);
	MPI_Scatter(
		// send_buf    , send_count        , send_type,
		   boss_array  , NUMBERS_PER_THREAD, MPI_INT  ,
		// recv_buf    , recv_count        , recv_type,
		   worker_array, NUMBERS_PER_THREAD, MPI_INT  ,
		// source      , comm
		   boss_rank   , MPI_COMM_WORLD
	);

	int worker_sum = 0;
	for (int i = 0; i < NUMBERS_PER_THREAD; ++i) {
		worker_sum += worker_array[i];
	}

	free(worker_array);
	if (mpi_rank == boss_rank) {
		free(boss_array);
	}

	// boss sums
	int *boss_sums = NULL;
	if (mpi_rank == boss_rank) {
		boss_sums = malloc(sizeof(int) * mpi_size);
	}
	MPI_Gather(
		// send_buf   , send_count, send_type,
		   &worker_sum, 1         , MPI_INT  ,
		// recv_buf   , recv_count, recv_type,
		   boss_sums  , 1         , MPI_INT  ,
		// source     , comm
		   boss_rank  , MPI_COMM_WORLD
	);

	// boss sum
	if (mpi_rank == boss_rank) {
		int boss_sum = 0;
		for (int i = 0; i < mpi_size; ++i) {
			boss_sum += boss_sums[i];
		}
		free(boss_sums);
	
		printf("%d\n", boss_sum);
	}

	MPI_Finalize();

	return 0;
}
```
