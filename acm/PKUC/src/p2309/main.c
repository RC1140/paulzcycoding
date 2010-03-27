/*
 * main.c
 *
 *  Created on: Mar 26, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int n;
	unsigned int r, t;

	scanf("%d", &n);
	while (n--) {
		scanf("%d", &r);
		t = r & (~r + 1);
		printf("%d %d\n", r - t + 1, r -1 + t);
	}

	return 0;
}
