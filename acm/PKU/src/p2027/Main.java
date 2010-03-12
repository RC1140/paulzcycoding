package p2027;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		final String[] RESULT = { "NO BRAINS", "MMM BRAINS" };

		Scanner jin = new Scanner(System.in);

		int t = jin.nextInt();
		while (t-- > 0) {
			int m = jin.nextInt();
			int n = jin.nextInt();
			if (m < n) {
				System.out.println(RESULT[0]);
			} else {
				System.out.println(RESULT[1]);
			}
		}
	}
}
