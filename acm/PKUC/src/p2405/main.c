/*
 * main.c
 *
 *  Created on: Apr 6, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <math.h>
#define PI 3.1415926535897932384626f

int main(void) {
	float D, V;
	while (1) {
		scanf("%f%f", &D, &V);
		if (D == 0.f) {
			break;
		}
		printf("%.3f\n", pow(D * D * D - V / (PI / 4.f - PI / 12.f), 1.f / 3.f));
	}
	return 0;
}
