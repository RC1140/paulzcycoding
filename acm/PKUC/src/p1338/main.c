/*
 * main.c
 *
 *  Created on: Mar 30, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <limits.h>
#define MAXN 1500

int main(void) {
	int ugly[MAXN], t;
	int p = 0;

	int priority_queue[MAXN];
	int queue_size, i, j;

	priority_queue[0] = 1;
	queue_size = 1;

	while (p < MAXN) {
		t = priority_queue[0];
		for (i = 1; i < queue_size; ++i) {
			priority_queue[i - 1] = priority_queue[i];
		}
		--queue_size;

		ugly[p++] = t;

#define insert(num) \
	for (i = 0; i < queue_size && priority_queue[i] < (num); ++i) {\
	}\
	if (i == queue_size) {\
		priority_queue[queue_size] = (num);\
		++queue_size;\
	} else if (priority_queue[i] > (num)) {\
		for (j = queue_size; j > i; --j) {\
			priority_queue[j] = priority_queue[j - 1];\
		}\
		++queue_size;\
		priority_queue[i] = (num);\
	}

		if (t <= INT_MAX / 2) insert(t * 2);
		if (t <= INT_MAX / 3) insert(t * 3);
		if (t <= INT_MAX / 5) insert(t * 5);
//		printf("%d %d\n", p, t);
	}

	for (scanf("%d", &p); p; scanf("%d", &p)) {
		printf("%d\n", ugly[p - 1]);
	}
	return 0;
}
