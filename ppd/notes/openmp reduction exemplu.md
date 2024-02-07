```c
// run {"compiler": "omp"}

#include <omp.h> 
#include <stdio.h>

int main () {
  int i, n, chunk; 
  float a[100], b[100], result; 

  // initialization
  n = 100; 
  chunk = 10; 
  result = 0.0; 
  for (i = 0; i < n; i++) { 
    a[i] = i * 1.0;
    b[i] = i * 2.0;
  } 

  // calculation
  #pragma omp parallel for default(shared) private(i) schedule(static,chunk) reduction(+:result) 
  for (i=0; i < n; i++) {
    result = result + (a[i] * b[i]); 
  }

  // result
  printf("result = %f\n", result); 

  return 0;
}

```
