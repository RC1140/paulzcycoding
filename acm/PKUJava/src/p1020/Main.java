package p1020;

import java.util.Scanner;

public class Main {
	static final int MAX_CAKES = 10;
	static final String[] RESULT = { "HUTUTU!", "KHOOOOB!" };

	static int s;
	static int[] cakes;
	static boolean[][] occupied;

	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);

		int t = jin.nextInt();
		while (t-- > 0) {
			s = jin.nextInt();
			int area = s * s;

			int n = jin.nextInt();
			cakes = new int[MAX_CAKES];
			int maxCakeSize = 0;

			while (n-- > 0) {
				int size = jin.nextInt();
				if (size > maxCakeSize) {
					maxCakeSize = size;
				}
				++cakes[size - 1];
				area -= size * size;
			}

			if (area != 0) {
				System.out.println(RESULT[0]);
				continue;
			}

			occupied = new boolean[s][s];
			System.out.println(RESULT[dfs(0, 0)]);
		}
	}

	static int dfs(int x, int y) {
		for (int i = 0; i < 10 && y + i < s && x + i < s && !occupied[x + i][y]; ++i) {
			if (cakes[i] > 0) {
				--cakes[i];
				for (int m = x; m < x + i + 1; ++m) {
					for (int n = y; n < y + i + 1; ++n) {
						occupied[m][n] = true;
					}
				}

				int x0 = x;
				int y0 = y;

				while (y0 < s && occupied[x0][y0]) {
					y0 = y0 + (x0 + 1) / s;
					x0 = (x0 + 1) % s;
				}
				
				if (y0 == s) {
					return 1;
				} else if (dfs(x0, y0) == 1) {
					return 1;
				}

				for (int m = x; m < x + i + 1; ++m) {
					for (int n = y; n < y + i + 1; ++n) {
						occupied[m][n] = false;
					}
				}
				++cakes[i];
			}
		}
		return 0;
	}
}
