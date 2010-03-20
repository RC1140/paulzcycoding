/*
 * p2656.c
 *
 *  Created on: Mar 19, 2010
 *      Author: XTOg
 */

#include <stdio.h>

#define THRESHOLD 8

int main(void) {
	int n;
	int a, b;
	int mv, md;
	int i;
	while (1) {
		scanf("%d", &n);
		if (!n) break;

		mv = 0;
		for (i = 1; i <= n; ++i) {
			scanf("%d%d", &a, &b);
			if (a + b > mv) {
				mv = a + b;
				md = i;
			}
		}

		if (mv > THRESHOLD) {
			printf("%d\n", md);
		} else {
			printf("0\n");
		}
	}
	return 0;
}
