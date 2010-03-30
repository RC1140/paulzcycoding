/*
 * main.c
 *
 *  Created on: Mar 30, 2010
 *      Author: XTOg
 */

#include <stdio.h>

inline int reverse(int a) {
	int b = 0;
	while (a) {
		b *= 10;
		b += a % 10;
		a = a / 10;
	}
	while (!(b % 10)) {
		b /= 10;
	}
	return b;
}

int main(void) {
	int n;
	int a, b;

	scanf("%d", &n);

	while (n--) {
		scanf("%d%d", &a, &b);
		printf("%d\n", reverse(reverse(a) + reverse(b)));
	}
	return 0;
}
