#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BACKLOG 1
#define BUFFERSIZE 65536

void usage() {
	fprintf(stderr, "server <serverip> <serverport>\n");
}

int main(int argc, char* argv[]) {

	if (argc != 3) {
		usage();
		exit(EXIT_FAILURE);
	}

	char* srv_addr = argv[1];
	char* srv_port = argv[2];
#ifdef DEBUG
	fprintf(stderr, "addr: %s\nport: %s\n", srv_addr, srv_port);
#endif

	struct addrinfo hints;
	struct addrinfo *srv_info, *p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET; 
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (getaddrinfo(srv_addr, srv_port, &hints, &srv_info) == -1) {
		perror("getaddrinfo error");
		exit(EXIT_FAILURE);
	}

	int serv_sock_fd;
	
	for (p = srv_info; p != NULL; p = p->ai_next) {
#ifdef DEBUG
		fprintf(stderr, "%d\n", p->ai_addr->sa_family);
#endif
		serv_sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (serv_sock_fd == -1) {
			continue;
		}
#ifdef DEBUG
		fprintf(stderr, "socket created: %d\n", serv_sock_fd);
#endif

		if (bind(serv_sock_fd, p->ai_addr, p->ai_addrlen) == -1) {
			close(serv_sock_fd);
			continue;
		}

		break;
	}

	if (p == NULL) {
		perror("socket or bind error");
		exit(EXIT_FAILURE);
	}

	//int window_size = 128 * 1024;	/* 128 kilobytes */
	//setsockopt(serv_sock_fd, SOL_SOCKET, SO_SNDBUF, &window_size, sizeof(window_size));
	//setsockopt(serv_sock_fd, SOL_SOCKET, SO_RCVBUF, &window_size, sizeof(window_size));

	if (listen(serv_sock_fd, BACKLOG) == -1) {
		perror("listen error");
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG
	fprintf(stderr, "start listening on %s:%s\n", srv_addr, srv_port);
#endif

	struct sockaddr_storage cli_addr;
	socklen_t addr_size = sizeof(cli_addr);
	int new_sock_fd = accept(serv_sock_fd, (struct sockaddr *)&cli_addr, &addr_size);

	if (new_sock_fd == -1) {
		perror("accept failed");
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG
	fprintf(stderr, "new connection established\n");
#endif
	
	char buffer[BUFFERSIZE];
	int rv;

	while (1) {
//		rv = recv(new_sock_fd, buffer, BUFFERSIZE, 0);
		rv = read(new_sock_fd, buffer, BUFFERSIZE);
		printf("%d\n", rv);
		if (rv <= 0) {
			perror("read error");
			break;
		}
	}

	close(new_sock_fd);
	close(serv_sock_fd);

	freeaddrinfo(srv_info);

	return 0;
}
