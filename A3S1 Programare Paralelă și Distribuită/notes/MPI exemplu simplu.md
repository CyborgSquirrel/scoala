[[message passing interface; MPI]]

```c
// run {"compiler": "mpi"}
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
	int rank;
	int size;
	int name_len;
	char name[MPI_MAX_PROCESSOR_NAME];
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Get_processor_name(name, &name_len);

	printf("name: %s\n", name);
	printf("rank: %d\n", rank);
	printf("size: %d\n", size);

	MPI_Finalize();

	return 0;
}
```
