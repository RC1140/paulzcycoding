package p1011;

import java.util.Scanner;

public class Main {
	static final int MAXSTICKS = 100;

	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);

		int n = jin.nextInt();

		while (n > 0) {

			int totalLength = 0;

			sticks = 0;

			for (int i = 0; i < n; ++i) {
				int l = jin.nextInt();
				totalLength += l;

				int j;
				for (j = 0; j < sticks; ++j) {
					if (length[j] == l) {
						++number[j];
						break;
					} else if (length[j] < l) {
						for (int k = sticks; k > j; --k) {
							length[k] = length[k - 1];
							number[k] = number[k - 1];
						}
						length[j] = l;
						number[j] = 1;
						++sticks;
						break;
					}
				}
				if (j == sticks) {
					length[j] = l;
					number[j] = 1;
					++sticks;
				}

			}

			for (basketLength = length[0];; ++basketLength) {
				if (totalLength % basketLength != 0)
					continue;

				baskets = totalLength / basketLength;
				filled = new int[baskets];
				solution = new int[baskets][sticks];

				possible = new boolean[basketLength + 1][sticks];

				for (int i = 0; i <= number[sticks - 1]
						&& i * length[sticks - 1] <= basketLength; ++i) {
					possible[i * length[sticks - 1]][sticks - 1] = true;
				}

				for (int i = sticks - 2; i >= 0; --i) {
					for (int j = 0; j <= number[i]; ++j) {
						for (int k = 0; k <= basketLength; ++k)
							if (k - j * length[i] >= 0
									&& possible[k - j * length[i]][i + 1])
								possible[k][i] = true;
					}
				}

				if (dfsByStick(0, 0)) {
					System.out.println(basketLength);
					break;
				}
			}

			n = jin.nextInt();
		}
	}

	static int sticks;
	static int[] length = new int[MAXSTICKS];
	static int[] number = new int[MAXSTICKS];

	static int baskets;
	static int basketLength;
	static int[] filled;
	static int[][] solution;
	static boolean[][] possible;

	static boolean dfsByStick(int stick, int basket) {

		if (stick + 1 == sticks) {
			for (int i = 0; i < baskets; ++i) {
				if ((basketLength - filled[i]) % length[stick] != 0)
					return false;
			}
			return true;
		}

		int max = Math.min(number[stick], (basketLength - filled[basket])
				/ length[stick]);
		if (basket > 0 && solution[basket - 1][stick] < max) {
			int j = 0;
			while (j < stick && solution[basket - 1][j] == solution[basket][j])
				++j;
			if (j == stick) {
				max = solution[basket - 1][stick];
			}
		}

		int min = 0;
		if (stick == 0)
			min = (number[0] + baskets - 1) / baskets;
		if (basketLength - filled[basket] == length[stick] && number[stick] > 0)
			min = 1;

		for (int i = max; i >= min; --i) {
			solution[basket][stick] = i;
			number[stick] -= i;
			filled[basket] += i * length[stick];

			if (possible[basketLength - filled[basket]][stick + 1]) {
				if (number[stick] == 0) {
					boolean result = dfsByStick(stick + 1, 0);
					if (result)
						return true;
				} else if (basket + 1 < baskets) {
					boolean result = dfsByStick(stick, basket + 1);
					if (result)
						return true;
				}
			}

			filled[basket] -= i * length[stick];
			number[stick] += i;
			solution[basket][stick] = 0;
		}

		return false;
	}
}
