/*
 * p2301.c
 *
 *  Created on: Mar 17, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int main(int argc, char* argv[]) {
	int t;
	int s, d;

	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &s, &d);
		if (s < d || (s - d) % 2) {
			printf("impossible\n");
		} else {
			printf("%d %d\n", (s + d) / 2, (s - d) / 2);
		}
	}

	return 0;
}
