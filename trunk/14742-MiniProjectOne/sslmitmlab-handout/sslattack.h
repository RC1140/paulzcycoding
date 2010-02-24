/*****************************************************************
 * File: ssl_attack.h
 * by: Group YaKeXi
 * 
 * History:
 * 
 *  2010/02/22 Completed and tested by Hongkai Xing 
 *             on Ubuntu 9.10 with libnet 1.1.4 and libpcap 0.8.
 *  
 ******************************************************************
 *  [ dns hijacker v1.3 ]                                         *
 *                                                                *
 *  originally written by pedram amini (pedram@redhive.com)       *
 *  modified for SSL Attack Lab                                   *
 *                                                                *
 *****************************************************************/

/* includes */
#include <libnet.h>
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <resolv.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> 
#include <net/ethernet.h>
#include <netinet/ether.h> 

/* defines */
#define BUFSIZE  1518

#ifndef ETHER_HDRLEN
#define ETHER_HDRLEN 14
#endif

/* Storage for Packet Generation */
struct sp  {
	u_long  src_address;                /* source address               */
	u_long  dst_address;                /* destination address          */
	u_short src_port;                   /* source port                  */
	u_short dst_port;                   /* destination port             */
	u_short dns_id;                     /* dns id                       */
	int     payload_size;               /* size of our payload          */
	u_char  payload[512];               /* payload storage              */
	char    query[128];                 /* query being asked            */
	char    *response;                  /* response we are using        */
};

/* globals */
struct sp spoofpacket;               /* Spoofing Packet                    */

/* function prototypes */
int analyze_packet(const u_char *, int, char *, char *); /* parse a packet, build an answer */
pcap_t *set_cap_dev(char *, char *);                       /* set capdev up to capture dns    */
void spoof_dns(char *);                               /* spoof a dns packet              */

/* dns packet header
 *
 *  |--- 1 byte ----|
 *  +---------------|---------------|---------------|---------------+
 *  |            DNS ID             | QR,OP,AA,TC,RD|RA,0,AD,CD,CODE|
 *  |---------------|---------------|---------------|---------------|
 *  |         # Questions           |          # Answers            |
 *  |---------------|---------------|---------------|---------------|
 *  |         # Authority           |          # Resource           |
 *  +---------------|---------------|---------------|---------------+
 *
 */
struct dnshdr   {
    unsigned    id:      16;            /* query identification number     */
    unsigned    rd:       1;            /* recursion desired               */
    unsigned    tc:       1;            /* truncated message               */
    unsigned    aa:       1;            /* authoritative answer            */
    unsigned    opcode:   4;            /* purpose of message              */
    unsigned    qr:       1;            /* response flag                   */
    unsigned    rcode:    4;            /* response code                   */
    unsigned    cd:       1;            /* checking disabled by resolver   */
    unsigned    ad:       1;            /* authentic data from named       */
    unsigned    unused:   1;            /* unused bits (MBZ as of 4.9.3a3) */
    unsigned    ra:       1;            /* recursion available             */
    unsigned    qdcount: 16;            /* number of question entries      */
    unsigned    ancount: 16;            /* number of answer entries        */
    unsigned    nscount: 16;            /* number of authority entries     */
    unsigned    arcount: 16;            /* number of resource entries      */
};

