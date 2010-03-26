/*
 * main.c
 *
 *  Created on: Mar 25, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#define SUM(a) (a[0] + a[1] + a[2] + a[3])
#define CHECK(a, b) \
	for (j = 0; j < 4; ++j) {\
		if (a[j] >= b) {\
			++a[j + 1];\
			a[j] -= b;\
		}\
	}

int main(void) {
	int dec[] = { 0, 0, 0, 1 }, hex[] = { 8, 14, 3, 0 },
			duo[] = { 4, 11, 6, 0 };
	int i, j;
	for (i = 1000; i <= 9999; ++i) {
		if (SUM(dec) == SUM(hex) && SUM(hex) == SUM(duo)) {
			printf("%d%d%d%d\n", dec[3], dec[2], dec[1], dec[0]);
		}
		++dec[0];
		++hex[0];
		++duo[0];

		CHECK(dec, 10);
		CHECK(hex, 16);
		CHECK(duo, 12);
	}
	return 0;
}
