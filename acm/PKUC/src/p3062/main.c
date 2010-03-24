/*
 * main.c
 *
 *  Created on: Mar 23, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	char buf[255];
	while (gets(buf)) {
		puts(buf);
	}
	return 0;
}
