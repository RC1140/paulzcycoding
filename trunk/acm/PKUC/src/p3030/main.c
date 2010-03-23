/*
 * main.c
 *
 *  Created on: Mar 23, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	const char* output[] = {"advertise",
		"does not matter",
		"do not advertise"};
	int n;
	int r, e, c;

	scanf("%d", &n);

	while(n--) {
		scanf("%d%d%d", &r, &e, &c);
		if (e - c > r) {
			printf("%s\n", output[0]);
		} else if (e - c == r) {
			printf("%s\n", output[1]);
		} else {
			printf("%s\n", output[2]);
		}
	}
	return 0;
}
