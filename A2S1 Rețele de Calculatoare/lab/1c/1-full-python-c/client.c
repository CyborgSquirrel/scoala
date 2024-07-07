#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
	struct sockaddr_in server;
	server.sin_port = htons(4100);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
	
	int32_t n1;
	scanf("%d", &n1);
	int32_t n1_n = htonl(n1);
	sendto(client_socket, &n1_n, sizeof(int32_t), 0, (struct sockaddr *)(&server), sizeof(server));
	
	int32_t n2;
	scanf("%d", &n2);
	int32_t n2_n = htonl(n2);
	sendto(client_socket, &n2_n, sizeof(int32_t), 0, (struct sockaddr *)(&server), sizeof(server));
	
	int32_t sum_n;
	recvfrom(client_socket, &sum_n, sizeof(int32_t), 0, NULL, NULL);
	int32_t sum = ntohl(sum_n);
	
	printf("%d\n", sum);
	
	return 0;
}
