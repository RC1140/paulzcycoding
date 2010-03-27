/*
 * main.c
 *
 *  Created on: Mar 26, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#define FIX(a) ((a) % 9)?((a) % 9):9

int main(void) {
	int n, s, t;
	int i, j;
	scanf("%d%d", &n, &s);

	for (i = 1; i <= n; ++i) {
		for (j = 1; j < i; ++j) {
			printf("  ");
		}
		printf("%d", s);
		t = s;
		for (j = i; j < n; ++j) {
			t = FIX(t + j);
			printf(" %d", t);
		}
		printf("\n");
		s = FIX(s + i + 1);
	}
	return 0;
}
