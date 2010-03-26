/*
 * main.c
 *
 *  Created on: Mar 25, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <math.h>
#define PI 3.1415926535897932384626
int main(void) {
	int n, m;
	double t, R, num;

	scanf("%d", &n);
	for (m = 1; m <= n; ++m) {
		scanf("%lf%lf", &R, &num);

		t = sin(PI / num);

		printf("Scenario #%d:\n", m);
		printf("%.3f\n\n", R * t / (1 + t));
	}
	return 0;
}
