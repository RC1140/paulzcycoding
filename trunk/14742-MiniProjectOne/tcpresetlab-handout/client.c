/*****************************************************************
 * File: client.c
 * by: Group YaKeXi
 * 
 * History:
 * 
 *  2010/02/22 Completed and tested by Hongkai Xing 
 *             on Ubuntu 9.10 with libnet 1.1.4 and libpcap 0.8.
 *
 *****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
/*
 * Simple tcp client for use in tcp reset attack testing.
 *
 * Execute as follows: ./client  server_address server_port client_port input_file
 *
 */
static const int CLIBUFFER = 1024;
static const int CLISENT_MAX = 800 * 1024;//800 kilobytes

void showErrorMsg(char *msg)
{
        perror(msg);
        exit(1);
}

int main(int argc, char **argv)
{	
	char *cli_port_str;
	char *srv_addr_str;
	char *srv_port_str;
	char *input_file_str; 

	if(argc >= 4) {
		cli_port_str = argv[3];
	} else {
		cli_port_str = "10001";
	}
  
	if (argc >= 2) {
		srv_addr_str = argv[1];
	} else {
		srv_addr_str = "127.0.0.1";
	}
  
	if (argc >= 3) {
		srv_port_str = argv[2];
	}
	else {
		srv_port_str = "9999";
	}

	if(argc >= 5) {
		input_file_str = argv[4];
	} else {
		input_file_str = "junk";
	}

	printf("starting client using port %s, connecting to server %s:%s, reading file %s\n",
		cli_port_str, srv_addr_str, srv_port_str, input_file_str);

	/*******************/
	int sock_fd,
	    srv_port_int,
	    rv,
	    cli_sent;

	struct in_addr srv_ipv4addr;	//ipv4 address structure for server
	struct sockaddr_in 
		srv_addr,	//internet address structure for server
		cli_addr;	//internet address structure for client
	struct hostent *srv_host;	//pointer to internet protocol host (server)

	char cli_buffer[CLIBUFFER];
	FILE *input_file;

	srv_port_int = atoi(srv_port_str);
        if ((sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		showErrorMsg("Client cannot open socket\n");

	inet_pton(AF_INET, srv_addr_str, &srv_ipv4addr);
	srv_host = gethostbyaddr(&srv_ipv4addr,sizeof(srv_ipv4addr),AF_INET);
	if (srv_host == NULL)
		showErrorMsg("Client cannot find the server host\n");
	
        bzero((char*)&srv_addr,sizeof(srv_addr));       //zero out the structure
        srv_addr.sin_family=AF_INET;                    //set to IPv4 address family
	bcopy((char*)srv_host->h_addr, (char*)&srv_addr.sin_addr.s_addr, srv_host->h_length);		srv_addr.sin_port=htons(srv_port_int);  	//host byte order-->network byte order
	
	// to specifiy the source port
	cli_addr.sin_family=AF_INET;
	cli_addr.sin_port=htons(atoi(cli_port_str));
	cli_addr.sin_addr.s_addr=INADDR_ANY;
	if (bind(sock_fd,(struct sockaddr*)&cli_addr,sizeof(cli_addr))<0)
		showErrorMsg("Client cannot bind socket");

	// connect to the server
	if (connect(sock_fd, (struct sockaddr*)&srv_addr,sizeof(srv_addr))<0)
		showErrorMsg("Client cannot connect to server\n");
	bzero(cli_buffer,CLIBUFFER);

	// try to open the file
	if ((input_file=fopen(input_file_str,"r"))==NULL)
		showErrorMsg("Client cannot open file\n");
	
	// try to send the file
	cli_sent=0;
	while(fgets(cli_buffer,CLIBUFFER,input_file)!=NULL){
		rv=write(sock_fd,cli_buffer,strlen(cli_buffer));
		printf("%d\n",rv);
		if (rv<0)
			 showErrorMsg("Client cannot write to socket\n");
		cli_sent+=rv;
		if (cli_sent > CLISENT_MAX)
			break;
		bzero(cli_buffer,CLIBUFFER);
		sleep(1);
	}

	fclose(input_file);
	close(sock_fd);
	return 0;  
}

