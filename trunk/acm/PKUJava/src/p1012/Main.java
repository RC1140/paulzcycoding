package p1012;

import java.util.Scanner;

public class Main {
	static final int MAXK = 14;

	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);

		int k = jin.nextInt();
		int[] cache = new int[MAXK];

		while (k > 0) {
			if (cache[k] == 0) {
				int p;
				for (p = k;; ++p) {
					int i;
					int j = 0;
					for (i = 0; i < k; ++i) {
						j = (j + p) % (2 * k - i);
						if (j < k)
							break;
					}
					if (i == k)
						break;
				}
				cache[k] = p + 1;
			}
			
			System.out.println(cache[k]);

			k = jin.nextInt();
		}
	}
}
