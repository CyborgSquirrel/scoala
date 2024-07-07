#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char ** argv) {
  int a[2], b[2], c[2], i;
  char val = 0, x = 0;
  pipe(a);
  pipe(b);
  pipe(c);
  if (fork() == 0) {
    close(b[0]);
    close(c[1]);
    for (i = 0; i < 3; i++) {
      write(a[1], &val, 1);
      write(b[1], &x, 1);
      read(a[0], &val, 1);
      read(c[0], &x, 1);
    }
    printf("%d\n", val);
    close(a[0]);
    close(a[1]);
    close(b[1]);
    close(c[0]);
    exit(0);
  }
  close(b[1]);
  close(c[0]);
  for (i = 0; i < 3; i++) {
    read(b[0], &x, 1);
    read(a[0], &val, 1);
    val++;
    write(a[1], &val, 1);
    write(c[1], &x, 1);
  }
  close(a[0]);
  close(a[1]);
  close(b[0]);
  close(c[1]);
  printf("%d\n", x);
  wait(NULL);
  return 0;
}
