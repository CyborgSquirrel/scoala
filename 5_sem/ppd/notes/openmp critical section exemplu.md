```c
// run {"compiler": "omp"}

#include <omp.h>
#include <stdio.h>

int main() {
	int sum = 0;

	#pragma omp parallel for shared(sum)
	for (int i = 0; i < 1000; ++i) {
		#pragma omp critical
		{
			sum += i;
		}
	}

	printf("%d\n", sum);

	return 0;
}
```
