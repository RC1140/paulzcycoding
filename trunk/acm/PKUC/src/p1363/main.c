/*
 * main.c
 *
 *  Created on: Apr 15, 2010
 *      Author: XTOg
 */

#include <stdio.h>

#define MAXN 1000

int main(void) {
	int n;
	int i;
	int stack[MAXN];
	int head;
	int next;
	int p;
	int possible;

	while (1) {
		scanf("%d", &n);

		if (!n) {
			break;
		}

		while (1) {
			scanf("%d", &p);
			if (!p) {
				break;
			}
			next = 1;
			head = 0;
			while (next <= p) {
				stack[head++] = next++;
			}
			--head;

			possible = 1;
			for (i = 1; i < n; ++i) {
				scanf("%d", &p);
				if (!possible) {
					continue;
				}
				if (stack[head - 1] == p) {
					--head;
				} else if (next <= p) {
					while (p >= next) {
						stack[head++] = next++;
					}
					--head;
				} else {
					possible = 0;
				}
			}

			if (possible) {
				printf("Yes\n");
			} else {
				printf("No\n");
			}
		}
		printf("\n");

	}
	return 0;
}
