/*
 * main.c
 *
 *  Created on: Mar 23, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int n;
	int k;
	int o;
	int sum;

	scanf("%d", &n);
	while (n--) {
		scanf("%d", &k);
		sum = 1 - k;
		while (k--) {
			scanf("%d", &o);
			sum += o;
		}
		printf("%d\n", sum);
	}
	return 0;
}
