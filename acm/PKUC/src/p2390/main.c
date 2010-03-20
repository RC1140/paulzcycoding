/*
 * p2390.c
 *
 *  Created on: Mar 17, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
	int r, m, y;
	int i;
	double result;
	double interest;

	scanf("%d%d%d", &r, &m, &y);
	result = m;
	interest = 1. + (double)r / 100;

	for (i = 0; i < y; ++i) {
		result = result * interest;
	}

	printf("%d\n", (int)result);
	return 0;
}
