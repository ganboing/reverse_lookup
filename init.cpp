#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <cinttypes>

union ipv4{
	uint32_t ip;
	struct{
		uint8_t a;
		uint8_t b;
		uint8_t c;
		uint8_t d;
	};
};

int main(int /*argc*/, char** argv){
	ipv4 net;
	ipv4 mask;
	sscanf(argv[1], "%" SCNu8 ".%" SCNu8 ".%" SCNu8 ".%" SCNu8, &net.d, &net.c, &net.b, &net.a);
	sscanf(argv[2], "%" SCNu8 ".%" SCNu8 ".%" SCNu8 ".%" SCNu8, &mask.d, &mask.c, &mask.b, &mask.a);
	uint32_t s = -mask.ip;
	if(s & s-1){
		fprintf(stderr, "invalid mask");
		exit(-1);
	}
	if(net.ip & s-1){
		fprintf(stderr, "invalid net");
		exit(-1);
	}
	uint32_t i=0;
	size_t cmd_len = strlen(argv[3]);
	char cmdline[cmd_len + 1 + 3*4 + 3 + 1];
	sprintf(cmdline, "%s ", argv[3]);
	do{
		ipv4 curr{net.ip + i};
		sprintf(cmdline + cmd_len + 1, "%" PRIu8 ".%" PRIu8 ".%" PRIu8 ".%" PRIu8, curr.d, curr.c, curr.b, curr.a);
		printf("%s %" PRIu32 " ", cmdline + cmd_len + 1, curr.ip);
		fflush(stdout);
		system(cmdline);
	}while(++i != s);
	return 0;
}
