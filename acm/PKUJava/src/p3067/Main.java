package p3067;

import java.util.Arrays;
import java.util.Scanner;

public class Main {
	static final int MAXN = 1000, MAXM = 1000;

	static class Highway implements Comparable<Highway> {
		int east, west;

		@Override
		public int compareTo(Highway o) {
			if (east < o.east) {
				return 1;
			} else if (east > o.east) {
				return -1;
			} else {
				return o.west - west;
			}
		}

	}

	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);
		
		int T = jin.nextInt();

		for (int t = 1; t <= T; ++t) {
			@SuppressWarnings("unused")
			int n = jin.nextInt();
			int m = jin.nextInt();
			int k = jin.nextInt();
			
			Highway[] highways = new Highway[k];
			
			for (int i = 0; i < k; ++i) {
				highways[i] = new Highway();
				highways[i].east = jin.nextInt();
				highways[i].west = jin.nextInt();
			}
			
			Arrays.sort(highways);
			
			long sum = 0;
			int[] map = new int[m + 1];
			
			for (int i = 0; i < k;) {
				int j = i;
				while(j < k && highways[j].east == highways[i].east) {
					for (int w = highways[j].west - 1; w > 0; w -= (w & -w)) {
						sum += map[w];
					}
					for (int w = highways[j].west; w <= m; w += (w & -w)) {
						++map[w];
					}
					++j;
				}
				i = j;
			}

			System.out.format("Test case %d: %d\n", t, sum);
		}
	}
}
