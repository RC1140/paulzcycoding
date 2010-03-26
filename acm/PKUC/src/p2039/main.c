/*
 * main.c
 *
 *  Created on: Mar 25, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>

int main(void) {
	char buf[201];
	int w;
	int i, j, l;

	while (1) {
		scanf("%d", &w);
		if (!w) {
			break;
		}
		scanf("%s", buf);

		l = strlen(buf) / w;
		for (i = 0; i < w; ++i) {
			for (j = 0; j < l; ++j) {
				if (j % 2) {
					putchar(buf[j * w + w - i - 1]);
				} else {
					putchar(buf[j * w + i]);
				}
			}
		}
		putchar('\n');
	}
	return 0;
}
