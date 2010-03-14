package p1010;

import static java.util.Arrays.sort;
import java.util.Collection;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.Vector;

public class Main {
	static class Handler {
		class Pair {
			Integer stamp;
			Integer number;

			Pair(Integer stamp, Integer number) {
				this.stamp = stamp;
				this.number = number;
			}

			public Pair(Pair p) {
				this.stamp = new Integer(p.stamp);
				this.number = new Integer(p.number);
			}
		}

		class Answer implements Comparable<Answer> {
			LinkedList<Pair> stamps;

			public Answer(Answer answer) {
				stamps = new LinkedList<Pair>();
				for (Pair p : answer.stamps) {
					stamps.add(new Pair(p));
				}
			}

			public Answer() {
				stamps = new LinkedList<Pair>();
			}

			public String toString() {
				StringBuffer sb = new StringBuffer();
				for (Pair p : stamps) {
					for (int i = 0; i < p.number; ++i)
						sb.append(" " + p.stamp);
				}
				return sb.toString();
			}

			@Override
			public int compareTo(Answer o) {
				if (this.stamps.size() < o.stamps.size()) {
					return -1;
				} else if (this.stamps.size() > o.stamps.size()) {
					return 1;
				} else {
					if (this.stamps.getLast().stamp < o.stamps.getLast().stamp) {
						return -1;
					} else if (this.stamps.getLast().stamp > o.stamps.getLast().stamp) {
						return 1;
					} else {
						return 0;
					}
				}
			}
		}

		Integer[] stamps;

		Handler(Collection<Integer> stamps) {
			this.stamps = stamps.toArray(new Integer[0]);
			sort(this.stamps);
		}

		Answer bestAnswer;
		boolean tie;

		void dfs(int depth, int usedStamps, int remaining, Answer answer) {
			if (depth == stamps.length)
				return;

			dfs(depth + 1, usedStamps, remaining, answer);

			int max = 4 - usedStamps;
			if (remaining / stamps[depth] < max)
				max = remaining / stamps[depth];

			for (int i = 1; i <= max; ++i) {
				answer.stamps.add(new Pair(stamps[depth], i));
				if (remaining - stamps[depth] * i == 0) {
					//System.out.println(answer);
					if (bestAnswer == null) {
						bestAnswer = new Answer(answer);
					} else if (answer.compareTo(bestAnswer) > 0) {
						bestAnswer = new Answer(answer);
						tie = false;
					} else if (answer.compareTo(bestAnswer) == 0) {
						tie = true;
					}
				} else if (usedStamps + i < 4) {
					dfs(depth + 1, usedStamps + i, remaining - stamps[depth]
							* i, answer);
				}
				answer.stamps.removeLast();
			}
		}

		public void handle(int request) {
			bestAnswer = null;
			tie = false;

			Answer answer = new Answer();
			dfs(0, 0, request, answer);

			if (bestAnswer == null) {
				System.out.println("" + request + " ---- none");
			} else {
				if (tie) {
					System.out.println("" + request + " ("
							+ bestAnswer.stamps.size() + "): tie");
				} else {
					System.out.println("" + request + " ("
							+ bestAnswer.stamps.size() + "):" + bestAnswer);
				}
			}

		}
	}

	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);
		while (jin.hasNext()) {
			Vector<Integer> stamps = new Vector<Integer>();

			int denomination = jin.nextInt();
			while (denomination > 0) {
				stamps.add(denomination);
				denomination = jin.nextInt();
			}

			Handler handler = new Handler(stamps);

			int request = jin.nextInt();
			while (request > 0) {
				handler.handle(request);
				request = jin.nextInt();
			}

		}
	}

}
