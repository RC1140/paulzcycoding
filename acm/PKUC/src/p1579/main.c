/*
 * main.c
 *
 *  Created on: Mar 27, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <limits.h>

int ww[21][21][21];

int w(int a, int b, int c) {
	int d;
	if (a <= 0 || b <= 0 || c <= 0) {
		return 1;
	}
	if (a > 20 || b > 20 || c > 20) {
		return w(20, 20, 20);
	}
	if (ww[a][b][c] != INT_MAX) {
		return ww[a][b][c];
	}
	if (a < b && b < c) {
		d = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
	} else {
		d = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1,
				b - 1, c - 1);
	}

	ww[a][b][c] = d;
	return d;
}

int main(void) {
	int a, b, c;
	for (a = 0; a <= 20; ++a) {
		for (b = 0; b <= 20; ++b) {
			for (c = 0; c <= 20; ++c) {
				ww[a][b][c] = INT_MAX;
			}
		}
	}
	while (1) {
		scanf("%d%d%d", &a, &b, &c);
		if (a == -1 && b == -1 && c == -1) {
			break;
		}
		printf("w(%d, %d, %d) = %d\n", a, b, c, w(a, b, c));
	}
	return 0;
}
