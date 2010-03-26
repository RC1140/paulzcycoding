/*
 * main.c
 *
 *  Created on: Mar 25, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int n;
	int i, j;
	while (scanf("%d", &n) != EOF) {
		for (i = 1, j = 1; i; ++j) {
			i = (i * 10 + 1) % n;
		}
		printf("%d\n", j);
	}
	return 0;
}
