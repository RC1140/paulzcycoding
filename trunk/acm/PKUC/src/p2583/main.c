/*
 * main.c
 *
 *  Created on: Mar 25, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int f0, f1, f2;
	while (scanf("%d%d%d", &f0, &f1, &f2) == 3) {
		printf("%d %d %d\n",
				f0 - 3 * f1 + 3 * f2,
				3 * f0 - 8 * f1 + 6 * f2,
				6 * f0 - 15 * f1 + 10 * f2);
	}
	return 0;
}
