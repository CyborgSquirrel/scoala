#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(client_socket, (struct sockaddr*)(&addr), sizeof(addr));
	
	char word[256];
	printf("I command you to enter the word: ");
	scanf("%s", word);
	
	uint32_t word_len = strlen(word);
	uint32_t word_len_n = htonl(word_len);
	send(client_socket, &word_len_n, sizeof(uint32_t), 0);
	
	send(client_socket, word, word_len, 0);
	
	for (int i = 0; i < 5; ++i) {
		printf("I command you to guess: ");
		
		uint32_t guess;
		scanf("%d", &guess);
		
		uint32_t guess_n = htonl(guess);
		send(client_socket, &guess_n, sizeof(uint32_t), 0);
		
		int32_t first_response_n;
		recv(client_socket, &first_response_n, sizeof(int32_t), 0);
		int32_t first_response = ntohl(first_response_n);
		if (first_response == -1) {
			printf("The guess was wrong!\n");
			printf("Keep going?: ");
			
			uint8_t keep_going;
			scanf("%hhd", &keep_going);
			send(client_socket, &keep_going, sizeof(keep_going), 0);
			
			if (keep_going == 0) {
				uint32_t attempts_n;
				recv(client_socket, &attempts_n, sizeof(uint32_t), 0);
				uint32_t attempts = ntohl(attempts_n);
				printf("You made only %d attempts\n", attempts);
				
				break;
			}
		} else {
			uint32_t attempts = *((uint32_t*)(&first_response));
			printf("You succeeded! It took you a staggering %d attempts.\n", attempts);
			
			break;
		}
	}
	
	close(client_socket);
	
	return 0;
}
