/*
 * main.c
 *
 *  Created on: Apr 5, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>
#define MAXN 40

void store(char *buf, int *n, int *l) {
	int i;
	*l = strlen(buf) - 1;
	for (i = 0; i <= *l; ++i) {
		n[i] = buf[*l - i] - '0';
	}
}

int main(void) {
	char buf[MAXN + 1];
	int n1[MAXN], n2[MAXN], mul[MAXN * 2];
	int l1, l2, l;
	int i, j;

	scanf("%s", buf);
	store(buf, n1, &l1);
	scanf("%s", buf);
	store(buf, n2, &l2);

	memset(mul, 0, sizeof(mul));
	l = l1 + l2 + 1;

	for (i = 0; i <= l1; ++i) {
		for (j = 0; j <= l2; ++j) {
			mul[i + j] += n1[i] * n2[j];
		}
	}
	for (i = 0; i < l; ++i) {
		mul[i + 1] += mul[i] / 10;
		mul[i] %= 10;
	}
	while (mul[l] == 0 && l > 0) --l;
	for (; l >= 0; --l) printf("%d", mul[l]);
	printf("\n");
	return 0;
}
