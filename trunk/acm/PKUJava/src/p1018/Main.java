package p1018;

import java.text.DecimalFormat;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;

public class Main {
	static class Device implements Comparable<Device> {
		int bandwidth;
		int price;
		int device;

		public Device(int bandwidth, int price, int device) {
			this.bandwidth = bandwidth;
			this.price = price;
			this.device = device;
		}

		@Override
		public int compareTo(Device o) {
			return o.bandwidth - bandwidth;
		}

	}

	static public void main(String[] args) {
		Scanner jin = new Scanner(System.in);
		DecimalFormat df = new DecimalFormat("0.000");
		
		int t = jin.nextInt();
		while (t-- > 0) {
			int n = jin.nextInt();
			Queue<Device> queue = new PriorityQueue<Device>();

			for (int i = 0; i < n; ++i) {
				int m = jin.nextInt();
				for (int j = 0; j < m; ++j) {
					queue.offer(new Device(jin.nextInt(), jin.nextInt(), i));
				}
			}

			boolean[] isConnected = new boolean[n];
			int connected = 0;
			int totalPrice = 0;
			int[] price = new int[n];
			double maxAverage = 0;

			while (!queue.isEmpty()) {
				Device d = queue.poll();

				if (isConnected[d.device]) {
					if (d.price < price[d.device]) {
						totalPrice = totalPrice - price[d.device] + d.price;
						price[d.device] = d.price;
					}
				} else {
					isConnected[d.device] = true;
					price[d.device] = d.price;
					totalPrice += d.price;
					++connected;
				}

				if (connected == n) {
					double average = (double) d.bandwidth / (double) totalPrice;
					if (average > maxAverage) {
						maxAverage = average;
					}
				}
			}
			
			System.out.println(df.format(maxAverage));
		}
	}
}
