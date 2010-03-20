/*
 * main.c
 *
 *  Created on: Mar 20, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BIGINT 10000
#define check(u, v) \
	if (1) {\
		if (distance[(u)] != BIGINT && distance[(u)] + weight[(u)][(v)] < distance[(v)]) {\
			distance[(v)] = distance[(u)] + weight[(u)][(v)];\
			parent[(v)] = (u);\
			flag = 1;\
		}\
	}

#define MAXN 200
#define MAXMAN 200
#define MAN 'm'
#define HOME 'H'

#define SOURCE 0
#define TARGET 2 * MAXMAN + 1

inline void get_input(int n, int m, int *man_x, int *man_y, int *home_x,
		int *home_y, int *man) {
	int i, j;
	int pm = 0, ph = 0;
	char buf[MAXN + 1];

	for (i = 0; i < n; ++i) {
		scanf("%s", buf);
		for (j = 0; j < m; ++j) {
			switch (buf[j]) {
			case HOME:
				home_x[ph] = i;
				home_y[ph] = j;
				++ph;
				break;
			case MAN:
				man_x[pm] = i;
				man_y[pm] = j;
				++pm;
				break;
			}
		}
	}
	*man = ph;
#ifdef DEBUG
	printf("%d\n", *man);
#endif
}

void build_graph(int *man_x, int *man_y, int *home_x, int *home_y, int man,
		int weight[2 * MAXMAN + 2][2 * MAXMAN + 2],
		int residual[2 * MAXMAN + 2][2 * MAXMAN + 2]) {
	int i, j;

	for (i = 0; i < man; ++i) {
		residual[SOURCE][i + 1] = 1;
		residual[i + 1][SOURCE] = 0;
		residual[MAXMAN + i + 1][TARGET] = 1;
		residual[TARGET][MAXMAN + i + 1] = 0;
	}

	for (i = 0; i < man; ++i) {
		for (j = 0; j < man; ++j) {
			weight[i + 1][MAXMAN + j + 1] = abs(man_x[i] - home_x[j]) + abs(
					man_y[i] - home_y[j]);
			weight[MAXMAN + j + 1][i + 1] = -weight[i + 1][MAXMAN + j + 1];
			residual[i + 1][MAXMAN + j + 1] = 1;
			residual[MAXMAN + j + 1][i + 1] = 0;
#ifdef DEBUG
			printf("%d %d %d\n", i + 1, MAXMAN + j + 1, weight[i + 1][MAXMAN
					+ j + 1]);
#endif
		}
	}
}

inline int find_flow(int residual[2 * MAXMAN + 2][2 * MAXMAN + 2], int weight[2
		* MAXMAN + 2][2 * MAXMAN + 2], int man, int *parent) {
	int distance[2 * MAXMAN + 2];
	int i, j, k;
	int flag = 1;

	for (i = 0; i < man; ++i) {
		distance[i + 1] = BIGINT;
		distance[MAXMAN + i + 1] = BIGINT;
	}
	distance[0] = 0;
	distance[TARGET] = BIGINT;

	for (i = 0; i < 2 * man + 1 && flag; ++i) {
		flag = 0;

		for (j = 0; j < man; ++j) {
			//SOURCE to NODES
			if (residual[SOURCE][j + 1]) {
				check(SOURCE, j + 1);
			} else {
				check(j + 1, SOURCE);
			}

			//NODES to TARGET
			if (residual[MAXMAN + j + 1][TARGET]) {
				check(MAXMAN + j + 1, TARGET);
			} else {
				check(TARGET, MAXMAN + j + 1);
			}
		}

		for (j = 0; j < man; ++j) {
			for (k = 0; k < man; ++k) {
				if (residual[j + 1][MAXMAN + k + 1]) {
					check(j + 1, MAXMAN + k + 1);
				} else {
					check(MAXMAN + k + 1, j + 1);
				}
			}
		}
	}
	return distance[TARGET];
}

int main(void) {
	int n, m;
	int man;

	int man_x[MAXMAN], man_y[MAXMAN], home_x[MAXMAN], home_y[MAXMAN];
	int weight[2 * MAXMAN + 2][2 * MAXMAN + 2];
	memset(weight, 0, sizeof(weight));
	int residual[2 * MAXMAN + 2][2 * MAXMAN + 2];

	int flow;
	int p;

	int parent[2 * MAXMAN + 2];
	int result;

	while (1) {
		scanf("%d%d", &n, &m);
		if (n == 0) {
			break;
		}

		get_input(n, m, man_x, man_y, home_x, home_y, &man);
		build_graph(man_x, man_y, home_x, home_y, man, weight, residual);

		result = 0;

		for (flow = 0; flow < man; ++flow) {

			result += find_flow(residual, weight, man, parent);

			for (p = TARGET; p != SOURCE; p = parent[p]) {
				residual[parent[p]][p] = 0;
				residual[p][parent[p]] = 1;
			}
		}
		printf("%d\n", result);

	}
	return 0;
}
