/*
 * p1664.c
 *
 *  Created on: Mar 17, 2010
 *      Author: XTOg
 */

#include <stdio.h>

int dfs(int apples, int plates, int max) {
	if (plates == 1) {
		return 1;
	}
	int i;
	int sum = 0;
	for (i = (max < apples)?max:apples; plates * i >= apples; --i) {
		sum += dfs(apples - i, plates - 1, i);
	}
	return sum;
}

int main(int argc, char* argv[]) {
	int t;
	int m, n;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &m, &n);
		printf("%d\n", dfs(m, n, m));
	}
	return 0;
}
