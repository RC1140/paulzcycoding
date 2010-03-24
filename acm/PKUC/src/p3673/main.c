/*
 * main.c
 *
 *  Created on: Mar 23, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int a, b, i, j;
	int sum = 0;
	scanf("%d%d", &a, &b);
	for (i = a; i; i /= 10) {
		for (j = b; j; j /= 10) {
			sum += (i % 10) * (j % 10);
		}
	}
	printf("%d\n", sum);
	return 0;
}
