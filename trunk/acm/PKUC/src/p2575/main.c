/*
 * main.c
 *
 *  Created on: Mar 26, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	int n;
	int jolly[3000];
	int i;
	int prev, diff, t;
	int flag;

	while (scanf("%d", &n) != EOF) {
		memset(jolly, 0, sizeof(jolly));
		scanf("%d", &prev);
		flag = 0;

		for (i = 1; i < n; ++i) {
			scanf("%d", &t);
			if (flag) continue;

			diff = abs(t - prev);
			if (diff <= 0 || diff >= n) {
				flag = 1;
				continue;
			}

			if (jolly[diff]) {
				flag = 1;
				continue;
			}

			jolly[diff] = 1;
			prev = t;
		}

		if (flag) {
			printf("Not jolly\n");
		} else {
			printf("Jolly\n");
		}
	}
	return 0;

}
