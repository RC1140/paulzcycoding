/*
 * p2105.c
 *
 *  Created on: Mar 17, 2010
 *      Author: XTOg
 */

#include <stdio.h>

const int E[8] = {0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1};

inline int bin2int(char* bin) {
	int result = 0, i;
	for (i = 0; i < 8; ++i) {
		if (bin[i] == '1') {
			result += E[i];
		}
	}
	return result;
}

int main(int argc, char* argv[]) {
	int n;
	char ip[33];

	scanf("%d", &n);
	while (n--) {
		scanf("%s", ip);
		printf("%d.%d.%d.%d\n", bin2int(ip), bin2int(ip + 8), bin2int(ip + 16),
				bin2int(ip + 24));
	}
	return 0;
}
