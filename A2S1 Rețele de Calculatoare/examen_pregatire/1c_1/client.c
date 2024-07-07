/*
 * Un client trimite unui server doua
 * numere. Serverul va returna clientului suma
 * celor doua numere.
 */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
	struct sockaddr_in server_addr;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4141);
	
	int32_t a;
	printf("a = ");
	scanf("%d", &a);
	
	int32_t b;
	printf("b = ");
	scanf("%d", &b);
	
	int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
	
	int32_t n_a = htonl(a);
	sendto(
		  client_fd
		, &n_a
		, sizeof(int32_t)
		, 0
		, (struct sockaddr *) &server_addr
		, sizeof(server_addr)
	);
	
	int32_t n_b = htonl(b);
	sendto(
		  client_fd
		, &n_b
		, sizeof(int32_t)
		, 0
		, (struct sockaddr *) &server_addr
		, sizeof(server_addr)
	);
	
	int32_t n_sum;
	recvfrom(
		  client_fd
		, &n_sum
		, sizeof(int32_t)
		, 0
		, NULL
		, NULL
	);
	int32_t sum = ntohl(n_sum);
	
	close(client_fd);
	
	printf("sum = %d\n", sum);
	
	return 0;
}
