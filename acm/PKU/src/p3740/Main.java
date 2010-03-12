package p3740;

import java.util.Scanner;

public class Main {
	static final String FOUND = "Yes, I found it";
	static final String NOTFOUND = "It is impossible";
	static final int[] E = { 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80,
			0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000 };

	static void main(String[] args) {
		Scanner jin = new Scanner(System.in);
		while (jin.hasNext()) {
			int m = jin.nextInt();
			int n = jin.nextInt();
			
			int[] matrix = new int[n];
			
			for (int i = 0; i < m; ++i) {
				for (int j = 0; j < n; ++j) {
					matrix[j] |= jin.nextInt() * E[i];
				}
			}
		}
	}
	
}
