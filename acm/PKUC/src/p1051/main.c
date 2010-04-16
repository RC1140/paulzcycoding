/*
 * main.c
 *
 *  Created on: Apr 15, 2010
 *      Author: XTOg
 */

#include <stdio.h>
#include <string.h>

#define MAXN 100

const char *morse[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
		"....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
		".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
		"..--", ".-.-", "---.", "----" };
const int len[] = { 2, 4, 4, 3, 1, 4, 3, 4, 2, 4, 3, 4, 2, 2, 3, 4, 4, 3, 3, 1,
		3, 4, 3, 4, 4, 4, 4, 4, 4, 4 };

int char2int(char c) {
	switch (c) {
	case '_':
		return 26;
	case ',':
		return 27;
	case '.':
		return 28;
	case '?':
		return 29;
	default:
		return c - 'A';
	}
}

int int2char(int n) {
	switch (n) {
	case 26:
		return '_';
	case 27:
		return ',';
	case 28:
		return '.';
	case 29:
		return '?';
	default:
		return 'A' + n;
	}
}

char get_char(char *s, int l) {
	int i, j;
	for (i = 0; i < 30; ++i) {
		if (len[i] != l) {
			continue;
		}
		for (j = 0; j < l; ++j) {
			if (s[j] != morse[i][j]) {
				break;
			}
		}
		if (j == l) {
			break;
		}
	}
	return int2char(i);
}

int main(void) {
	int n;
	char buf[MAXN + 1];
	char code[4 * MAXN + 1];
	int p;
	int l;
	int i, j;

	scanf("%d\n", &n);
	for (i = 1; i <= n; ++i) {
		gets(buf);
		l = strlen(buf);
		p = 0;
		printf("%d: ", i);
		for (j = 0; j < l; ++j) {
			strcpy(code + p, morse[char2int(buf[j])]);
			p += len[char2int(buf[j])];
		}

		p = 0;
		for (j = l - 1; j >= 0; --j) {
			putchar(get_char(code + p, len[char2int(buf[j])]));
			p += len[char2int(buf[j])];
		}
		putchar('\n');
	}

	return 0;
}
