/*
 * main.c
 *
 *  Created on: Apr 5, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>

int main(void) {
	char buf[200];
	char city[200];
	int mile, sum;
	char c;

	while (strcmp(gets(buf), "#")) {
		sum = 0;
		for (; strcmp(buf, "0"); gets(buf)) {
			sscanf(buf, "%s %s %d %c", city, city, &mile, &c);
			switch (c) {
			case 'F':
				sum += mile * 2;
				break;
			case 'B':
				sum += (mile + (mile + 1) / 2);
				break;
			case 'Y':
				sum += (mile > 500) ? mile : 500;
			}
		}
		printf("%d\n", sum);
	}
	return 0;
}
