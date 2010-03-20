/*
 * p2388.c
 *
 *  Created on: Mar 17, 2010
 *      Author: XTOg
 */

#include <stdio.h>

void divide(int*, int, int, int);

int main(int argc, char* argv[]) {
	const int MAXN = 10000;
	int n;
	int milk[MAXN];
	int i;

	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		scanf("%d", &milk[i]);
	}

	divide(milk, 0, n, n / 2);
	printf("%d\n", milk[n / 2]);

	return 0;
}

void divide(int* a, int l, int h, int t) {
	int pivot = a[l];
	int i = l, j = h - 1;

	while (i < j) {
		while (i < j && a[j] >= pivot) --j;
		a[i] = a[j];
		while (i < j && a[i] <= pivot) ++i;
		a[j] = a[i];
	}
	a[i] = pivot;

	if (i < t) {
		divide(a, i + 1, h, t);
	} else if (i > t) {
		divide(a, l, i, t);
	}
}
