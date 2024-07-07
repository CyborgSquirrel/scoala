Chiar dacă tipul de date din `MPI_Gather` este `MPI_FLOAT`, pe când șirurile au tipul de date `int`, merge ok.

```c
// run {"compiler": "mpi", "args": {"processes_no": 3}}

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	int nprocs, myrank; 
	int i; int *a, *b; 
	MPI_Status status; 
	MPI_Init(&argc, &argv); 
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs); 
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank); 
 
	a = (int *) malloc( nprocs * sizeof(int)); 
	b = (int *) malloc( nprocs* nprocs * sizeof(int));
	for(int i=0;i<nprocs; i++) a[i]=nprocs*myrank+i; 

	MPI_Gather(a, nprocs, MPI_FLOAT, b, nprocs, MPI_FLOAT, 0 , MPI_COMM_WORLD);

	if (myrank==0)  for(i=0; i<nprocs*nprocs; i++) printf(" %d", b[i]);
	printf("\n");
 
	MPI_Finalize( ); return 0; 
} 
```
