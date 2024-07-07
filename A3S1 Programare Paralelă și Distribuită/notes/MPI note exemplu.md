```c
// run {"compiler": "mpi"}

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);

	float *a;
	int al;

	// date de intrare
	{
		al = 100;
		a = malloc(sizeof(float) * al);
		for (int i = 0; i < al; ++i) {
			a[i] = ((float) i) / (float) 10;
		}
	}

	int mpi_rank; MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
	int mpi_size; MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

	int *cnt, *dp;
	if (mpi_rank == 0) {
		dp = malloc(sizeof(int) * mpi_size);
		cnt = malloc(sizeof(int) * mpi_size);
		for (int i = 0; i < mpi_size; ++i) {
			cnt[i] = al / mpi_size;
			if (i < al % mpi_size) cnt[i] += 1;
			if (i == 0) dp[i] = 0;
			else dp[i] = dp[i-1] + cnt[i-1];
		}
	}

	MPI_Bcast(&al, 1, MPI_INT, 0, MPI_COMM_WORLD);

	int wcnt = al / mpi_size;
	if (mpi_rank < al % mpi_size) wcnt += 1;
	float *wa = malloc(sizeof(float) * wcnt);
	MPI_Scatterv(
		a, cnt, dp, MPI_FLOAT,
		wa, wcnt, MPI_FLOAT,
		0, MPI_COMM_WORLD);

	for (int i = 0; i < wcnt; ++i) {
		float v = wa[i];
		float frac = v - floor(v);
		if (frac > 0.50) v = floor(v) + 1;
		else v = floor(v);
		wa[i] = v;
	}

	MPI_Gatherv(
		wa, wcnt, MPI_FLOAT,
		a, cnt, dp, MPI_FLOAT,
		0, MPI_COMM_WORLD);

	if (mpi_rank == 0) {
		for (int i = 0; i < al; ++i) {
			printf("%f\n", a[i]);
		}
	}

	MPI_Finalize();
	return 0;
}
```