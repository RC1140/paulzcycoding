/*
 * main.c
 *
 *  Created on: Apr 16, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

int comp(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int main(void) {
	int t;
	int n, i;
	int rope[MAXN];
	int max;

	for (scanf("%d", &t); t; t--) {
		scanf("%d", &n);
		for (i = 0; i < n; ++i) {
			scanf("%d", &rope[i]);
		}
		qsort(rope, n, sizeof(int), comp);

		max = 0;
		for (i = 0; i < n; ++i) {
			if (rope[i] * (n - i) > max) {
				max = rope[i] * (n - i);
			}
		}

		printf("%d\n", max);
	}



	return 0;
}
