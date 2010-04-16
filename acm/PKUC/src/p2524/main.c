/*
 * main.c
 *
 *  Created on: Apr 14, 2010
 *      Author: XTOg
 */

#include <stdio.h>

#define MAXN 50000
int p[MAXN];

int getp(int i) {
	if (p[i] == i) {
		return p[i];
	}
	p[i] = getp(p[i]);
	return p[i];
}

int main(void) {
	int n, m;
	int i, j;
	int c = 0;
	while (1) {
		scanf("%d%d", &n, &m);
		if (!n) {
			break;
		}
		for (i = 0; i < n; ++i) {
			p[i] = i;
		}
		while (m--) {
			scanf("%d%d", &i, &j);
			--i;
			--j;
			if (getp(i) != getp(j)) {
				p[p[j]] = p[i];
				--n;
			}
		}
		printf("Case %d: %d\n", ++c, n);
	}
	return 0;
}
