package p3740;

import java.util.Arrays;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		final String FOUND = "Yes, I found it";
		final String NOTFOUND = "It is impossible";
		final int[] E = { 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100,
				0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000 };

		final int MAXN = 300;
		final int MAXM = 16;

		int[] matrix = new int[MAXN];
		int[] next = new int[(1 << MAXM) + 1];

		Scanner jin = new Scanner(System.in);

		while (jin.hasNext()) {
			int m = jin.nextInt();
			int n = jin.nextInt();

			Arrays.fill(matrix, 0, n, 0);

			for (int i = 0; i < m; ++i) {
				for (int j = 0; j < n; ++j) {
					matrix[j] |= jin.nextInt() * E[i];
				}
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
				
				if (next[HEAD] == HEAD) break;
			}

			if (k == n) {
				System.out.println(FOUND);
			} else {
				System.out.println(NOTFOUND);
			}
		}
	}

}
