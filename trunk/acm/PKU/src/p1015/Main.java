package p1015;

import java.util.Scanner;

public class Main {
	static final String format = "Jury #%d\n"
			+ "Best jury has value %d for prosecution and value %d for defence:\n";
	static final int MAXPOINT = 20;
	static final int NOBODY = Integer.MIN_VALUE;
	static final int IMPOSSIBLE = Integer.MIN_VALUE;

	static class Info {
		int lastMember;
		int sum;
		static final Info NONE = new Info();

		public Info() {
			lastMember = NOBODY;
			sum = IMPOSSIBLE;
		}

		public Info(int lastMember, int sum) {
			this.lastMember = lastMember;
			this.sum = sum;
		}

		// public Info(Info o) {
		// this.lastMember = o.lastMember;
		// this.sum = o.sum;
		// }
	}

	static int m, n;
	static int[] defence, prosecution;

	static Scanner jin = new Scanner(System.in);
	static Info[][][] info;

	public static void main(String[] args) {
		int cases = 0;

		while (getInput()) {
			info = new Info[n][m][2 * MAXPOINT * m + 2];

			int maxSum = IMPOSSIBLE;
			int p = NOBODY;

			for (int i = 0; p == NOBODY; ++i) {
				Info plus = getBest(n, m, i);
				if (plus.sum > maxSum) {
					maxSum = plus.sum;
					p = i;
				}

				Info minus = getBest(n, m, -i);
				if (minus.sum > maxSum) {
					maxSum = minus.sum;
					p = -i;
				}
			}

			++cases;
			System.out
					.format(format, cases, (maxSum + p) / 2, (maxSum - p) / 2);
			recurseBest(n, m, p);
		}
	}

	private static void recurseBest(int n1, int m1, int diff) {
		int lastMember = info[n1 - 1][m1 - 1][diff + m * MAXPOINT].lastMember;
		if (m1 > 1) {
			recurseBest(lastMember - 1, m1 - 1, diff
					- (prosecution[lastMember - 1] - defence[lastMember - 1]));
		}
		System.out.print(" " + lastMember);
		if (m1 == m) {
			System.out.println();
			System.out.println();
		}
	}

	/**
	 * The best jury with <code>m1</code> members within the first
	 * <code>n1</code> members.
	 * 
	 * @param n1
	 *            The selection is within the first <code>n1</code> members
	 * @param m1
	 *            The selection has <code>m1</code> members
	 * @param diff
	 *            The jury's difference
	 * @return The information of the indicated jury. <br>
	 *         Should return <code>Info.NONE</code> if such jury does not exist.
	 */
	static Info getBest(int n1, int m1, int diff) {
		if (m1 * MAXPOINT < Math.abs(diff))
			return Info.NONE;

		if (info[n1 - 1][m1 - 1][diff + m * MAXPOINT] != null) {
			return info[n1 - 1][m1 - 1][diff + m * MAXPOINT];
		}

		if (m1 == 1) {
			Info temp;

			if (prosecution[n1 - 1] - defence[n1 - 1] == diff) {
				temp = new Info(n1, prosecution[n1 - 1] + defence[n1 - 1]);
			} else {
				temp = Info.NONE;
			}

			if (n1 > 1) {
				Info temp2 = getBest(n1 - 1, 1, diff);
				if (temp2.sum > temp.sum) {
					temp = temp2;
				}
			}

			info[n1 - 1][m1 - 1][diff + m * MAXPOINT] = temp;
		} else {
			Info temp;

			// Include the <code>n1</code> member
			Info temp2 = getBest(n1 - 1, m1 - 1, diff
					- (prosecution[n1 - 1] - defence[n1 - 1]));
			if (temp2.lastMember != NOBODY) {
				temp = new Info(n1, temp2.sum + prosecution[n1 - 1]
						+ defence[n1 - 1]);
			} else {
				temp = Info.NONE;
			}

			// Do not include the <code>n1</code> member
			if (n1 > m1) {
				temp2 = getBest(n1 - 1, m1, diff);
				if (temp2.sum > temp.sum) {
					temp = temp2;
				}
			}

			info[n1 - 1][m1 - 1][diff + m * MAXPOINT] = temp;
		}

		return info[n1 - 1][m1 - 1][diff + m * MAXPOINT];
	}

	static boolean getInput() {
		n = jin.nextInt();
		m = jin.nextInt();

		defence = new int[n];
		prosecution = new int[n];

		for (int i = 0; i < n; ++i) {
			prosecution[i] = jin.nextInt();
			defence[i] = jin.nextInt();
		}

		return n > 0;
	}
}
