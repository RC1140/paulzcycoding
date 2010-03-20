#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int i, j, i1, j1;
	int p, q;
	int n, maxn;
	while (scanf("%d %d", &i, &j) == 2) {
		maxn = 0;
		if (i > j) {
			i1 = j;
			j1 = i;
		} else {
			i1 = i;
			j1 = j;
		}

		for (p = i1; p <= j1; ++p) {
			for (q = p, n = 1; q != 1; ++n) {
				if (q % 2) {
					q = 3 * q + 1;
				} else {
					q >>= 1;
				}
			}
			if (n > maxn) {
				maxn = n;
			}
		}
		printf("%d %d %d\n", i, j, maxn);
	}

	return EXIT_SUCCESS;
}
