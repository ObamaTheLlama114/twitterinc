#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>

#include "request.h"
#include "response.h"

#define PORT 8080


struct handler_args {
	int socket;
};


void handler(struct handler_args* args) {
    char* buffer;
    char* hello = "Hello from server";
    ssize_t valread;

	int len = 0;
	ioctl(args->socket, FIONREAD, &len);
	buffer = malloc(len + 1);
	*(buffer + len + 1) = 0;
	if (len > 0) {
		len = read(args->socket, buffer, len);
	}

	// create request for handler func to use
	struct Request request = parse_request(buffer);
	

	// do stuff
	printf("%s\n", buffer);
	send(args->socket, hello, strlen(hello), 0);
	printf("Hello message sent\n");

	// clean up
	close(args->socket);
	free(args);
	free(buffer);
}


int main(int argc, char const* argv[])
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* hello = "Hello from server";
 
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
 
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
 
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
	while(1){
		pthread_t thread;

		if ((new_socket
			 = accept(server_fd, (struct sockaddr*)&address,
					  &addrlen))
			< 0) {
			perror("accept");
			exit(EXIT_FAILURE);
		}

		struct handler_args* args = malloc(sizeof(struct handler_args));
		args->socket = new_socket;

		pthread_create(&thread, NULL, (void* (*)(void*))handler, args);
	}
    // closing the listening socket
    close(server_fd);
    return 0;
}

