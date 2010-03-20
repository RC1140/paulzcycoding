#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {
	const int MAXN = 100;
	int n;
	int i, j, k, l;
	int sum[MAXN + 1][MAXN + 1];
	int max, tmp;

	cin >> n;
	for (i = 0; i <= n; ++i) {
		sum[i][0] = 0;
		sum[0][i] = 0;
	}

	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			cin >> tmp;
			sum[i + 1][j + 1] = sum[i][j + 1] + sum[i + 1][j] - sum[i][j] + tmp;
		}
	}

	max = tmp;

	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			for (k = i + 1; k <= n; ++k) {
				for (l = j + 1; l <= n; ++l) {
					tmp = sum[k][l] - sum[i][l] - sum[k][j] + sum[i][j];
					if (tmp > max) {
						max = tmp;
					}
				}
			}
		}
	}

	cout << max << endl;
	return 0;
}
