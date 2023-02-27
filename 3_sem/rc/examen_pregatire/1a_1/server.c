/*
 * Un client trimite unui server un sir de
 * numere. Serverul va returna clientului suma
 * numerelor primite.
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
	
	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	bind(
		  listen_fd
		, (struct sockaddr *) &server_addr
		, sizeof(server_addr)
	);
	listen(listen_fd, 5);
	
	struct sockaddr_in client_addr;
	socklen_t client_addr_len;
	while (1) {
		int client_fd = accept(
			  listen_fd
			, (struct sockaddr *) &client_addr
			, &client_addr_len
		);
		
		uint32_t n_numbers_len;
		recv(client_fd, &n_numbers_len, sizeof(uint32_t), 0);
		uint32_t numbers_len = ntohl(n_numbers_len);
		
		int32_t *n_numbers = malloc(numbers_len * sizeof(int32_t));
		recv(client_fd, n_numbers, numbers_len * sizeof(int32_t), 0);
		for (int i = 0; i < numbers_len; ++i) {
			n_numbers[i] = ntohl(n_numbers[i]);
		}
		int32_t *numbers = n_numbers;
		
		int32_t sum = 0;
		for (int i = 0; i < numbers_len; ++i) {
			sum += numbers[i];
		}
		int32_t n_sum = htonl(sum);
		
		free(n_numbers);
		
		send(client_fd, &n_sum, sizeof(int32_t), 0);
		close(client_fd);
	}
	close(listen_fd);
	
	return 0;
}
