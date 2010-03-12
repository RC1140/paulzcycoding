package p1016;

import java.util.Scanner;

public class Main {
	static final String[] FORMAT = { "%s is self-inventorying\n",
			"%s is self-inventorying after %d steps\n",
			"%s enters an inventory loop of length %d\n",
			"%s can not be classified after 15 iterations\n" };
	static final int MAX_ITERATION = 15;

	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);

		String n = jin.nextLine();
		while (!n.equals("-1")) {
			String[] iteration = new String[MAX_ITERATION + 1];
			iteration[0] = n;
			
			int result = 3;
			int para = 0;

			for (int i = 1; i <= MAX_ITERATION && result == 3; ++i) {
				iteration[i] = transform(iteration[i - 1]);
				for (int j = 0; j < i; ++j) {
					if (iteration[i].equals(iteration[j])) {
						if (i == 1) {
							result = 0;
						} else if (j + 1 == i) {
							result = 1;
							para = j;
						} else {
							result = 2;
							para = i - j;
						}
						break;
					}
				}
			}

			System.out.format(FORMAT[result], n, para);

			n = jin.nextLine();
		}
	}

	static String transform(String string) {
		int[] count = new int[10];

		for (char c : string.toCharArray())
			++count[c - '0'];
		
		StringBuffer sb = new StringBuffer();
		for (int i = 0; i < 10; ++i) {
			if (count[i] > 0) {
				sb.append(count[i]);
				sb.append(i);
			}
		}

		return sb.toString();
	}
}
