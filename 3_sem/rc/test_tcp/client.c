#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

char message[256];

int main(int argc, char **argv) {
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4100);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(client_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));
	
	printf("Marimea matricii: ");
	int32_t mat_size;
	scanf("%d", &mat_size);
	
	int32_t mat_size_n = htonl(mat_size);
	send(client_socket, &mat_size_n, 4, 0);
	
	int32_t start_message_len_n;
	recv(client_socket, &start_message_len_n, 4, 0);
	int32_t start_message_len = ntohl(start_message_len_n);
	
	recv(client_socket, message, start_message_len, 0);
	message[start_message_len] = '\0';
	
	printf("Mesaj: '%s'\n", message);
	if (strcmp(message, "jocul a inceput") != 0) {
		return 0;
	}
	
	int32_t running = 1;
	while (running) {
		int32_t line;
		printf("Linie: ");
		scanf("%d", &line);
		int32_t line_n = htonl(line);
		send(client_socket, &line_n, 4, 0);
		
		int32_t column;
		printf("Coloana: ");
		scanf("%d", &column);
		int32_t column_n = htonl(column);
		send(client_socket, &column_n, 4, 0);
		
		printf("\n");
		
		recv(client_socket, message, 2, 0);
		message[2] = '\0';
		printf("Ai nimerit? %s!\n", message);
		
		int32_t mistakes_n;
		recv(client_socket, &mistakes_n, 4, 0);
		int32_t mistakes = ntohl(mistakes_n);
		printf("Greseli: %d\n", mistakes);
		
		int32_t planes_left_n;
		recv(client_socket, &planes_left_n, 4, 0);
		int32_t planes_left = ntohl(planes_left_n);
		printf("Avioane ramase: %d\n", planes_left);
		
		printf("\n");
		
		int32_t message_len_n;
		recv(client_socket, &message_len_n, 4, 0);
		int32_t message_len = ntohl(message_len_n);
		
		if (message_len > 0) {
			recv(client_socket, message, message_len, 0);
			message[message_len] = '\0';
			printf("Rezultat joc: %s\n", message);
			
			running = 0;
		}
	}
	
	return 0;
}
