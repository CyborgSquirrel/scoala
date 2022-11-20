#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

char word[256];
char new_word[256];
char status[256];

int main(int argc, char **argv) {
	word[0] = '\0';
	
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4100);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(client_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));
	
	int32_t id_n;
	recv(client_socket, &id_n, 4, 0);
	int32_t id = ntohl(id_n);
	
	printf("Id-ul este %d\n", id);
	
	int running = 1;
	
	while (running) {
		int32_t word_len_n;
		recv(client_socket, &word_len_n, 4, 0);
		int32_t word_len = ntohl(word_len_n);
		
		printf("%d\n", word_len);
		
		if (word_len > 0) {
			recv(client_socket, word, word_len, 0);
			word[word_len+1] = '\0';
		}
		
		char letter;
		recv(client_socket, &letter, 1, 0);
		
		printf("Cuvantul este '%s'\n", word);
		printf("Litera este '%c'\n", letter);
		
		printf("Cuvant: ");
		scanf("%s", new_word);
		int32_t new_word_len = strlen(new_word);
		int32_t new_word_len_n = htonl(new_word_len);
		
		char new_letter[8];
		printf("Litera: ");
		scanf("%s", new_letter);
		
		send(client_socket, &new_word_len_n, 4, 0);
		send(client_socket, new_word, new_word_len, 0);
		send(client_socket, &(new_letter[0]), 1, 0);
		
		int32_t status_len_n;
		recv(client_socket, &status_len_n, 4, 0);
		int32_t status_len = ntohl(status_len_n);
		
		recv(client_socket, status, status_len, 0);
		status[status_len+1] = '\0';
		
		printf("Status: %s\n", status);
		
		int done = 
			   strcmp(status, "mesaj de castig") == 0
			|| strcmp(status, "mesaj de pierdere") == 0
		;
		
		if (done) {
			running = 0;
		}
	}
	
	return 0;
}
