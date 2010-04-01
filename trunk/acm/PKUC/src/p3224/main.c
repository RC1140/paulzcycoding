/*
 * main.c
 *
 *  Created on: Apr 1, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int n;
	int i, j, p;
	int count, max, w;

	scanf("%d", &n);

	max = 0;
	for (i = 0; i < n; ++i) {
		count = 0;
		for (j = 0; j < n; ++j) {
			scanf("%d", &w);
			if (w == 3) {
				++count;
			}
		}
		if (count > max) {
			max = count;
			p = i;
		}
	}
	printf("%d\n", p + 1);
	return 0;
}
