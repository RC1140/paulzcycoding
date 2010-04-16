/*
 * main.c
 *
 *  Created on: Apr 15, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int N;
	int i;
	int n;
	int r;
	scanf("%d", &N);
	for (i = 1; i <= N; ++i) {
		scanf("%d", &n);
		switch (n % 4) {
		case 0:
			r = n / 4 * (n + 1) * ((n + 2) / 2) * (n + 3);
			break;
		case 1:
			r = n * ((n + 1) / 2) * (n + 2) * ((n + 3) / 4);
			break;
		case 2:
			r = n / 2 * (n + 1) * ((n + 2) / 4) * (n + 3);
			break;
		case 3:
			r = n * ((n + 1) / 4) * (n + 2) * ((n + 3) / 2);
			break;
		}
		printf("%d %d %d\n", i, n, r);

	}
}
