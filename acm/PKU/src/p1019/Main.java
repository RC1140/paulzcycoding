package p1019;

import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);

		final int THRESHOLD = 5;
		final int E = 10;

		int[] EXP = new int[THRESHOLD + 1];
		int[] SEQUENCE_SIZE = new int[THRESHOLD + 1];
		int[] BLOCK_SIZE = new int[THRESHOLD + 1];

		EXP[0] = 1;
		SEQUENCE_SIZE[0] = 0;
		BLOCK_SIZE[0] = 0;

		for (int i = 1; i < THRESHOLD; ++i) {
			EXP[i] = E * EXP[i - 1];
			SEQUENCE_SIZE[i] = SEQUENCE_SIZE[i - 1] + i * (E - 1) * EXP[i - 1];
			BLOCK_SIZE[i] = SEQUENCE_SIZE[i - 1] * (E - 1) * EXP[i - 1] + i
					* (E - 1) * EXP[i - 1] * ((E - 1) * EXP[i - 1] + 1) / 2;
		}
		EXP[THRESHOLD] = EXP[THRESHOLD - 1] * E;
		SEQUENCE_SIZE[THRESHOLD] = Integer.MAX_VALUE;
		BLOCK_SIZE[THRESHOLD] = Integer.MAX_VALUE;

		int t = jin.nextInt();
		while (t-- > 0) {
			int i = jin.nextInt();

			/* Find e, so that 
			 * 
			 * |S_1 ... S_{E^{e - 1} - 1}| < i <= |S_1 ... S_{E^e - 1}|
			 */
			int e = 0;
			while (i > BLOCK_SIZE[e]) {
				i -= BLOCK_SIZE[e];
				++e;
			}

			/* 
			 * Find k, so that 
			 * 	
			 * |S_1 ... S_{E^{e-1} + k - 1}| < i <= |S_1 ... S_{E^{e-1} + k}|	
			 */
			int m = 0;
			int k = Math.min((E - 1) * EXP[e - 1], 22544);
			while (m + 1 != k) {
				int n = (m + k) / 2;
				int v = n * SEQUENCE_SIZE[e - 1] + n * (n + 1) / 2 * e;
				if (v >= i) {
					k = n;
				} else {
					m = n;
				}
			}
			i -= (k - 1) * SEQUENCE_SIZE[e - 1] + k * (k - 1) / 2 * e;
			
			for (int f = 1;; ++f) {

				if (i <= f * (E - 1) * EXP[f - 1]) {
					int l = i / f;
					i %= f;
					if (i == 0) {
						i = f;
					} else {
						l += 1;
					}
					l += EXP[f - 1] - 1;
					System.out.println(Integer.toString(l).charAt(i - 1));
					break;
				}
				i -= f * (E - 1) * EXP[f - 1];
			}
		}
	}
}
