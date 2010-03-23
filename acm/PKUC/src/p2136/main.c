#include <stdio.h>
#include <string.h>

#define MAXN 100

int main(void) {
	char buf[MAXN];
	int num[26];
	int i, j, k;
	int max;
	char *c;
	memset(num, 0, sizeof(num));

	for (i = 0; i < 4; ++i) {
		gets(buf);

		for (c = buf; *c; ++c) {
			if ('A' <= *c && *c <= 'Z') {
				++num[*c - 'A'];
			}
		}
	}

	max = 0;
	for (i = 0; i < 26; ++i) {
		if (num[i] > max) {
			max = num[i];
		}
	}

	for (i = 0; i < max; ++i) {
		for (k = 25; k >= 0 && num[k] < max - i; --k) ;
		for (j = 0; j < k; ++j) {
			if (num[j] >= max - i) {
				printf("* ");
			} else {
				printf("  ");
			}
		}
		printf("*\n");
	}

	for (i = 0; i < 25; ++i) {
		printf("%c ", 'A' + i);
	}
	printf("%c\n", 'A' + i);
	return 0;
}
