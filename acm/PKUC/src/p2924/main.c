/*
 * main.c
 *
 *  Created on: Mar 26, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int n, m;

	long long a, b;

	scanf("%d", &n) ;

	for (m = 1; m <= n; ++m) {
		scanf("%lld%lld", &a, &b);
		printf("Scenario #%d:\n%lld\n\n", m, (a + b) * (b - a + 1) / 2);
	}
	return 0;
}
