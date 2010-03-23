/*
 * main.c
 *
 *  Created on: Mar 23, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>

int main(void) {
	unsigned int e[32];
	char buf[33];

	int i, j;
	int result;

	e[0] = 2;
	for (i = 1; i < 32; ++i) {
		e[i] = e[i - 1] * 2;
	}
	for (i = 0; i < 32; ++i) {
		--e[i];
	}

	while(1) {
		gets(buf);
		if (!strcmp(buf, "0")) {
			break;
		}
		j = strlen(buf);
		result = 0;
		for (i = 0; i < j; ++i) {
			result += (buf[j - i - 1] - '0') * e[i];
		}
		printf("%d\n", result);
	}
	return 0;
}
