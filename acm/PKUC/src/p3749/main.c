/*
 * main.c
 *
 *  Created on: Mar 31, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>
#define MAXN 200

int main(void) {
	char buf[MAXN + 1], *c;
	gets(buf);
	while (strcmp(buf, "ENDOFINPUT")) {
		gets(buf);
		for (c = buf; *c; ++c) {
			if (*c >= 'A' && *c <= 'Z') {
				*c = (*c - 'A' + 21) % 26 + 'A';
			}
		}
		puts(buf);
		gets(buf);
		gets(buf);
	}
	return 0;
}
