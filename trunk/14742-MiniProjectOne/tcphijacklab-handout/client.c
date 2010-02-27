#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFERSIZE 1024
#define SLEEPTIME 1

void usage() {
	fprintf(stderr, "client <server ip> <server port> <client port> <file>\n");
}

int main(int argc, char* argv[]) {
	if (argc != 5) {
		usage();
		exit(EXIT_FAILURE);
	}

	char* serv_addr = argv[1];
	char* serv_port = argv[2];
	char* cli_port = argv[3];
	char* file = argv[4];

	struct addrinfo hints;
	struct addrinfo *srv_info, *cli_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	
	if (getaddrinfo(serv_addr, serv_port, &hints, &srv_info) == -1) {
		perror("getaddrinfo failed");
		exit(EXIT_FAILURE);
	}

	hints.ai_family = AF_INET;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, cli_port, &hints, &cli_info) == -1) {
		perror("getaddrinfo failed");
		exit(EXIT_FAILURE);
	}

	int sock_fd;

	sock_fd = socket(srv_info->ai_family, srv_info->ai_socktype, srv_info->ai_protocol);
	if (sock_fd == -1) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	if (bind(sock_fd, cli_info->ai_addr, cli_info->ai_addrlen) == -1) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}


//	setsockopt(sock_fd, SOL_SOCKET, SO_SNDBUF, &window_size, sizeof(window_size));
//	setsockopt(sock_fd, SOL_SOCKET, SO_RCVBUF, &window_size, sizeof(window_size));
	
	if (connect(sock_fd, srv_info->ai_addr, srv_info->ai_addrlen) == -1) {
		perror("connect failed");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(srv_info);
	freeaddrinfo(cli_info);
	
	FILE* filehd = fopen(file, "r");
	if (filehd == NULL) {
		perror("fopen failed");
		exit(EXIT_FAILURE);
	}

#ifdef DEBUG 
	int window_size = 1024 * 128;
	socklen_t opt_size = sizeof(window_size);
	getsockopt(sock_fd, SOL_SOCKET, SO_SNDBUF, &window_size, &opt_size);
	fprintf(stderr, "Peeked Send Window Size: %d\n", window_size);
	getsockopt(sock_fd, SOL_SOCKET, SO_RCVBUF, &window_size, &opt_size);
	fprintf(stderr, "Peeked Recv Window Size: %d\n", window_size);
#endif

	char buffer[BUFFERSIZE];
	int rv;

	while (fgets(buffer, BUFFERSIZE, filehd) != NULL) {
//		rv = send(sock_fd, buffer, strlen(buffer), 0);
		rv = write(sock_fd, buffer, strlen(buffer) + 1);
		printf("%d\n", rv);
		if (rv <= 0) {
			perror("send failed");
			break;
		}
		sleep(SLEEPTIME);
	}

	fclose(filehd);
	close(sock_fd);
	return 0;
}
