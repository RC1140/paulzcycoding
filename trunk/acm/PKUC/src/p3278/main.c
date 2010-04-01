/*
 * main.c
 *
 *  Created on: Apr 1, 2010
 *      Author: XTOg
 */

#include <stdio.h>

#define MAXN 100000
#define FLAG -1

int main(void) {
	int n, k;
	int depth;
	int queue[MAXN + 1];
	int head = 0, tail = 0;
#define push(num, depth) if (visited[num] == FLAG) {visited[num] = (depth);queue[tail++] = (num);}
#define pop(num, depth) if (1) {num = queue[head++];depth = visited[num];}
	int visited[MAXN + 1];

	for (n = 0; n <= MAXN; ++n) {
		visited[n] = FLAG;
	}

	scanf("%d%d", &n, &k);
	push(n, 0);

	while (1) {
		pop(n, depth);
		if (n == k) {
			printf("%d\n", depth);
			break;
		}
		if (n > 0) {
			push(n - 1, depth + 1);
		}
		if (n < MAXN) {
			push(n + 1, depth + 1);
		}
		if ((n << 1) <= MAXN) {
			push(n << 1, depth + 1);
		}
	}

	return 0;
}
