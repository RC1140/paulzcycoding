/*
 * main.c
 *
 *  Created on: Mar 27, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	char map[27];
	char buf[81];
	char *c;

	gets(map);
	gets(buf);

	for (c = buf; *c; ++c) {
		if ('a' <= *c && *c <= 'z') {
			putchar(map[*c - 'a']);
		} else if ('A' <= *c && *c <= 'Z') {
			putchar(map[*c - 'A'] + 'A' - 'a');
		} else {
			putchar(*c);
		}
	}

	putchar('\n');
	return 0;
}
