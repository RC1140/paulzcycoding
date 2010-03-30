/*
 * main.c
 *
 *  Created on: Mar 29, 2010
 *      Author: XTOg
 */

#include <stdio.h>

#define MAXN 20

int main(void) {
	int t;
	int n;

	int stack[MAXN + 1];
	int top;
	int p, prev;

	scanf("%d", &t);

	while (t--) {
		scanf("%d", &n);
		stack[0] = 0;
		top = 0;
		prev = 0;

		while (n--) {
			scanf("%d", &p);
			for (; prev < p; ++prev) {
				stack[++top] = 1;
			}
			printf("%d ", stack[top--]);
			stack[top] += stack[top + 1];
		}
		printf("\n");
	}

	return 0;
}
