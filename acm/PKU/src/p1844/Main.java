package p1844;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);

		int s = jin.nextInt();

		int i = (int) Math.ceil((-1 + Math.sqrt(1 + 8 * s)) / 2);

		while ((i * (i + 1) / 2 - s) % 2 != 0)
			++i;

		System.out.println(i);
	}
}
