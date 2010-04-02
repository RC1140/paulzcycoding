/*
 * main.c
 *
 *  Created on: Apr 2, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int k;
	int n, s;
	int t, r;

	int total;
	int rest;

	scanf("%d%d", &n, &k);
	while (k--) {
		scanf("%d%d%d", &s, &t, &r);
		total = (n + s - 1) / s;
		rest = (total - 1) / t;
		printf("%d\n", total + rest * r);
	}
	return 0;
}
