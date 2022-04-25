#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <poll.h>

int is_pipe_readable(int fd) {
  /*
  struct pollfd {
    int   fd;          file descriptor 
    short events;      requested events 
    short revents;     returned events 
  };
  */
  struct pollfd pfd;
  pfd.fd = fd;
  pfd.events = POLLIN;
  // pointer to an array of pollfd structs, number of actual pollfd structs in the array, timeout in milliseconds
  if(poll(&pfd, 1, 1) < 0) {
    perror("Error on poll");
    return 0; //if fail, then assume false
  }
  if (pfd.revents & POLLERR) {
    return 0; // if POLLERR set, then an error occured while checking the descriptor
  }
  return pfd.revents & POLLIN; //if the revents field has the POLLIN bit set, then the file descriptor is ready to be read
}

int is_pipe_writeable(int fd) {
  /*
  struct pollfd {
    int   fd;          file descriptor
    short events;      requested events
    short revents;     returned events
  };
  */
  struct pollfd pfd;
  pfd.fd = fd;
  pfd.events = POLLOUT;
  // pointer to an array of pollfd structs, number of actual pollfd structs in the array, timeout in milliseconds
  if(poll(&pfd, 1, 1) < 0) {
    perror("Error on poll");
    return 0; //if fail, then assume false
  }
  if (pfd.revents & (POLLERR|POLLNVAL|POLLHUP)) {
    return 0; //for checkout output we have 3 cases of failure, error (like input), hangup and invalid request
  } 
  return pfd.revents & POLLOUT; //if the revents field has the POLLOUT bit set, then the file descriptor is ready to be written to
}

void sigpipe_handler(int sig) {
  printf("Caught a SIGPIPE error, caused by writing into a pipe for which there are no readers\n");
}


int main (int argc, char *argv[]) {
  int p2c[2], c2p[2];
  if(-1 == pipe(p2c)) {
    perror("Error on p2c");
    exit(1);
  }
  if(-1 == pipe(c2p)) {
    perror("Error on c2p");
    exit(1);
  }
  int f = fork();
  if(-1 == f) {
    perror("Error on fork");
    exit(1);
  } else if (0 == f) {
    int i = 0;
    while(1) {
      i++;
      if(i == 2) {
        printf("--- child: closing c2p[0] - reading end\n");
        close(c2p[0]);
      }
      if(i == 4) {
        printf("--- child: adding data to c2p\n");
        write(c2p[1], &i, sizeof(int));
      }
      if(i == 6) {
        printf("--- child: closing c2p[1] - writing end\n");
        close(c2p[1]);
      }
      if(i == 8) {
        printf("--- child: closing p2c[1] - writing end\n");
        close(p2c[1]);
      }
      if(i == 10) {
        printf("--- child: closing p2c[0] - reading end\n");
        close(p2c[0]);
      }
      sleep(1);
    }
    exit(0);
  } else {
    signal(SIGPIPE, sigpipe_handler);
    close(p2c[0]);
    close(c2p[1]);
    int i = 0;
    int a;
    while(1) {
      if(is_pipe_readable(c2p[0])) {
        printf("parent: c2p is readable\n");
      } else {
        printf("parent: c2p is not readable\n");
      }
      if(is_pipe_writeable(p2c[1])) {
        printf("parent: p2c is writeable\n");
      } else {
        printf("parent: p2c is not writeable\n");
      }
      i++;
      if(i == 12) {
        printf("--- parent: closing p2c[1] - writing end\n");
        close(p2c[1]);
      } 
      if(i == 14) {
        printf("--- parent: consuming data to c2p\n");
        read(c2p[0], &a, sizeof(int));
      }
      if(i == 16) {
        printf("--- parent: closing c2p[0] - reading end\n");
        close(c2p[0]);
      }
      sleep(1);
    }
  }

  return 0;
}
