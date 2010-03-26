/*
 * main.c
 *
 *  Created on: Mar 25, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int n, i, sum;

	printf("PERFECTION OUTPUT\n");
	while (1) {
		scanf("%d", &n);
		if (!n) {
			break;
		}
		sum = 0;
		for (i = 1; i * 2 <= n; ++i) {
			if (!(n % i)) {
				sum += i;
			}
		}

		if (sum < n) {
			printf("%5d  %s\n", n, "DEFICIENT");
		} else if (sum == n) {
			printf("%5d  %s\n", n, "PERFECT");
		} else {
			printf("%5d  %s\n", n, "ABUNDANT");
		}
	}
	printf("END OF OUTPUT\n");
	return 0;
}
