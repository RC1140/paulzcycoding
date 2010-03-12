package p1845;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);
		final int M = 9901;
		
		int a = jin.nextInt(), b = jin.nextInt();
		
		if (a == 0) {
			System.out.println(0);
			return;
		} else if (a == 1) {
			System.out.println(1);
			return;
		}
		
		int result = 1;
		int P = 2;
		
		while (a > 1) {
			while (a % P != 0) {
				++P;
			}
			
			int n = 0;
			while (a % P == 0) {
				++n;
				a = a / P;
			}
			n = n * b;
			
			//calculate (1 + p + p^2 + ... + p^n) % 9901 
			int p = P % M;
			int subresult = 1;
			if (p == 1) {
				subresult = (n + 1) % M;
			} else if (p == 0) {
				subresult = 1;
			} else {
				int m = (n + 1) % (M - 1);
				for (int i = 0; i < m; ++i)
					subresult = (subresult * p) % M;
				subresult = (subresult - 1) % M;
				
				int j = 1;
				while (j * (p - 1) % M != 1) ++j;
				
				subresult = subresult * j % M;
			}
			
			result = result * subresult % M;
		}
		
		System.out.println(result);
		return;
	}
}
