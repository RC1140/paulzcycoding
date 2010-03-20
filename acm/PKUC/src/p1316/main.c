/*
 * p1316.c
 *
 *  Created on: Mar 17, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(int argc, char* argv[]) {
	int MAX = 10000;
	int self[MAX + 1];
	int i, j, sum;

	for (i = 1; i <= MAX; ++i) {
		self[i] = 1;
	}

	for (i = 1; i < MAX; ++i) {
		sum = i;
		for (j = i; j; j /= 10) {
			sum += j % 10;
		}
		if (sum <= MAX) {
			self[sum] = 0;
		}
	}

	for (i = 1; i <= MAX; ++i) {
		if (self[i]) {
			printf("%d\n", i);
		}
	}

	return 0;
}
