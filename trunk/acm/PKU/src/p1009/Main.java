package p1009;

import static java.lang.Math.abs;
import static java.lang.Math.max;
import static java.lang.Math.min;

import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Scanner;

public class Main {
	private static class Writer {
		private Pair queue;

		public Writer(int width) {
			System.out.println(width);
			queue = null;
		}

		public void write(Pair entry) {
			if (queue == null) {
				queue = new Pair(entry);
			} else {
				if (queue.value == entry.value) {
					queue.length += entry.length;
				} else {
					flush();
					queue = new Pair(entry);
				}
			}
		}

		public void finish() {
			flush();
			System.out.println("0 0");
		}

		private void flush() {
			System.out.println(queue);
		}
	}

	private static class Pair {
		public int value;
		public int length;

		public Pair(int value, int length) {
			this.value = value;
			this.length = length;
		}

		public Pair(Pair entry) {
			this.value = entry.value;
			this.length = entry.length;
		}

		public String toString() {
			return "" + value + ' ' + length;
		}
	}

	private static class Edge {
		LinkedList<Pair> edge;
		Writer writer;

		public Edge(int width, Writer writer) {
			edge = new LinkedList<Pair>();
			edge.add(new Pair(0, width));
			this.writer = writer;
		}

		public void update(int start, Pair pair) {

			if (pair.length <= 0)
				return;

			ListIterator<Pair> iterator = edge.listIterator();
			int end = start + pair.length;

			Pair temp = iterator.next();
			int p = 0;

			while (p + temp.length <= start) {
				p += temp.length;
				temp = iterator.next();
			}

			if (p < start) {
				iterator.remove();
				iterator.add(new Pair(temp.value, start - p));
				temp = new Pair(temp.value, temp.length - (start - p));

				iterator.add(temp);
				iterator.previous();
				iterator.next();
				p = start;
			}

			while (p + temp.length <= end) {
				if (temp.value < pair.value) {
					temp.value = pair.value;
				}

				p += temp.length;
				if (iterator.hasNext())
					temp = iterator.next();
			}

			if (p < end) {
				if (temp.value < pair.value) {
					iterator.remove();
					iterator.add(new Pair(pair.value, end - p));
					iterator.add(new Pair(temp.value, temp.length - (end - p)));
				}
			}
		}

		public String toString() {
			return edge.toString();
		}

		public void output() {
			for (Pair i : edge) {
				writer.write(i);
			}
		}
	}

	private static class Handler {

		private Writer writer;
		private int width;

		private LinkedList<Pair> lastLine, currentLine;
		private Edge lastEdge, currentEdge;
		private int currentPos;

		public Handler(int width) {
			this.width = width;
			writer = new Writer(width);

			currentPos = 0;
			currentLine = new LinkedList<Pair>();
		}

		private void insert(Pair pair) {

			currentLine.add(pair);
			currentPos += pair.length;

			// if current line is full, calculate current edge, update last
			// edge and export last line
			if (currentPos == width) {
				// calculate current edge
				currentEdge = new Edge(width, writer);

				if (lastLine == null) {
					ListIterator<Pair> p = currentLine.listIterator();

					Pair i = p.next();
					currentEdge.update(0, new Pair(0, i.length));
					int q = i.length;

					while (p.hasNext()) {
						Pair j = p.next();
						int diff = abs(j.value - i.value);

						currentEdge.update(q, new Pair(0, j.length));
						currentEdge.update(q - 1, new Pair(diff, 2));

						q += j.length;
						i = j;
					}

				} else {
					int p = 0;
					ListIterator<Pair> i = currentLine.listIterator();
					ListIterator<Pair> j = lastLine.listIterator();

					Pair m = i.next();
					Pair n = j.next();

					int nextI = m.length;
					int nextJ = n.length;

					currentEdge.update(p, new Pair(abs(m.value - n.value), min(
							nextI, nextJ)));
					lastEdge.update(p, new Pair(abs(m.value - n.value), min(
							nextI, nextJ)));

					while (i.hasNext() || j.hasNext()) {
						int currentValueAtP_1, currentValueAtP;
						int lastValueAtP_1, lastValueAtP;

						if (nextI < nextJ) {
							p = nextI;

							lastValueAtP_1 = n.value;
							currentValueAtP_1 = m.value;

							m = i.next();
							lastValueAtP = n.value;
							currentValueAtP = m.value;

							nextI = p + m.length;

						} else if (nextI == nextJ) {
							p = nextI;

							lastValueAtP_1 = n.value;
							currentValueAtP_1 = m.value;

							m = i.next();
							n = j.next();
							lastValueAtP = n.value;
							currentValueAtP = m.value;

							nextI = p + m.length;
							nextJ = p + n.length;
						} else { // nextI > nextJ
							p = nextJ;

							lastValueAtP_1 = n.value;
							currentValueAtP_1 = m.value;

							n = j.next();
							lastValueAtP = n.value;
							currentValueAtP = m.value;

							nextJ = p + n.length;
						}

						lastEdge.update(p - 1, new Pair(max(abs(lastValueAtP
								- lastValueAtP_1), abs(currentValueAtP
								- lastValueAtP_1)), 1));
						lastEdge.update(p, new Pair(max(abs(lastValueAtP_1
								- lastValueAtP), abs(currentValueAtP_1
								- lastValueAtP)), 1));

						currentEdge.update(p - 1, new Pair(max(abs(lastValueAtP
								- currentValueAtP_1), abs(currentValueAtP
								- currentValueAtP_1)), 1));
						currentEdge.update(p, new Pair(max(abs(lastValueAtP_1
								- currentValueAtP), abs(currentValueAtP_1
								- currentValueAtP)), 1));

						currentEdge.update(p, new Pair(abs(m.value - n.value),
								min(nextI, nextJ) - p));
						lastEdge.update(p, new Pair(abs(m.value - n.value),
								min(nextI, nextJ) - p));

					}

					lastEdge.output();
				}

				lastLine = currentLine;
				lastEdge = currentEdge;

				currentLine = new LinkedList<Pair>();
				currentPos = 0;
			}
		}

		public void push(Pair pair) {
			if (pair.length == 0) {

				lastEdge.output();

				writer.finish();
				return;
			}

			// fit the pair into current line
			if (pair.length >= width - currentPos) {
				pair.length -= (width - currentPos);
				insert(new Pair(pair.value, width - currentPos));
			}

			// ---------
			// .........
			// ---------
			// ----

			int lines = pair.length / width;

			if (lines >= 2) {
				insert(new Pair(pair.value, width));
				if (lines >= 3)
					writer.write(new Pair(0, (lines - 2) * width));
				pair.length -= (lines - 1) * width;
			}

			// fit the remaining
			if (pair.length > width) {
				insert(new Pair(pair.value, width));
				pair.length -= width;
			}

			if (pair.length > 0)
				insert(pair);

		}
	}

	public static void main(String[] args) {
		Scanner jin = new Scanner(System.in);

		int width;

		width = jin.nextInt();

		while (width > 0) {
			Handler handler = new Handler(width);

			int value = jin.nextInt();
			int length = jin.nextInt();
			handler.push(new Pair(value, length));

			while (length > 0) {

				value = jin.nextInt();
				length = jin.nextInt();
				handler.push(new Pair(value, length));
			}

			width = jin.nextInt();

		}
		System.out.println(0);
	}
}
