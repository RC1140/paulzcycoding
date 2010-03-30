/*
 * main.c
 *
 *  Created on: Mar 27, 2010
 *      Author: XTOg
 */

#include <stdio.h>

inline int gcd(int a, int b) {
	int t;
	while (a % b) {
		t = a;
		a = b;
		b = t % b;
	}
	return b;
}

int main(void) {
	int m, n;

	while (scanf("%d%d", &m, &n) != EOF) {
		if (gcd(m, n) == 1) {
			printf("%10d%10d%s\n\n", m, n, "    Good Choice");
		} else {
			printf("%10d%10d%s\n\n", m, n, "    Bad Choice");
		}
	}
	return 0;
}
