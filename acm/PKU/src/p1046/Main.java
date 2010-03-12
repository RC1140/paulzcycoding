package p1046;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);

		String FORMAT = "(%d,%d,%d) maps to (%d,%d,%d)\n";

		int[] R, G, B;
		R = new int[16];
		G = new int[16];
		B = new int[16];

		for (int i = 0; i < 16; ++i) {
			R[i] = jin.nextInt();
			G[i] = jin.nextInt();
			B[i] = jin.nextInt();
		}

		int r, g, b;
		r = jin.nextInt();
		g = jin.nextInt();
		b = jin.nextInt();
		while (r != -1) {
			int diff = Integer.MAX_VALUE;
			int p = 0;
			for (int i = 0; i < 16; ++i) {
				int t = (r - R[i]) * (r - R[i]) + (g - G[i]) * (g - G[i])
						+ (b - B[i]) * (b - B[i]);
				if (t < diff) {
					diff = t;
					p = i;
				}
			}
			System.out.format(FORMAT, r, g, b, R[p], G[p], B[p]);

			r = jin.nextInt();
			g = jin.nextInt();
			b = jin.nextInt();
		}
	}

}
