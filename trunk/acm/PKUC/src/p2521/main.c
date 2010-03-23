#include <stdio.h>

int main(void) {
	int n, m, p, c;
	while (1) {
		scanf("%d%d%d%d", &n, &m, &p, &c);
		if (!(n || m || p || c)) break;
		printf("%d\n", n + -(m + c - p) + c);
	}
	return 0;
}
