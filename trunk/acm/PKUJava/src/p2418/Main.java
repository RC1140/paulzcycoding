package p2418;

import java.util.NavigableMap;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.Map.Entry;

public class Main {

	static NavigableMap<String, Integer> map = new TreeMap<String, Integer>();

	public static void main(String[] args) {
		// Runtime.getRuntime().
		Scanner jin = new Scanner(System.in);
		int sum = 0;
		while (jin.hasNext()) {
			String name = jin.nextLine();
			Integer num = map.get(name);
			if (num == null) {
				map.put(name, 1);
			} else {
				map.put(name, num + 1);
			}

			++sum;
		}

		while (!map.isEmpty()) {
			Entry<String, Integer> tree = map.pollFirstEntry();
			System.out.format("%s %.4f\n", tree.getKey(), 100.
					* tree.getValue() / sum);
		}
	}
}
