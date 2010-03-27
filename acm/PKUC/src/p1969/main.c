/*
 * main.c
 *
 *  Created on: Mar 27, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int n, m, i;
	while (scanf("%d", &n) != EOF) {
		m = n;
		for (i = 1; m > i; ++i) {
			m -= i;
		}
		if (i % 2) {
			printf("TERM %d IS %d/%d\n", n, i - m + 1, m);
		} else {
			printf("TERM %d IS %d/%d\n", n, m, i - m + 1);
		}
	}
	return 0;
}
