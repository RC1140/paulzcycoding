/*
 * main.c
 *
 *  Created on: Mar 22, 2010
 *      Author: XTOg
 */

#include <stdio.h>

#define MAXN 1000

int main(void) {
	int c;
	int n;
	int num[MAXN];
	double sum, ave;
	int above;
	int i;

	scanf("%d", &c);
	while (c--) {
		scanf("%d", &n);
		sum = 0;
		for (i = 0; i < n; ++i) {
			scanf("%d", &num[i]);
			sum += num[i];
		}
		ave = sum / n;
		above = 0;
		for (i = 0; i < n; ++i) {
			if (ave < num[i]) {
				++above;
			}
		}
		printf("%.3f%%\n", (double)above * 100 / n);
	}
	return 0;
}
