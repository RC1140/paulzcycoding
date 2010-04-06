/*
 * main.c
 *
 *  Created on: Apr 5, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXN 100

int comp(const void *a, const void *b) {
	return *(float *)a - *(float *)b;
}

int main(void) {
	float w[MAXN];
	int n, i;

	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		scanf("%f", &w[i]);
	}

	qsort(w, n, sizeof(float), comp);

	for (i = n - 1; i > 0; --i) {
		w[i - 1] = 2 * sqrt(w[i - 1] * w[i]);
	}

	printf("%.3f\n", w[0]);

	return 0;
}
