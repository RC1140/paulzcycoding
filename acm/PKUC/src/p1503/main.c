/*
 * p1503.c
 *
 *  Created on: Mar 19, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>

#define MAXN 103
inline int max(int a, int b) {
	return (a > b)?a:b;
}

int main(void) {
	int result[MAXN];
	char buf[MAXN];
	int e, i, len;

	e = 0;
	memset(result, 0, sizeof(result));

	scanf("%s", buf);

	while (strcmp(buf, "0")) {
		len = strlen(buf);
		for (i = 0; i < len; ++i) {
			result[i] += (buf[len - 1 - i] - '0');
			if (result[i] >= 10) {
				++result[i + 1];
				result[i] -= 10;
			}
		}
		e = max(len, e) + 1;
		while (!result[e]) --e;
		scanf("%s", buf);
	}

	while (e >= 0) {
		printf("%d", result[e--]);
	}
	printf("\n");
	return 0;
}
