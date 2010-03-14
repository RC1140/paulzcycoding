package p1936;

import java.util.Scanner;

public class Main {
	static final String YES = "Yes";
	static final String NO = "No";

	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);
		
		while (jin.hasNext()) {
			String a = jin.next();
			String b = jin.next();
			
			int p = 0;
			
			for (char c:b.toCharArray()) {
				if (c == a.charAt(p)) {
					++p;
				}
				if (p == a.length()) {
					break;
				}
			}
			
			if (p == a.length()) {
				System.out.println(YES);
			} else {
				System.out.println(NO);
			}
		}

	}

}
