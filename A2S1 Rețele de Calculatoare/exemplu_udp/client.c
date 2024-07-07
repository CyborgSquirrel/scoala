#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int c;
  struct sockaddr_in server;
  uint16_t a, b, suma;
  int32_t i, k;
  
  
  c = socket(AF_INET, SOCK_DGRAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  for (i = 0; i < 1000000; i++) {
    k = i + 1;
    k = htonl(k);
    sendto(c, &k, sizeof(k), 0, (struct sockaddr *) &server, sizeof(server));
  }
  
  close(c);
}
