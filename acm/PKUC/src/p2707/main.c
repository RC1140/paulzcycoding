/*
 * main.c
 *
 *  Created on: Apr 6, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int min(int a, int b) {
	return (a < b) ? a : b;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int main(void) {
	int w1, h1, w2, h2;
	while (1) {
		scanf("%d%d%d%d", &w1, &h1, &w2, &h2);
		if (!w1) {
			break;
		}
		printf("%d%%\n", min(max(min(w2 * 100 / w1, h2 * 100 / h1), min(w2 * 100
				/ h1, h2 * 100 / w1)), 100));
	}
	return 0;
}
