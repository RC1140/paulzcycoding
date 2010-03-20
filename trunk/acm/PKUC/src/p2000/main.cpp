#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	const int MAXN = 10000;
	int sum[MAXN + 1];
	int i, j, p = 0;
	sum[0] = 0;
	for (i = 1; p <= MAXN; ++i) {
		for (j = 1; p <= MAXN && j <= i; ++j) {
			sum[p + 1]= sum[p] + i;
			++p;
		}
	}

	int n;
	cin >> n;
	while (n != 0) {
		cout << n << ' ' << sum[n] << endl;
		cin >> n;
	}
	return 0;
}
