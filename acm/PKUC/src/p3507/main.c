/*
 * main.c
 *
 *  Created on: Apr 6, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int a[6];
	int min;
	int max;
	int sum;

	int i;
	while (1) {
		sum = 0;
		min = 100;
		max = 0;
		for (i = 0; i < 6; ++i) {
			scanf("%d", &a[i]);
			if (a[i] < min) {
				min = a[i];
			}
			if (a[i] > max) {
				max = a[i];
			}
			sum += a[i];
		}
		sum -= (min + max);

		if (!a[0] && !a[1] && !a[2] && !a[3] && !a[4] && !a[5]) {
			break;
		}

		printf("%g\n", (float) sum / 4);
	}
	return 0;
}
