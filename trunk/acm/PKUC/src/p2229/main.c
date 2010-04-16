/*
 * main.c
 *
 *  Created on: Apr 6, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>

#define MAXN 1000000

int sum[MAXN + 1];

int get(int n) {
	if (n == 0) {
		return 1;
	}
	if (n % 2) {
		return get(n - 1);
	}
	if (!sum[n]) {
		sum[n] = (get(n / 2) + get(n - 2)) % 1000000000;
	}
	return sum[n];
}

int main(void) {
	int n;
	scanf("%d", &n);
	memset(sum, 0, sizeof(sum));
	printf("%d\n", get(n));
	return 0;
}
