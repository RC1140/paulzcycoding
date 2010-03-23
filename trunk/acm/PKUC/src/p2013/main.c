/*
 * main.c
 *
 *  Created on: Mar 23, 2010
 *      Author: XTOg
 */

#include <stdio.h>

void stack(int n) {
	char buf[26];
	if (n == 0) {
		return;
	}
	scanf("%s", buf);
	printf("%s\n", buf);
	if (n == 1) {
		return;
	}
	scanf("%s", buf);
	stack(n - 2);
	printf("%s\n", buf);
}

int main(void) {
	int n;
	int c = 0;

	while (1) {
		scanf("%d", &n);
		if (!n) break;

		printf("SET %d\n", ++c);
		stack(n);
	}
	return 0;
}
