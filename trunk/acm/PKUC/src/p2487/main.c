/*
 * main.c
 *
 *  Created on: Apr 14, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXF 1000

int comp(const void *a, const void *b) {
	return *(int *)b - *(int *)a;
}

int main(void) {
	int c, C;
	int s, f;
	int stamp[MAXF];

	int i;

	scanf("%d", &C);
	for (c = 1; c <= C; ++c) {
		scanf("%d%d", &s, &f);
		for (i = 0; i < f; ++i) {
			scanf("%d", &stamp[i]);
		}

		qsort(stamp, f, sizeof(int), comp);
		for (i = 0; i < f; ++i) {
			s -= stamp[i];
			if (s <= 0) {
				break;
			}
		}

		printf("Scenario #%d:\n", c);
		if (i == f) {
			printf("impossible\n\n");
		} else {
			printf("%d\n\n", i + 1);
		}
	}
	return 0;
}
