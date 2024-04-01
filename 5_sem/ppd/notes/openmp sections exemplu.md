
> [!NOTE]
> Dacă omiți acoladele la `#pragma omp parallel`, atunci programul nu va mai fi determinist. Asta pentru că în locul unde se calculează `t`, acesta este `private`, deci valoarea lui nu este extrasă la final. Și apoi toate thread-urile din `#pragma omp sections` primesc o valoare random neinițializată pentru `t`.


```c
// run {"compiler": "omp"}

#include <omp.h>
#include <stdio.h>

void main() {
	int i, t, N = 12;
	int a[N], b[N], c[N];

	for (i=0; i<N; i++) a[i] = b[i] = 3;

	omp_set_num_threads(3);

	#pragma omp parallel shared(a,b,c) private(i,t) firstprivate(N)
//	{
		#pragma omp single
			t = omp_get_thread_num();
		#pragma omp sections
		{
			#pragma omp section
			{
				printf("0 t = %d\n", t);
				for (i=0; i<N/3; i++) {
					c[i] = a[i] + b[i] + t;
				}
			}

			#pragma omp section
			{
				printf("1 t = %d\n", t);
				for (i=N/3; i<(N/3)*2; i++) {
					c[i] = a[i] + b[i] + t;
				}
			}

			#pragma omp section
			{
				printf("2 t = %d\n", t);
				for (i=(N/3)*2; i<N; i++) {
					c[i] = a[i] + b[i] + t;
				}
			}
		}
	//}

	for (int i = 0; i < N; i++) {
		printf("%d ", c[i]);
	}
	printf("\n");
} 

```