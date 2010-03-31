/*
 * main.c
 *
 *  Created on: Mar 31, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>

#define MAXN 100
typedef enum {
	WHITE = 0, BLACK
} color;

int main(void) {
	color board[MAXN][MAXN];
	char buf[6];
	int n;
	int x, y, l;
	int i, j;
	int sum;
	memset(board, 0, sizeof(board));

	scanf("%d", &n);
	while (n--) {
		scanf("%s%d%d%d", buf, &x, &y, &l);
		if (strcmp(buf, "WHITE") == 0) {
			for (i = 0; i < l; ++i) {
				for (j = 0; j < l; ++j) {
					board[x - 1 + i][y - 1 + j] = WHITE;
				}
			}
		} else if (strcmp(buf, "BLACK") == 0) {
			for (i = 0; i < l; ++i) {
				for (j = 0; j < l; ++j) {
					board[x - 1 + i][y - 1 + j] = BLACK;
				}
			}
		} else {
			sum = 0;
			for (i = 0; i < l; ++i) {
				for (j = 0; j < l; ++j) {
					if (board[x - 1 + i][y - 1 + j] == BLACK) {
						++sum;
					}
				}
			}
			printf("%d\n", sum);
		}

	}

	return 0;
}
