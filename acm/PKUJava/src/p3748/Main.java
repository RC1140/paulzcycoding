package p3748;

import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);

		String[] buf = jin.nextLine().split(",");

		int[] R = new int[32];
		int i = buf[0].length() - 1;
		int p = 0;

		while (i >= 0) {
			char c = buf[0].charAt(i);
			int v;
			if ('0' <= c && c <= '9') {
				v = c - '0';
			} else {
				v = c - 'a' + 10;
			}
			
			R[p++] = v % 2;
			v = v / 2;
			R[p++] = v % 2;
			v = v / 2;
			R[p++] = v % 2;
			v = v / 2;
			R[p++] = v % 2;
			v = v / 2;
			--i;
		}

		int X = Integer.parseInt(buf[1]);
		int Y = Integer.parseInt(buf[2]);

		R[X] = 0;
		R[Y] = 1;
		R[Y - 1] = 1;
		R[Y - 2] = 0;

		final char CHAR[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
		boolean write = false;
		for (i = 31; i > 0; i -= 4) {
			int v = R[i] * 8 + R[i - 1] * 4 + R[i - 2] * 2 + R[i - 3];
			if (v > 0) {
				write = true;
				System.out.print(CHAR[v]);
			} else {
				if (write) {
					System.out.print(CHAR[v]);
				}
			}
		}
	}

}
