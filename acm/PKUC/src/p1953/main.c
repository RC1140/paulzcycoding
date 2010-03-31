/*
 * main.c
 *
 *  Created on: Mar 30, 2010
 *      Author: XTOg
 */

#include <stdio.h>

#define MAXN 45
int main(void) {
	unsigned int c[MAXN + 1][2];
	int i, j, n;

	c[0][0] = 1;
	c[0][1] = 0;

	for (i = 1; i <= MAXN; ++i) {
		c[i][0] = c[i - 1][0] + c[i - 1][1];
		c[i][1] = c[i - 1][0];
	}

	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &j);
		printf("Scenario #%d:\n%u\n\n", i, c[j][0] + c[j][1]);

	}

	return 0;
}
