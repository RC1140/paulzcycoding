/*
 * main.c
 *
 *  Created on: Apr 16, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	const int t[] = { 0, 1, 2, 3, 0, 1, 2, 0, 0, 2, 2, 4, 5, 5, 0, 1, 2, 6, 2,
			3, 0, 1, 0, 2, 0, 2 };
	char c;
	int i;

	while ((c = getchar()) != EOF) {
		i = t[c - 'A'];
		for (; c != '\n'; c = getchar()) {
			if (t[c - 'A'] != i) {
				if (i) {
					putchar('0' + i);
				}
				i = t[c - 'A'];
			}
		}
		if (i) {
			putchar('0' + i);
		}
		putchar('\n');
	}
	return 0;
}
