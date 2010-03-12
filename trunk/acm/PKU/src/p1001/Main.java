package p1001;

import java.util.Scanner;

public class Main {
	/**
	 * A <code>BigNumber</code> can be represented by <latex>d_l d_{l-1} \dots
	 * d_0 \times 10^e</latex>.
	 * 
	 * @author XTOg
	 * 
	 */
	static private class BigNumber {
		private final int MAXDIGITS = 150;

		private int[] digits;
		private int e;
		private int l;

		public BigNumber(String r) {
			digits = new int[MAXDIGITS];
			e = 0;
			l = r.length();
			
			int p = 0;

			for (int i = r.length() - 1; i >= 0; --i) {
				char c = r.charAt(i);
				if (c == '.') {
					e = -p;
				} else {
					digits[p] = c - '0';
					++p;
				}
			}

			while (digits[l] == 0)
				--l;
			
		}

		public void exp(int n) {
			int[] result = digits.clone();

			for (int i = 1; i < n; ++i) {
				int[] temp = new int[MAXDIGITS];

				for (int j = 0; j < l + 1; ++j)
					for (int k = 0; k < (l + 1) * i; ++k) {
						temp[j + k] += result[k] * digits[j];
					}

				for (int p = 0; p < (l + 1) * (i + 1); ++p) {
					temp[p + 1] += temp[p] / 10;
					temp[p] = temp[p] % 10;
				}

				result = temp;

			}

			e *= n;
			l = (l + 1) * n - 1;

			digits = result;
			while (digits[l] == 0)
				--l;

		}

		public String toString() {

			StringBuffer sb = new StringBuffer();
			int p = l;

			for (; p + e >= 0; --p)
				sb.append(digits[p]);

			int q = 0;
			while (digits[q] == 0)
				++q;

			if (q + e < 0)
				sb.append('.');

			for (int i = e + l + 1; i < 0; ++i)
				sb.append('0');

			for (; p >= q; --p)
				sb.append(digits[p]);
			
			return sb.toString();
		}

	}

	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);
		
		while (jin.hasNext()) {
			String r = jin.next();
			int n = jin.nextInt();

			BigNumber num = new BigNumber(r);

			num.exp(n);

			System.out.println(num);
		}

	}

}
