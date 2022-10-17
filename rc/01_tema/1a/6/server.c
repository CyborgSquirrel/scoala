#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

/*
 * Un client trimite unui server un sir de caractere si un caracter. Serverul
 * va returna clientului toate pozitiile pe care caracterul primit se
 * regaseste in sir.
 */

/*
 * lungime sir de caractere
 * sir de caractere
 * caracterul cautat
 */

int requested_char_positions[1024];

int main() {
	int listening_socket = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(
		  listening_socket
		, SOL_SOCKET
		, SO_REUSEADDR
		, &(int){1}
		, sizeof(int)
	);
	
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(42069);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	int a = bind(
		  listening_socket
		, (struct sockaddr *) &server_addr
		, sizeof(server_addr)
	);
	listen(listening_socket, 5);
	
	struct sockaddr_in other_address;
	int other_address_size = sizeof(other_address);
	while (1) {
		printf("Waiting for client...\n");
		int new_socket = accept(
			  listening_socket
			, (struct sockaddr *) &other_address
			, (socklen_t *) &other_address_size
		);
		
		printf("Client connected.\n");
		
		int str_len;
		recv(new_socket, &str_len, sizeof(int), 0);
		str_len = ntohl(str_len);
		printf("%d\n", str_len);
		
		char *str = malloc(sizeof(char) * str_len);
		recv(new_socket, str, str_len, 0);
		
		char requested_char;
		recv(new_socket, &requested_char, sizeof(char), 0);
		
		int requested_char_positions_len = 0;
		for (int i = 0; i < str_len; ++i) {
			if (str[i] == requested_char) {
				requested_char_positions[requested_char_positions_len] = i;
				requested_char_positions_len++;
			}
		}
		
		printf("Sending response...\n");
		int idk = htonl(requested_char_positions_len);
		send(new_socket, &idk, sizeof(int), 0);
		for (int i = 0; i < requested_char_positions_len; ++i) {
			requested_char_positions[i] = htonl(requested_char_positions[i]);
		}
		send(new_socket, requested_char_positions, sizeof(int) * requested_char_positions_len, 0);
		printf("Sent response.\n");
		
		close(new_socket);
	}
	close(listening_socket);
	return 0;
}
