/*
 * main.c
 *
 *  Created on: Apr 6, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	char buf[11];
	int p, i;
	int sum = 0;
	gets(buf);

	for (i = 10; i > 1; --i) {
		if (buf[10 - i] == '?') {
			p = i;
		} else {
			sum += i * (buf[10 - i] - '0');
		}
	}

	switch (buf[9]) {
	case '?':
		p = (11 - sum % 11) % 11;
		printf("%c\n", (p == 10) ? 'X' : ('0' + p));
		return 0;
		break;
	case 'X':
		sum += 10;
		break;
	default:
		sum += buf[9] - '0';
	}

	for (i = 0; i < 10; ++i) {
		if ((p * i + sum) % 11 == 0) {
			printf("%c\n", '0' + i);
			return 0;
		}
	}
	printf("-1\n");

	return 0;
}
