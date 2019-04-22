#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>

#include "http_parser.h"
#include "http_headers_parser.h"

#define PORT 8080
#define BUFFER_SIZE 8192

/** prototypes **/ 
void start_ws_server();


/**
 * Main function.
 * 
 */
int main(int argc, char **argv) {
	start_ws_server();

	return 0;
}


void start_ws_server() {
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[BUFFER_SIZE] = { 0 };
	char *hello = "Hello from server";

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
			sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0) {
		perror("lister");
		exit(EXIT_FAILURE);
	}

	while (1) {
		if ((new_socket = accept(server_fd, (struct sockaddr *) &address,
				(socklen_t*) &addrlen)) < 0) {
			perror("accept");
			exit(EXIT_FAILURE);
		}

//		FILE *file = fdopen(new_socket, "w");
//		fgets(buffer, BUFFER_SIZE, file);

		while ((valread = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
			printf("%s\n", buffer);
			enum http_headers_parsing_state state = parse_request(buffer, BUFFER_SIZE);
			printf("state: %d\n", state);

			close(new_socket);
		}

		return;

		//	send(new_socket, hello, strlen(hello), 0);
//		printf("Hello message sent\n");
	}
}
