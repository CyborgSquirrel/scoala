`MPI_Finalize()` nu face să se execute doar un proces.

Rezultatul va fi ceva similar cu:
```
Process 1/3
Process 2/3
Process 0/3
Regards!
Regards!
Regards!
```

```c
// run {"compiler": "mpi", "args": {"processes_no": 3}}

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	int size; MPI_Comm_size(MPI_COMM_WORLD, &size);
	int rank; MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("Process %d/%d\n", rank, size);
	MPI_Finalize();
	printf("Regards!\n");
	return 0;
}
```