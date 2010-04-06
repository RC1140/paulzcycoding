/*
 * main.c
 *
 *  Created on: Apr 6, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(void) {
	float t1, t2;
	scanf("%f", &t1);
	while (1) {
		scanf("%f", &t2);
		if (t2 > 300) {
			break;
		}
		printf("%.2f\n", t2 - t1);
		t1 = t2;
	}
	printf("End of Output\n");
	return 0;
}
