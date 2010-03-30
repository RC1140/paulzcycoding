/*
 * main.c
 *
 *  Created on: Mar 28, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <limits.h>

#define MAXN 100

int main(void) {
	int n;
	int d[MAXN][MAXN];
	int i, j, k;
	int t, dist, min;

	while (1) {
		scanf("%d", &n);
		if (!n) {
			break;
		}

		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				d[i][j] = INT_MAX;
			}

			scanf("%d", &j);
			while (j--) {
				scanf("%d%d", &t, &dist);
				d[i][t - 1] = dist;
			}
		}

		for (k = 0; k < n; ++k) {
			for (i = 0; i < n; ++i) {
				for (j = 0; j < n; ++j) {
					if (d[i][k] < INT_MAX && d[k][j] < INT_MAX && d[i][k]
							+ d[k][j] < d[i][j]) {
						d[i][j] = d[i][k] + d[k][j];
					}
				}
			}
		}

		min = INT_MAX;

		for (i = 0; i < n; ++i) {
			dist = 0;
			for (j = 0; j < n; ++j) {
				if (j != i && d[i][j] > dist) {
					dist = d[i][j];
				}
			}
			if (dist < min) {
				min = dist;
				k = i;
			}
		}

		if (min == INT_MAX) {
			printf("disjoint\n");
		} else {
			printf("%d %d\n", k + 1, min);
		}
	}
	return 0;
}
