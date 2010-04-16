/*
 * main.c
 *
 *  Created on: Apr 6, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	char num1[5], num2[5];
	int n;
	int i, j;
	int a, b;

	scanf("%d", &n);
	while (n--) {
		scanf("%s %s", num1, num2);
		a = 0;
		b = 0;
		for (i = 0; i < 4; ++i) {
			for (j = 0; j < 4; ++j) {
				if (num1[i] == num2[j]) {
					if (i == j) {
						++a;
					} else {
						++b;
					}
				}
			}
		}
		printf("%dA%dB\n", a, b);

	}
	return 0;
}
