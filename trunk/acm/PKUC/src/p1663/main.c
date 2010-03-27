/*
 * main.c
 *
 *  Created on: Mar 27, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int n;
	int x, y;

	scanf("%d", &n);

	while (n--) {
		scanf("%d%d", &x, &y);
		if (x == y) {
			printf("%d\n", ((x & ~1) << 1) + x % 2);
		} else if (x == y + 2) {
			printf("%d\n", ((x & ~1) << 1) - 2 + x % 2);
		} else {
			printf("No Number\n");
		}
	}
	return 0;
}
