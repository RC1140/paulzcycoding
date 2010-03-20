/*
 * p2140.c
 *
 *  Created on: Mar 17, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
	int n;
	int i, sum;
	scanf("%d", &n);

	sum = 0;
	for (i = 1; i * (i - 1) / 2 < n; ++i) {
		if ((n - i * (i - 1) / 2) % i == 0) {
			++sum;
		}
	}
	printf("%d\n", sum);
	return 0;
}
