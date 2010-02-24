/*****************************************************************
 * File: server.c
 * by: Group YaKeXi
 * 
 * History:
 * 
 *  2010/02/22 Completed and tested by Hongkai Xing 
 *             on Ubuntu 9.10 with libnet 1.1.4 and libpcap 0.8.
 *
 *
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
 * Simple tcp server to test the tcp reset attack.
 *
 * Start as follows: ./server  server_ip  server_port
 *
 */

static const int MAXPENDING =5;	//maximum connection request
static const int SRVBUFFER = 65536;

void showErrorMsg(char *msg)
{
	perror(msg);
	exit(1);
}


int main(int argc, char **argv) {
	char *srv_addr_str;	//server address in string
	char *srv_port_str;	//server port number in string

	if (argc >= 2) {	//get or set server ip address
		srv_addr_str = argv[1];
	} else {
		srv_addr_str = "127.0.0.1";
	}

	if (argc >= 3) {	//get or set server port number
		srv_port_str = argv[2];
	} else {
		srv_port_str = "9999";
	}

	printf("starting server at IP %s, listening on port %s\n", srv_addr_str, srv_port_str);


	/*******************/
        int sock_fd,            //socket used in bind and listen function
            new_sock_fd,        //socket used in accept and read function
            srv_port_int,       //server port number in integer
            cli_len,            //size of cli_addr
            rv;                 //return value of read and write function
        char srv_buffer[SRVBUFFER];     //server's receive buffer
        struct sockaddr_in
                srv_addr,       //internet address structure for server
                cli_addr;       //internet address structure for client



	if ((sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) 
		showErrorMsg("Server cannot open socket\n");
	
	srv_port_int=atoi(srv_port_str);
	bzero((char*)&srv_addr,sizeof(srv_addr));	//zero out the structure
	srv_addr.sin_family=AF_INET;			//set to IPv4 address family
	srv_addr.sin_addr.s_addr=inet_addr(srv_addr_str);	//specific interface
	srv_addr.sin_port=htons(srv_port_int);	//host byte order --> network byte order
	

	if (bind(sock_fd, (struct sockaddr*)&srv_addr,sizeof(srv_addr))<0)
		showErrorMsg("Server cannot bind socket\n");
	if (listen(sock_fd,MAXPENDING)<0)
		showErrorMsg("Server cannot listen to socket\n");
	
	
	while(1){
		cli_len = sizeof(cli_addr);	//get the length of client address structure
		new_sock_fd = accept(sock_fd,(struct sockaddr *)&cli_addr,(socklen_t*)&cli_len);
		if (new_sock_fd < 0)
			showErrorMsg("Server cannot accept\n");
		rv=1;
		while(rv>0){
			bzero(srv_buffer, SRVBUFFER);
	                rv=recv(new_sock_fd,srv_buffer,SRVBUFFER-1,0);
                	printf("%d\n",rv);
			if (rv<0)
        	                showErrorMsg("Server cannot read from socket\n");
		}
		shutdown(new_sock_fd,2);
		close(new_sock_fd);	//close the client's socket
	}

	return 0;
}



