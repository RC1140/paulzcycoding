/*
 * p2549.c
 *
 *  Created on: Mar 17, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

struct sum_t {
	int sum;
	int a, b;
};

int compare(const void *a, const void *b) {
	return (*(int*) a - *(int*) b);
}

int compare2(const void *a, const void *b) {
	return ((struct sum_t *) a)->sum - ((struct sum_t *) b)->sum;
}

struct sum_t sum[MAXN * (MAXN - 1) / 2 + 1];

int main(int argc, char* argv[]) {
	int n;
	int num[MAXN];
	int i, j, k;
	int flag;
	struct sum_t *p;
	struct sum_t key;

	scanf("%d", &n);
	while (n) {
		for (i = 0; i < n; ++i) {
			scanf("%d", num + i);
		}

		qsort(num, n, sizeof(int), compare);

		flag = 0;
		k = 0;
		for (i = 0; i < n; ++i) {
			for (j = i + 1; j < n; ++j) {
				sum[k].a = num[i];
				sum[k].b = num[j];
				sum[k].sum = num[i] + num[j];
				++k;
			}
		}
		qsort(sum, n * (n - 1) / 2, sizeof(struct sum_t), compare2);
		sum[n * (n - 1) / 2].sum = 2147483647;

		for (i = n - 1; i >= 0; --i) {
			for (j = 0; j < n; ++j) {
				if (i == j)
					continue;
				key.sum = num[i] - num[j];
				p = (struct sum_t *) bsearch(&key, sum, n * (n - 1) / 2,
						sizeof(struct sum_t), compare2);
				if (p == NULL)
					continue;
				while (p->sum == key.sum) {
					if (p->a != num[i] && p->b != num[i] && p->a != num[j] && p->b != num[j]) {
						printf("%d\n", num[i]);
						flag = 1;
						break;
					}
					++p;
				}
				if (flag) break;
			}
			if (flag) break;
		}

		if (!flag) {
			printf("no solution\n");
		}

		scanf("%d", &n);
	}
	return 0;
}
