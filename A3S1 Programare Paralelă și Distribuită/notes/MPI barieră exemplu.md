```c
// run {"compiler": "mpi"}
#include <mpi.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	int mpi_rank; MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

	printf("%d: sleeping\n", mpi_rank);
	sleep(mpi_rank);
	printf("%d: waiting at barrier\n", mpi_rank);
	MPI_Barrier(MPI_COMM_WORLD);
	printf("%d: passed barrier\n", mpi_rank);

	MPI_Finalize();

	return 0;
}
```