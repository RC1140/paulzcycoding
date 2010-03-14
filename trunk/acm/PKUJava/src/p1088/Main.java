package p1088;

import java.util.Scanner;

public class Main {
	static int r, c;
	static int[][] map;
	static int[][] max;
	static int[] dx = { -1, 0, 1, 0 };
	static int[] dy = { 0, 1, 0, -1 };

	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);

		r = jin.nextInt();
		c = jin.nextInt();
		map = new int[r][c];
		max = new int[r][c];

		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				map[i][j] = jin.nextInt();
			}
		}

		int maxLength = 0;
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				int m = getMax(i, j);
				if (m > maxLength) {
					maxLength = m;
				}
			}
		}
		System.out.println(maxLength);
	}

	static int getMax(int row, int column) {
		if (max[row][column] == 0) {
			max[row][column] = 1;
			for (int i = 0; i < 4; ++i) {
				int x = row + dx[i];
				int y = column + dy[i];
				if (0 <= x && x < r && 0 <= y && y < c) {
					if (map[x][y] < map[row][column]) {
						int m = getMax(x, y) + 1;
						if (m > max[row][column]) {
							max[row][column] = m;
						}
					}

				}
			}
		}
		return max[row][column];
	}
}
