/*
 * main.c
 *
 *  Created on: Apr 2, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int n;
	int a, b, top;
	int numof9;
	char buf[4];

	scanf("%d\n", &n);
	gets(buf);
	a = buf[0] - '0';
	b = buf[2] - '0';
	top = a + b;
	numof9 = 0;
	while (--n) {
		gets(buf);
		a = buf[0] - '0';
		b = buf[2] - '0';
		if (a + b >= 10) {
			putchar('0' + top + 1);
			while (numof9--) {
				putchar('0');
			}
			numof9 = 0;
			top = a + b - 10;
		} else if (a + b == 9) {
			++numof9;
		} else {
			putchar(top + '0');
			while (numof9--) {
				putchar('9');
			}
			numof9 = 0;
			top = a + b;
		}
	}
	if (a + b == 9) {
		putchar(top + '0');
		while (numof9--) {
			putchar('9');
		}
	} else {
		putchar(top + '0');
	}
	putchar('\n');
	return 0;
}
