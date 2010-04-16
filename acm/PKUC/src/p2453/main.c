/*
 * main.c
 *
 *  Created on: Apr 11, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	int i;
	int f, e;
	while (1) {
		scanf("%d", &i);
		if (!i) {
			break;
		}
		e = 1;
		while (! (i & e)) {
			e <<= 1;
		}
		i -= e;
		e <<= 1;
		f = 1;
		while (i & e) {
			i -= e;
			i += f;
			e <<= 1;
			f <<= 1;
		}
		i += e;
		printf("%d\n", i);
	}
	return 0;
}
