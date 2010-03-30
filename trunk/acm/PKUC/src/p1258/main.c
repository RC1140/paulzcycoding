/*
 * main.c
 *
 *  Created on: Mar 28, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 100

int main(void) {
	int n;
	int map[MAXN][MAXN];

	int i, j, k;
	int in_tree[MAXN];
	int dist[MAXN], min;
	int total;

	while (scanf("%d", &n) != EOF) {
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				scanf("%d", &map[i][j]);
			}
		}

		total = 0;
		memset(in_tree, 0, sizeof(in_tree));
		in_tree[0] = 1;
		for (i = 1; i < n; ++i) {
			dist[i] = map[i][0];
		}

		for (i = 1; i < n; ++i) {
			min = INT_MAX;
			for (j = 1; j < n; ++j) {
				if (!in_tree[j] && dist[j] < min) {
					min = dist[j];
					k = j;
				}
			}

			in_tree[k] = 1;
			total += dist[k];

			for (j = 1; j < n; ++j) {
				if (!in_tree[j] && map[j][k] < dist[j]) {
					dist[j] = map[j][k];
				}
			}
		}

		printf("%d\n", total);
	}
	return 0;
}
