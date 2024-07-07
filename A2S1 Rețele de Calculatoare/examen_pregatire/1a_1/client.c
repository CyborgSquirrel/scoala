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
	
	uint32_t numbers_len;
	printf("numbers_len = ");
	scanf("%d", &numbers_len);
	
	int32_t *numbers = malloc(numbers_len * sizeof(int32_t));
	for (uint32_t i = 0; i < numbers_len; ++i) {
		printf("numbers[%d] = ", i);
		scanf("%d", &numbers[i]);
	}
	
	uint32_t n_numbers_len = htonl(numbers_len);
	for (int i = 0; i < numbers_len; ++i) {
		numbers[i] = htonl(numbers[i]);
	}
	int32_t *n_numbers = numbers;
	
	int client_fd = socket(AF_INET, SOCK_STREAM, 0);
	connect(
		  client_fd
		, (struct sockaddr *) &server_addr
		, sizeof(server_addr)
	);
	
	send(client_fd, &n_numbers_len, sizeof(uint32_t), 0);
	send(client_fd, n_numbers, n_numbers_len * sizeof(uint32_t), 0);
	
	int32_t n_sum;
	recv(client_fd, &n_sum, sizeof(int32_t), 0);
	int32_t sum = ntohl(n_sum);
	
	printf("sum = %d\n", sum);
	
	close(client_fd);
	
	return 0;
}
