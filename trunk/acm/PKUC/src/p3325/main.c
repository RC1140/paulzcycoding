/*
 * main.c
 *
 *  Created on: Mar 25, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int n;
	int sum, min, max;
	int i;
	int t;
	while (1) {
		scanf("%d", &n);
		if (!n)
			break;
		max = 0;
		min = 1000;
		sum = 0;
		for (i = 0; i < n; ++i) {
			scanf("%d", &t);
			sum += t;
			if (t < min) {
				min = t;
			}
			if (t > max) {
				max = t;
			}
		}
		printf("%d\n", (sum - min - max) / (n - 2));
	}
	return 0;
}
