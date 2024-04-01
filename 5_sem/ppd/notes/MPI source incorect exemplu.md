Programul se blochează la `MPI_Recv`, pentru că parametrul `source` are valoarea `0`, însă mesajul se trimite de la procesul cu rank `1`.

```c
// run {"compiler": "mpi", "args": {"processes_no": 2}}
#include <mpi.h>
#include <stdio.h>
int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	MPI_Status status;
	int mpi_rank; MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

	int value = mpi_rank;
	if (mpi_rank == 0) MPI_Recv(&value, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
	if (mpi_rank == 1) MPI_Send(&value, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
	if (mpi_rank == 0) printf("%d\n", value);

	printf("%d: gata", mpi_rank);

	MPI_Finalize();
	return 0;
}
```