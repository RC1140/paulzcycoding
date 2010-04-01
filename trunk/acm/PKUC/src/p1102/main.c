/*
 * main.c
 *
 *  Created on: Apr 1, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	const int tp[] = { 1, 0, 1, 1, 0, 1, 1, 1, 1, 1 };
	const int ul[] = { 1, 0, 0, 0, 1, 1, 1, 0, 1, 1 };
	const int ur[] = { 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 };
	const int md[] = { 0, 0, 1, 1, 1, 1, 1, 0, 1, 1 };
	const int ll[] = { 1, 0, 1, 0, 0, 0, 1, 0, 1, 0 };
	const int lr[] = { 1, 1, 0, 1, 1, 1, 1, 1, 1, 1 };
	const int bt[] = { 1, 0, 1, 1, 0, 1, 1, 0, 1, 1 };

	int s, i, j;
	char n[9], *c;

	while (1) {
		scanf("%d %s", &s, n);
		if (!s) {
			break;
		}

		for (c = n; *c; ++c) {
			putchar(' ');
			for (i = 0; i < s; ++i) {
				putchar(tp[*c - '0'] ? '-' : ' ');
			}
			putchar(' ');
			putchar(' ');
		}
		putchar('\n');

		for (i = 0; i < s; ++i) {
			for (c = n; *c; ++c) {
				putchar(ul[*c - '0'] ? '|' : ' ');
				for (j = 0; j < s; ++j) {
					putchar(' ');
				}
				putchar(ur[*c - '0'] ? '|' : ' ');
				putchar(' ');
			}
			putchar('\n');
		}

		for (c = n; *c; ++c) {
			putchar(' ');
			for (i = 0; i < s; ++i) {
				putchar(md[*c - '0'] ? '-' : ' ');
			}
			putchar(' ');
			putchar(' ');
		}
		putchar('\n');

		for (i = 0; i < s; ++i) {
			for (c = n; *c; ++c) {
				putchar(ll[*c - '0'] ? '|' : ' ');
				for (j = 0; j < s; ++j) {
					putchar(' ');
				}
				putchar(lr[*c - '0'] ? '|' : ' ');
				putchar(' ');
			}
			putchar('\n');
		}

		for (c = n; *c; ++c) {
			putchar(' ');
			for (i = 0; i < s; ++i) {
				putchar(bt[*c - '0'] ? '-' : ' ');
			}
			putchar(' ');
			putchar(' ');
		}
		putchar('\n');
		putchar('\n');
	}
	return 0;
}
