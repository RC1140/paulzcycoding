/*
 * main.c
 *
 *  Created on: Apr 6, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <ctype.h>
int main(void) {
	int n;
	char c;
	int inited;
	char num;
	int count;

	scanf("%d\n", &n);

	while (n--) {
		inited = 0;
		while (isdigit(c = getchar())) {

			if (inited) {

				if (c == num) {
					++count;
				} else {
					printf("%d%c", count, num);
					num = c;
					count = 1;
				}

			} else {
				num = c;
				count = 1;
				inited = 1;
			}

		}
		printf("%d%c\n", count, num);
	}

	return 0;
}
