/*
 * p2017.c
 *
 *  Created on: Mar 17, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(int argc, char* argv[]) {
	int n, s, t, t1;;
	int i;
	int sum;

	scanf("%d", &n);
	while (n != -1) {
		sum = 0;
		t1 = 0;
		for (i = 0; i < n; ++i) {
			scanf("%d %d", &s, &t);
			sum += s * (t - t1);
			t1 = t;
		}
		printf("%d miles\n", sum);
		scanf("%d", &n);
	}
	return 0;
}
