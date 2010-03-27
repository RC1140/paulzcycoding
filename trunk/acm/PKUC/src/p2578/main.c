/*
 * main.c
 *
 *  Created on: Mar 27, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int i;
	int h;

	for (i = 0; i < 3; ++i) {
		scanf("%d", &h);
		if (h <= 168) {
			printf("CRASH %d\n", h);
			break;
		}
	}
	if (i == 3) {
		printf("NO CRASH\n");
	}
	return 0;
}
