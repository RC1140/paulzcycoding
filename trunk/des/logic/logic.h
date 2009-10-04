#ifndef __LOGIC_H__
#define __LOGIC_H__

template <int N>
class LogicPolynomial {
public:
	LogicPolynomial(const LogicPolynomial<N>& b) {
		if (b.high) {
			high = new LogicPolynomial<N - 1>(*(b.high));
		} else {
			high = 0;
		}
		low = new LogicPolynomial<N - 1>(*(b.low));
		notZero = b.notZero;
	};
	LogicPolynomial(const LogicPolynomial<N - 1>& b) {
		high = 0;
		low = new LogicPolynomial<N - 1>(b);
		notZero = b.notZero;
	};
	~LogicPolynomial() {
		if (high) delete high;
		delete low;
	};
	
	LogicPolynomial& operator = (const LogicPolynomial<N>& b) {
		if (this == &b) return *this;
		if (high) delete high;
		if (low) delete low;
		if (b.high) {
			high = new LogicPolynomial<N - 1>(*(b.high));
		} else {
			high = 0;
		}
		low = new LogicPolynomial<N - 1>(*(b.low));

		notZero = b.notZero;
		return *this;
	};
	LogicPolynomial<N>& operator &= (const LogicPolynomial<N>& b);
	LogicPolynomial<N>& operator ^= (const LogicPolynomial<N>& b) {
		if (b.high) {
			if (a.high) {
				*a.high ^= *b.high;
				if (!a.high->notZero) {
					delete a.high;
					a.high = 0;
				}
			} else {
				a.high = new LogicPolynomial<N - 1>(*b.high);
			}
		}

		if (a.low) {
			*a.low ^= *b.low;
		}
		notZero = high || low->notZero;
		return *this;
	};

private:
	LogicPolynomial<N - 1>* high;
	LogicPolynomial<N - 1>* low;
	int notZero;
	
friend bool operator == (const LogicPolynomial<N>& a, const LogicPolynomial<N>& b);
//friend LogicPolynomial<N> operator & (const LogicPolynomial<N>& a, const LogicPolynomial<N>& b);
//friend LogicPolynomial<N> operator ^ (const LogicPolynomial<N>& a, const LogicPolynomial<N>& b);

friend std::ostream& operator << (std::ostream& os, const LogicPolynomial<N>& b);
};

template <int N>
bool operator == (const LogicPolynomial<N>& a, const LogicPolynomial<N>& b) {
	return ((a.high == 0 && b.high == 0) || (a.high != 0 && b.high != 0 && *a.high) == *b.high)))
		&& ((a.low == 0 && b.low == 0) || (a.low != 0 && b.low != 0 && *a.low) == *b.low)))
};

template <int N>
std::ostream& operator << (std::ostream& os, const LogicPolynomial<N>& b) {
	const static char OPAND = '&';
	const static char OPXOR = '+';
	if (b.high) {
		os << 'x' << N << ' ' << OPAND << ' ' << '(' << *b.high << ')';
		if (b.low->notZero) {
			os << ' ' << OPXOR << ' ' << b.low;
		}
	} else {
		os << b.low;
	}
	return os;
}

class LogicPolynomial<0> {
private:
	int notZero;
public:
	LogicPolynomial(int _v = 0):notZero(_v) {};
	LogicPolynomial(const LogicPolynomial<0>& b):notZero(b.notZero) {};

	LogicPolynomial<0>& operator = (const LogicPolynomial<0>& b) {
		notZero = b.notZero;
		return *this;
	};
	LogicPolynomial& operator &= (const LogicPolynomial<N>& b) {
		notZero &= b.notZero;
		return *this;
	};
	LogicPolynomial& operator ^= (const LogicPolynomial<N>& b) {
		notZero ^= b.notZero;
		return *this;
	};
	
friend bool operator == (const LogicPolynomial<0>& a, const LogicPolynomial<0>& b);

friend std::ostream& operator << (std::ostream& os, const LogicPolynomial<N>& b);
};

bool operator == (const LogicPolynomial<0>& a, const LogicPolynomial<0>& b) {
	return a.notZero == b.notZero;
};

std::ostream& operator << (std::ostream& os, const LogicPolynomial<N>& b) {
	return os << notZero;
};
#endif