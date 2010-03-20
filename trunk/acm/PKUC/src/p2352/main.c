#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	const int MAXN = 15000;
	const int MAXX = 32001;

	int sum[MAXN + 1];
	int tree[MAXX + 1];
	int n;
	int i, j, k;
	int x, y;

	while (scanf("%d", &n) == 1) {
		memset(sum, 0, sizeof(sum));
		memset(tree, 0, sizeof(tree));

		for (i = 0; i < n; ++i) {
			scanf("%d %d", &x, &y);

			k = 0;
			for (j = x + 1; j > 0; j -= (j & -j)) {
				k += tree[j];
			}
			++sum[k];
			for (j = x + 1; j <= MAXX; j += (j & -j)) {
				++tree[j];
			}
		}
		for (i = 0; i < n; ++i) {
			printf("%d\n", sum[i]);
		}
	}

	return 0;
}
