package p1014;

import java.util.Scanner;

public class Main {
	static final int MARBLES = 6;

	static int sum;
	static int[] n = new int[MARBLES];

	static Scanner jin;

	public static void main(String[] args) {
		jin = new Scanner(System.in);

		final String[] format = {
				"Collection #%d:\n" + "Can't be divided.\n\n",
				"Collection #%d:\n" + "Can be divided.\n\n" };

		int cases = 0;

		while (getInput()) {
			int result = 0;
			if (sum % 2 == 0) {
				if (n[0] >= 5) {
					result = 1;
				} else {
					result = dfs(MARBLES, sum / 2);
				}
			} else {
				result = 0;
			}

			++cases;
			System.out.format(format[result], cases);
		}
	}

	private static boolean getInput() {
		sum = 0;
		boolean notAllZero = false;
		final int[][] R = { { 0, 0 }, { 4, 3 }, { 8, 7 }, { 8, 7 }, { 12, 11 },
				{ 8, 7 } };
		final int[] THRESHOLD = { 100000, 4, 8, 8, 12, 8 };

		for (int i = 0; i < MARBLES; ++i) {
			n[i] = jin.nextInt();
			if (n[i] > 0)
				notAllZero = true;

			/*
			 * See <a href =
			 * "http://acm.pku.edu.cn/JudgeOnline/showmessage?message_id=23416">
			 * http://acm.pku.edu.cn/JudgeOnline/showmessage?message_id=23416
			 * </a>
			 */
			if (i > 0 && n[i] >= THRESHOLD[i])
				n[i] = R[i][n[i] % 2];
			sum += n[i] * (i + 1);
		}

		return notAllZero;
	}

	static int dfs(int marble, int remain) {
		if (marble == 1) {
			return (n[0] >= remain) ? 1 : 0;
		}

		for (int i = Math.min(n[marble - 1], remain / marble); i >= 0; --i) {
			if (dfs(marble - 1, remain - marble * i) == 1)
				return 1;
		}

		return 0;
	}
}
