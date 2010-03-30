/*
 * main.c
 *
 *  Created on: Mar 30, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <limits.h>

#define MAXN 1000

int main(void) {
	int n;
	int min[MAXN], t;
	int i, j;
	int max = 0;

	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		min[i] = INT_MAX;
	}

	for (i = 0; i < n; ++i) {
		scanf("%d", &t);
		for (j = 0; min[j] < t; ++j) {
		}
		min[j] = t;
		if (j > max) {
			max = j;
		}
	}

	printf("%d\n", max + 1);
	return 0;
}
