package p1028;

import java.util.Scanner;

public class Main {

	static final int MAX_WEBS = 101;
	static final String IGNORED = "Ignored";

	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);

		String[] stack = new String[MAX_WEBS];
		stack[0] = "http://www.acm.org/ ";
		int pointer = 0;
		int top = 0;

		String[] command = jin.nextLine().split(" ");
		while (!command[0].equals("QUIT")) {
			if (command[0].equals("VISIT")) {
				++pointer;
				top = pointer;
				stack[pointer] = command[1];
				System.out.println(stack[pointer]);
			} else if (command[0].equals("BACK")) {
				if (pointer > 0) {
					--pointer;
					System.out.println(stack[pointer]);
				} else {
					System.out.println(IGNORED);
				}
			} else if (command[0].equals("FORWARD")) {
				if (pointer < top) {
					++pointer;
					System.out.println(stack[pointer]);
				} else {
					System.out.println(IGNORED);
				}
			}
			command = jin.nextLine().split(" ");
		}
	}
}
