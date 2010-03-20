/*
 * p1658.c
 *
 *  Created on: Mar 17, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(int argc, char* argv[]) {
	int a, b, c, d;
	int t;

	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		printf("%d %d %d %d", a, b, c, d);
		if (2 * b == a + c && 2 * c == b + d) {
			printf(" %d\n", 2 * d - c);
		} else {
			printf(" %d\n", d * d / c);
		}
	}

	return 0;
}
