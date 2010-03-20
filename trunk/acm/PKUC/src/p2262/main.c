/*
 * p2262.c
 *
 *  Created on: Mar 17, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int notPrime(int p) {
	int i;
	for (i = 3; i * i <= p; i += 2) {
		if (!(p % i)) {
			return 1;
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {

	int n;
	int p;

	scanf("%d", &n);
	while (n > 0) {
		for (p = 3; notPrime(p) || notPrime(n - p); p += 2) {
		}
		printf("%d = %d + %d\n", n, p, n - p);
		scanf("%d", &n);
	}
	return 0;
}

