/*
 * main.c
 *
 *  Created on: Mar 23, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>

#define getnum(c) ((c == ' ')?0:(c - 'A' + 1))

int main(void) {
	char buf[256];
	int sum;
	int i, l;

	while (1) {
		gets(buf);
		if (!strcmp(buf, "#")) {
			break;
		}
		l = strlen(buf);

		sum = 0;
		for (i = 0; i < l; ++i) {
			sum += (i + 1) * getnum(buf[i]);
		}

		printf("%d\n", sum);

	}
	return 0;
}
