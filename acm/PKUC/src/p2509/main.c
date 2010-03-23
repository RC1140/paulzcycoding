/*
 * main.c
 *
 *  Created on: Mar 23, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int n, k;
	int sum;
	while (scanf("%d%d", &n, &k) == 2) {
		sum = n;
		while (n >= k) {
			sum += n / k;
			n = n % k + n / k;
		}
		printf("%d\n", sum);
	}
	return 0;
}
