Rezultatul este `9`.

```c
// run {"compiler": "mpi", "args": {"processes_no": 3}}
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
	int nprocs, myrank;
	int i, value=0;
	int *a, *b;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	if (myrank == 0) {
		a = (int*) malloc(nprocs * sizeof(int));
		for(int i=0;i<nprocs; i++) a[i]=i+1;
	}
	b = (int *) malloc(sizeof(int));
	MPI_Scatter(a, 1, MPI_INT, b, 1, MPI_INT, 0, MPI_COMM_WORLD);
	b[0] += myrank;
	MPI_Reduce(b, &value, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (myrank == 0) {
		printf("value = %d\n", value);
	}
	MPI_Finalize();
	return 0; 
} 
```