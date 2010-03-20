/*
 * p1458.c
 *
 *  Created on: Mar 17, 2010
 *      Author: XTOg
 */
#include <stdio.h>
#include <string.h>

#define MAXN 500

int com[MAXN][MAXN];
inline int MAX(int x, int y) {
	if (x > y) return x; else return y;
}

int main(int argc, char* argv[]) {
	char str1[MAXN], str2[MAXN];
	int l1, l2;
	int i, j;

	while (scanf("%s%s", str1, str2) == 2) {
		l1 = strlen(str1);
		l2 = strlen(str2);
		if (str1[0] == str2[0]) {
			com[0][0] = 1;
		} else {
			com[0][0] = 0;
		}

		for (i = 1; i < l1; ++i) {
			if (str1[i] == str2[0]) {
				com[i][0] = 1;
			} else {
				com[i][0] = com[i - 1][0];
			}
		}
		for (j = 1; j < l2; ++j) {
			if (str1[0] == str2[j]) {
				com[0][j] = 1;
			} else {
				com[0][j] = com[0][j - 1];
			}
		}
		for (i = 1; i < l1; ++i) {
			for (j = 1; j < l2; ++j) {
				com[i][j] = MAX(com[i - 1][j], com[i][j - 1]);
				if (str1[i] == str2[j]) {
					com[i][j] = MAX(com[i - 1][j - 1] + 1, com[i][j]);
				}
			}
		}
		printf("%d\n", com[l1 - 1][l2 - 1]);
	}
	return 0;
}
