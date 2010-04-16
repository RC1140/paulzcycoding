/*
 * main.c
 *
 *  Created on: Apr 12, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>

#define MAXN 200
#define MAXK 33

int main(void) {
	int n;
	int p[MAXK][MAXN];
	int k;
	char buf[MAXN + 1], buf2[MAXN + 1], *p1, *p2, *t;
	char space;
	int i, j;

	while (1) {
		scanf("%d", &n);
		if (!n) {
			break;
		}

		for (i = 0; i < n; ++i) {
			scanf("%d", &p[0][i]);
			--p[0][i];
		}

		for (i = 1; i < MAXK; ++i) {
			for (j = 0; j < n; ++j) {
				p[i][j] = p[i - 1][p[i - 1][j]];
			}
		}

		while (1) {
			scanf("%d%c", &k, &space);
			if (!k) {
				break;
			}
			gets(buf);

			for (i = strlen(buf); i < n; ++i) {
				buf[i] = ' ';
			}
			buf[n] = '\0';
			buf2[n] = '\0';
			p1 = buf;
			p2 = buf2;

			for (i = 0; k; k /= 2, ++i) {
				if (k % 2) {
					for (j = 0; j < n; ++j) {
						p2[p[i][j]] = p1[j];
					}
					t = p1;
					p1 = p2;
					p2 = t;
				}
			}

			printf("%s\n", p1);
		}
		printf("\n");
	}

	return 0;
}
