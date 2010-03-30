/*
 * main.c
 *
 *  Created on: Mar 30, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <math.h>

int main() {
	float vs, r, c, w, vr;
	int t;
	scanf("%f%f%f%d", &vs, &r, &c, &t);
	while (t--) {
		scanf("%f", &w);
		vr = c * r * w * vs / sqrt(1 + c * r * w * c * r * w);
		printf("%.3f\n", vr);
	}
	return 0;
}
