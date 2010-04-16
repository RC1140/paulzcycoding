/*
 * main.c
 *
 *  Created on: Apr 13, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	char c;
	int i = 0;
	while ((c = getc(stdin)) != EOF) {
		if (c == '"') {
			if ((++i) % 2) {
				putchar('`');
				putchar('`');
			} else {
				putchar('\'');
				putchar('\'');
			}
		} else {
			putchar(c);
		}
	}
	return 0;
}
