/*
 * main.c
 *
 *  Created on: Mar 25, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>
#define MAXN 350

inline int MAX(int a, int b) {
	return (a > b)?a:b;
}

int main(void) {
	int max[MAXN];
	int n;
	int i, j;
	int t;

	scanf("%d", &n);
	scanf("%d", max);

	for (i = 1; i < n; ++i) {
		scanf("%d", &t);
		max[i] = max[i - 1] + t;

		for (j = i - 1; j > 0; --j) {
			scanf("%d", &t);
			max[j] = MAX(max[j], max[j - 1]) + t;
		}

		scanf("%d", &t);
		max[0] = max[0] + t;
	}

	j = 0;
	for (i = 0; i < n; ++i) {
		if (max[i] > j) {
			j = max[i];
		}
	}

	printf("%d\n", j);
	return 0;
}
