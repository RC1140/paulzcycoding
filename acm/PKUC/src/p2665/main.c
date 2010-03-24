/*
 * main.c
 *
 *  Created on: Mar 23, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int l, m;
	int i;
	int a, b;

	while (1) {
		scanf("%d%d", &l, &m);
		if (l == 0) break;
		++l;
		for (i = 0; i < m; ++i) {
			scanf("%d%d", &a, &b);
			l -= (b - a + 1);
		}
		printf("%d\n", l);
	}

	return 0;
}
