#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
#include<arpa/inet.h>

#include<netinet/if_ether.h>
#include<netinet/ip.h>
*/
#include<netinet/in.h>
#include"initrawsock.h"
/*
struct ip_packet {
	struct ether_header eth_hdr;
	struct ip ip_hdr; 
};
*/

#if 1
//u_int16_t packet[1000] = {
//	0xffff, 0xffff, 0xffff, 0xdeb4,
//	0x6b16, 0x904c, 0x0800, 0x4500,	//up to service type
//	0x0014, 0x1000, 0x4000, 0x4006, //length, ID, Flags, offset, TTL, proto
//	0x16e2, 0x0a00, 0x0002, 0x0a00,
//	0x0001
//};
//source ip 10.0.0.2
//dest ip 10.0.0.1
#else
u_int16_t packet[1000] = {
	0xdeb4, 0x6b16, 0x904c, 0xffff,
	0xffff, 0xffff, 0x0800, 0x4500,	//up to service type
	0x0014, 0x1000, 0x4000, 0x4006, //length, ID, Flags, offset, TTL, proto
	0x16e2, 0x0a00, 0x0002, 0x0a00,
	0x0001
};
#endif

u_int16_t icmp_packet[50] = {
	0x0036, 0x9f3e, 0xa08a, 0xa036,
	0x9f3f, 0x6202, 0x0800, 0x4500,
	0x0054, 0x670b, 0x4000, 0x4001,
	0xbf91, 0x0a00, 0x0007, 0x0a00,
	0x0006, 0x0800, 0x3687, 0x7ca3,
	0x0001, 0x31d1, 0xdd5a, 0x0000,
	0x0000
};


u_int16_t arp_packet[100] = {
	0xffff, 0xffff, 0xffff, 0xdeb4,
	0x6b16, 0x904c, 0x0806, 
};


int main(int argc, char **argv){
	int sock, size;
	u_char buf[2048];

	if (argc < 2){ 
    fprintf(stderr, "usage: ./main [dev-name]\n");
    exit(1);
  }

  if ((sock = initrawsock(argv[1], 0, 0)) < 0){ 
    fprintf(stderr, "InitRawSocket:error:%s\n", argv[1]);
    exit(1);
  }

	//struct ip_packet packet;
	//write(sock, icmp_packet, strlen(icmp_packet));

	struct sockaddr_in to;
	to.sin_addr.s_addr = (u_long)0x0a000006;
	to.sin_family = AF_INET;
	//to.sin_port = ;

	int n;
#if 0
	if ((n = write(sock, icmp_packet, strlen(icmp_packet))) <= 0){
		fprintf(stdout, "can not send packet\n");
		exit(1);
	}
	fflush(sock);
#endif
	if ((n = sendto(sock, (char *)icmp_packet, strlen(icmp_packet), 0, (struct sockaddr *)&to, sizeof(to))) <= 0){
		fprintf(stdout, "can not send packet\n");
		exit(1);
	}
	
	close(sock);
}
