package p1061;

import java.util.Scanner;

public class Main {

	static int lastX = 1;
	static int lastY = 0;
	static int l;
	
	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);
		final String IMPOSSIBLE = "Impossible";

		int x = jin.nextInt();
		int y = jin.nextInt();
		int m = jin.nextInt();
		int n = jin.nextInt();
		l = jin.nextInt();

		if (m == n) {
			System.out.println(IMPOSSIBLE);
			return;
		}

		int a = m - n;
		int b = x - y;

		if (a < 0) {
			a = -a;
			b = -b;
		}
		
		if (b < 0) b += l;

		int gcd = gcd(l, a);
		
		if (b % gcd != 0) {
			System.out.println(IMPOSSIBLE);
			return;
		}
		
		System.out.println(multiple(b / gcd, l - lastY));
	}
	
	static int plus(int a, int b) {
		if (a >= l - b)
			return b - l + a;
		else
			return a + b;
	}
	
	static int multiple(int a, int b) {
		int result = 0;
		int e = a;
		while (b > 0) {
			if (b % 2 == 1) {
				result = plus(result, e);
			}
			b = b / 2;
			e = plus(e, e);
		}
		return result;
	}

	static int gcd(int a, int b) {
		int x = 0;
		int y = 1;

		int temp;
		while (b != 0) {
			temp = x;
			x = plus(lastX, l - multiple(a / b, x));
			lastX = temp;
			
			temp = y;
			y = plus(lastY, l - multiple(a / b, y));
			lastY = temp;
			
			temp = b;
			b = a % b;
			a = temp;

		}
		return a;
	}
}
