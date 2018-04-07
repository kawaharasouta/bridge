#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
#include<arpa/inet.h>

#include<netinet/if_ether.h>
#include<netinet/ip.h>
*/
#include"initrawsock.h"
/*
struct ip_packet {
	struct ether_header eth_hdr;
	struct ip ip_hdr; 
};
*/

u_int16_t packet[1000] = {
	0xffff, 0xffff, 0xffff, 0xdeb4,
	0x6b16, 0x904c, 0x0800, 0x4500,	//up to service type
	
}

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

	struct ip_packet packet;	
}
