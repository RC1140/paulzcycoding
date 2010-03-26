/*
 * main.c
 *
 *  Created on: Mar 26, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>

int main(void) {
	char buf[80];
	char *c;
	while (strcmp(gets(buf), "#")) {
		for (c = buf; *c; ++c) {
			switch (*c) {
			case ' ':
				fputs("%20", stdout);
				break;
			case '!':
				fputs("%21", stdout);
				break;
			case '$':
				fputs("%24", stdout);
				break;
			case '%':
				fputs("%25", stdout);
				break;
			case '(':
				fputs("%28", stdout);
				break;
			case ')':
				fputs("%29", stdout);
				break;
			case '*':
				fputs("%2a", stdout);
				break;
			default:
				putchar(*c);
			}
		}
		putchar('\n');
	}
	return 0;
}
