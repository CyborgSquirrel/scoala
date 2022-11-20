#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
	struct sockaddr_in server_addr_0;
	server_addr_0.sin_family = AF_INET;
	server_addr_0.sin_port = htons(4100);
	server_addr_0.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
	
	struct sockaddr_in server_addr;
	socklen_t server_addr_len = sizeof(struct sockaddr_in);
	
	sendto(client_socket, NULL, 0, 0, (struct sockaddr *) &server_addr_0, sizeof(struct sockaddr_in));
	recvfrom(client_socket, NULL, 0, 0, (struct sockaddr *) &server_addr, &server_addr_len);
	
	char string[114];
	printf("Gime string: ");
	scanf("%s", string);
	
	int32_t string_len = strlen(string);
	int32_t string_len_n = htonl(string_len);
	sendto(client_socket, &string_len_n, 4, 0, (struct sockaddr *) &server_addr, server_addr_len);
	
	sendto(client_socket, string, string_len, 0, (struct sockaddr *) &server_addr, server_addr_len);
	
	char character[10];
	printf("Gime character: ");
	scanf("%s", character);
	sendto(client_socket, character, 1, 0, (struct sockaddr *) &server_addr, server_addr_len);
	
	int32_t positions_len_n;
	recvfrom(client_socket, &positions_len_n, 4, 0, NULL, NULL);
	int32_t positions_len = ntohl(positions_len_n);
	
	for (int i = 0; i < positions_len; ++i) {
		int32_t position_n;
		recvfrom(client_socket, &position_n, 4, 0, NULL, NULL);
		int32_t position = ntohl(position_n);
		
		printf("%d\n", position);
	}
	
	return 0;
}
