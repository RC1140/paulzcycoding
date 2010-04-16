/*
 * main.c
 *
 *  Created on: Apr 13, 2010
 *      Author: XTOg
 */

#include <stdio.h>

#define MAXN 26
#define BIGNUM 1000000

int main(void) {
	int n;
	int map[MAXN][MAXN];
	int dist[MAXN];
	int road;
	int i, j;
	char c;
	int length;
	int min;
	int p;
	int sum;

	while (1) {
		scanf("%d", &n);
		if (!n) {
			break;
		}

		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				map[i][j] = BIGNUM;
			}
		}

		for (i = 0; i < n - 1; ++i) {
			scanf("\n%c %d", &c, &road);

			for (j = 0; j < road; ++j) {
				scanf(" %c %d", &c, &length);
				map[i][c - 'A'] = length;
				map[c - 'A'][i] = length;
			}
		}

		for (i = 1; i < n; ++i) {
			dist[i] = map[0][i];
		}
		dist[0] = 0;
		sum = 0;

		for (i = 1; i < n; ++i) {
			min = BIGNUM;
			for (j = 1; j < n; ++j) {
				if (dist[j] && dist[j] < min) {
					min = dist[j];
					p = j;
				}
			}
			sum += dist[p];
			dist[p] = 0;
			for (j = 1; j < n; ++j) {
				if (map[p][j] < dist[j]) {
					dist[j] = map[p][j];
				}
			}
		}

		printf("%d\n", sum);
	}

	return 0;
}
