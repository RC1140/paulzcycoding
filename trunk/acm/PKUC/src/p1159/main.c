/*
 * p1159.c
 *
 *  Created on: Mar 17, 2010
 *      Author: XTOg
 */

#include <stdio.h>

#define MAXN 5001
#define MIN(X, Y) (((X) < (Y))?(X):(Y))

char str[MAXN];
int min[3][MAXN];

int main(int argc, char *argv[]) {
	int n;
	int i, l;
	int *l0, *l1, *l2, *t;

	scanf("%d", &n);
	scanf("%s", str);
	for (i = 0; i < n; ++i) {
		min[0][i] = 0;
		min[1][i] = 0;
	}
	l2 = min[0];
	l1 = min[1];
	l0 = min[2];

	for (l = 2; l <= n; ++l) {
		for (i = 0; i + l <= n; ++i) {
			if (str[i] == str[i + l - 1]) {
				l0[i] = l2[i + 1];
			} else {
				l0[i] = 1 + MIN(l1[i], l1[i + 1]);
			}
		}
		t = l2;
		l2 = l1;
		l1 = l0;
		l0 = t;
	}

	printf("%d\n", l1[0]);
	return 0;
}
