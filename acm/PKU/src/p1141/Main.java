package p1141;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);

		char[] input = jin.nextLine().toCharArray();
		int length = input.length;
		if (length == 0) {
			System.out.println();
			return;
		}

		StringBuffer[][] p = new StringBuffer[length][length];
		for (int i = 0; i < length; ++i) {
			p[i][i] = new StringBuffer(
					(input[i] == '(' || input[i] == ')') ? "()" : "[]");
		}
		
		for (int l = 2; l <= length; ++l) {
			for (int i = 0; i + l - 1 < length; ++i) {
				int j = i + l - 1;

				p[i][j] = new StringBuffer();
				int min = Integer.MAX_VALUE;

				if ((input[i] == '(' && input[j] == ')')
						|| (input[i] == '[' && input[j] == ']')) {

					p[i][j].append(input[i]);
					if (i + 1 <= j - 1) {
						p[i][j].append(p[i + 1][j - 1]);
					}
					p[i][j].append(input[j]);
					min = p[i][j].length();
				}

				int t = -1;
				for (int k = i; k + 1 <= j; ++k) {
					if (p[i][k].length() + p[k + 1][j].length() < min) {
						t = k;
						min = p[i][k].length() + p[k + 1][j].length();
					}
				}

				if (t != -1) {
					p[i][j].delete(0, p[i][j].length());
					p[i][j].append(p[i][t]);
					p[i][j].append(p[t + 1][j]);
				}
			}
		}

		System.out.println(p[0][length - 1]);
	}
}
