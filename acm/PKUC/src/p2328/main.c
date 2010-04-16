/*
 * main.c
 *
 *  Created on: Apr 14, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>

int main(void) {
	int n, h, l;
	char buf[20];
	while (1) {
		scanf("%d\n", &n);

		if (!n) {
			break;
		}
		l = 0;
		h = 11;

		while (1) {
			gets(buf);
			if (!strcmp(buf, "right on")) {
				break;
			}
			if (!strcmp(buf, "too low")) {
				l = (n > l) ? n : l;
			} else {
				h = (n < h) ? n : h;
			}
			scanf("%d\n", &n);
		}

		if (l < n && n < h) {
			printf("Stan may be honest\n");
		} else {
			printf("Stan is dishonest\n");
		}
	}

	return 0;
}
