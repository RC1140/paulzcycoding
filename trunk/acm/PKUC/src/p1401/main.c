/*
 * main.c
 *
 *  Created on: Mar 23, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int n;
	int num;
	int sum;

	scanf("%d", &n);
	while (n--) {
		scanf("%d", &num);
		for (sum = 0; num; num /= 5) {
			sum += num / 5;
		}
		printf("%d\n", sum);
	}
	return 0;
}
