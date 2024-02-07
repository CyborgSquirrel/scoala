Va întoarce ceva similar cu:
```
0: hello
1: hello
2: hello
```

Deci rulează 2+1 main thread-uri.

```c
// run {"compiler": "omp"}

#include <omp.h>
#include <stdio.h>

const int N = 10;

int main() {
	int t;
	omp_set_num_threads(3);

	#pragma omp parallel private(t)
	{
		t = omp_get_thread_num();
		printf("%d: hello\n", t);
	}
	
	return 0;
}

```