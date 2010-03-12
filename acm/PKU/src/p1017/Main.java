package p1017;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);
		
		int a1, a2, a3, a4, a5, a6;
		
		a1 = jin.nextInt();
		a2 = jin.nextInt();
		a3 = jin.nextInt();
		a4 = jin.nextInt();
		a5 = jin.nextInt();
		a6 = jin.nextInt();
		
		while (a1 + a2 + a3 + a4 + a5 + a6 > 0) {
			int result;
			int emptyCells = 0;
			
			result = a4 + a5 + a6;
			emptyCells += a5 * 11 + a4 * 20;
			
			result += a3 / 4;
			a3 %= 4;
			if (a3 > 0) {
				emptyCells += 36 - a3 * 9;
				++result;
			}
			
			int fitA2inA4 = Math.min(a2, a4 * 5);
			
			a2 -= fitA2inA4;
			emptyCells -= 4 * fitA2inA4;
			
			int fitA2inA3 = 0;
			if (a3 == 1) {
				fitA2inA3 = 5;
			} else if (a3 == 2) {
				fitA2inA3 = 3;
			} else if (a3 == 3) {
				fitA2inA3 = 1;
			}
			fitA2inA3 = Math.min(a2, fitA2inA3);
			a2 -= fitA2inA3;
			emptyCells -= 4 * fitA2inA3;
			
			result += a2 / 9;
			a2 = a2 % 9;
			if (a2 > 0) {
				++result;
				emptyCells += 36 - a2 * 4;
			}
			
			a1 -= Math.min(a1, emptyCells);
			result += a1 / 36;
			a1 = a1 % 36;
			if (a1 > 0) ++result;
			
			
			System.out.println(result);
			
			a1 = jin.nextInt();
			a2 = jin.nextInt();
			a3 = jin.nextInt();
			a4 = jin.nextInt();
			a5 = jin.nextInt();
			a6 = jin.nextInt();
		}
	}

}
