#include <iostream>

using namespace std;

const char FOUND[] = "Yes, I found it";
const char NOTFOUND[] = "It is impossible";
const int E[] = { 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200,
		0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000 };

const int MAXN = 300;
const int MAXM = 16;

int matrix[MAXN];
int next[(1 << MAXM) + 1];

inline int countOnes(int i) {
	int result = 0;
	while (i > 0) {
		result += i % 2;
		i = i / 2;
	}
	return result;
}

int main(int argc, char* argv[]) {

	int m, n;
	while (cin >> m >> n) {

		for (int i = 0; i < n; ++i) {
			matrix[i] = 0;
		}

		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				int t;
				cin >> t;
				matrix[j] |= t * E[i];
			}
		}

		for (int i = 0; i < n; ++i) {
			int p = i;
			int min = countOnes(matrix[i]);
			for (int j = i + 1; j < n; ++j) {
				if (countOnes(matrix[j]) < min) {
					p = j;
					min = countOnes(matrix[j]);
				}
			}
			int tmp = matrix[p];
			matrix[p] = matrix[i];
			matrix[i] = tmp;
		}

		int HEAD = 1 << m;

		for (int i = 0; i < HEAD; ++i) {
			next[i] = i + 1;
		}
		next[HEAD] = 0;

		int k;
		for (k = 0; k < n; ++k) {
			int p = HEAD;
			int q = next[p];

			while (q != HEAD) {
				int x = q & matrix[k];
				if (x > 0 && (x & (x - 1)) == 0) {
					p = q;
				} else {
					next[p] = next[q];
				}
				q = next[p];
			}

			if (HEAD == next[HEAD]) {
				break;
			}
		}

		if (k == n) {
			cout << FOUND << endl;
		} else {
			cout << NOTFOUND << endl;
		}
	}
	return 0;
}
