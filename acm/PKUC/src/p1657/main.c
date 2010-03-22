/*
 * main.c
 *
 *  Created on: Mar 22, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <stdlib.h>

inline int max(int a, int b) {
	return (a > b)?a:b;
}

int main(void) {
	int c;
	char pos[2][3];
	int x1, x2, y1, y2;
	int dx, dy;
	scanf("%d", &c);


	while (c--) {
		scanf("%s%s", pos[0], pos[1]);
		x1 = pos[0][0] - 'a';
		y1 = pos[0][1] - '1';
		x2 = pos[1][0] - 'a';
		y2 = pos[1][1] - '1';

		dx = abs(x1 - x2);
		dy = abs(y1 - y2);

		if (!(dx || dy)) {
			printf("0 0 0 0\n");
			continue;
		}

		printf("%d", max(dx, dy));
		printf(" %d", (dx && dy && dx != dy)?2:1);
		printf(" %d", (dx && dy)?2:1);
		if ((dx - dy) % 2) {
			printf(" Inf\n");
		} else {
			printf(" %d\n", (dx == dy)?1:2);
		}
	}
	return 0;
}
