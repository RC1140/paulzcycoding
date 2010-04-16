/*
 * main.c
 *
 *  Created on: Apr 12, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int t;
	int n, m;
	int e;
	int b;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		e = 0;
		m = n;
		while (n--) {
			scanf("%d", &b);
			if (b) {
				e += (n % 2) ? 1 : -1;
			}
		}
		if (m % 2 || (-1 <= e && e <= 1)) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}
