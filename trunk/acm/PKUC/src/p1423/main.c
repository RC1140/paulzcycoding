/*
 * main.c
 *
 *  Created on: Apr 9, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <math.h>

#define MAXN 10000000
int e[MAXN + 1];

int main(void) {

	int n;
	int i, m;
	double l = 0;

	e[0] = 0;
	for (i = 1; i <= MAXN; ++i) {
		l = l + log10((double) i);
		e[i] = (int) floor(l) + 1;
	}

	scanf("%d", &n);
	while (n--) {
		scanf("%d", &m);
		printf("%d\n", e[m]);
	}
	return 0;
}
