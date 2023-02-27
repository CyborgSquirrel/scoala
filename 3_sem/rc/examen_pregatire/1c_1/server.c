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
	
	int listen_fd = socket(AF_INET, SOCK_DGRAM, 0);
	bind(
		  listen_fd
		, (struct sockaddr *) &server_addr
		, sizeof(server_addr)
	);
	
	struct sockaddr_in client_addr;
	socklen_t client_addr_len;
	while (1) {
		int32_t n_a;
		recvfrom(
			  listen_fd
			, &n_a
			, sizeof(int32_t)
			, 0
			, (struct sockaddr *) &client_addr
			, &client_addr_len
		);
		int32_t a = ntohl(n_a);
		
		int32_t n_b;
		recvfrom(
			  listen_fd
			, &n_b
			, sizeof(int32_t)
			, 0
			, (struct sockaddr *) &client_addr
			, &client_addr_len
		);
		int32_t b = ntohl(n_b);
		
		int32_t sum = a+b;
		int32_t n_sum = htonl(sum);
		sendto(
			  listen_fd
			, &n_sum
			, sizeof(int32_t)
			, 0
			, (struct sockaddr *) &client_addr
			, client_addr_len
		);
	}
	close(listen_fd);
	
	return 0;
}
