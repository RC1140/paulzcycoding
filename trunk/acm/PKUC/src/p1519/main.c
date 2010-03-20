/*
 * p1519.c
 *
 *  Created on: Mar 17, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char dig[1000];
	int i, j;
	scanf("%s", dig);

	while (strcmp(dig, "0")) {
		j = 0;
		for (i = 0; i < strlen(dig); ++i) {
			j += dig[i] - '0';
		}
		j %= 9;
		if (j == 0) j = 9;

		printf("%d\n", j);
		scanf("%s", dig);
	}
	return 0;
}
