#ifndef __LOGIC_H__
#define __LOGIC_H__

#include <iostream>
// A LogicPolynomial is described as a tree.
// Subtree with height 0 is constant: zero or one.
// A height N tree T_N is
// T_N = X_N & T_N.high + T_N.low
// where T_N.high and T_N.low is subtree with height N - 1.
// 
// All trees, subtrees, created, or returned by functions must have the following properties:
// 1. The low pointer must not be 0(deferable).
// 2. The high pointer is set to 0, if and only if X_N & 0.
// 3. The check isZero() to see whether the Polynomial is equivilent to 0.

template <int N>
class LogicPolynomial {
public:
  static const LogicPolynomial<N> X;
  static const LogicPolynomial<N> ZERO, ONE;
  
  LogicPolynomial() {
    new (this) LogicPolynomial<N>(ZERO);
  };
  LogicPolynomial(const LogicPolynomial<N>& b) {
    if (b.high) {
      high = new LogicPolynomial<N - 1>(*(b.high));
    } else {
      high = 0;
    }
    low = new LogicPolynomial<N - 1>(*(b.low));
    zero = b.isZero();
  };
  LogicPolynomial(const LogicPolynomial<N - 1>& l) {
    high = 0;
    low = new LogicPolynomial<N - 1>(l);
    zero = l.isZero();
  };

  template <int M>
  LogicPolynomial(const LogicPolynomial<M>& l) {
    new (this) LogicPolynomial<N>(LogicPolynomial<N - 1>(l));
  }
  // If this constructor is used, h most not be zero, so that this cannot be zero.
  LogicPolynomial(const LogicPolynomial<N - 1>& l, const LogicPolynomial<N - 1>& h) {
    high = new LogicPolynomial<N - 1>(h);
    low = new LogicPolynomial<N - 1>(l);
    zero = 0;
  };
  ~LogicPolynomial() {
    if (high) delete high;
    delete low;
  };
  
  LogicPolynomial& operator = (const LogicPolynomial<N>& b) {
    if (this == &b) return *this;
    if (high) delete high;
    delete low;
    
    if (b.high) {
      high = new LogicPolynomial<N - 1>(*(b.high));
    } else {
      high = 0;
    }
    low = new LogicPolynomial<N - 1>(*(b.low));

    zero = b.isZero();
    return *this;
  };
  LogicPolynomial<N>& operator &= (const LogicPolynomial<N>& b) {
    //std::cout << N << '\t' << *this << " & " << b << std::endl;
    //result.high = a.h b.h + a.l b.h + a.h b.l;
    if (high) {
      if (b.high) {
        LogicPolynomial<N - 1> tmp(*b.high);
        tmp ^= *b.low;
        *high &= tmp;
        tmp = *b.high;
        tmp &= *low;
        *high ^= tmp;
        if (high->isZero()) {
          delete high;
	  high = 0;
        }
      } else {
        //if a.h is not 0 znd b.h is zero
        //then result.h = a.h b.l
        if (b.low->isZero()) {
          delete high;
	  high = 0;
        } else {
          *high &= *b.low;
        }
      }
    } else {
      // if a.h is zero,
      // then result = a.l b.h
      if (b.high && !low->isZero()) {
          high = new LogicPolynomial<N - 1>(*low);
          *high &= *b.high;
      } //else keep a.h 0.
    }
    
    *low &= *b.low;
    zero = !high && low->isZero();
    return *this;
  };
  LogicPolynomial<N>& operator ^= (const LogicPolynomial<N>& b) {
    //std::cout << N << '\t' << *this << " ^ " << b << std::endl;
    if (b.high) {
      if (high) {
        *high ^= *b.high;
        if (high->isZero()) {
          delete high;
          high = 0;
        }
      } else {
        high = new LogicPolynomial<N - 1>(*b.high);
      }
    }

    *low ^= *b.low;
    
    zero = !high && low->isZero();
    return *this;
  };

  inline bool isZero() const {
    return zero;
  };
  
  //private:
  LogicPolynomial<N - 1>* high;
  LogicPolynomial<N - 1>* low;
  int zero;
  
  //friend bool operator == (const LogicPolynomial<N>& a, const LogicPolynomial<N>& b);
  //friend LogicPolynomial<N> operator & (const LogicPolynomial<N>& a, const LogicPolynomial<N>& b);
  //friend LogicPolynomial<N> operator ^ (const LogicPolynomial<N>& a, const LogicPolynomial<N>& b);

  //friend std::ostream& operator << (std::ostream& os, const LogicPolynomial<N>& b);
};

template <int N>
const LogicPolynomial<N> LogicPolynomial<N>::X(LogicPolynomial<N - 1>::ZERO, LogicPolynomial<N - 1>::ONE);
template <int N>
const LogicPolynomial<N> LogicPolynomial<N>::ONE(LogicPolynomial<N - 1>::ONE);
template <int N>
const LogicPolynomial<N> LogicPolynomial<N>::ZERO(LogicPolynomial<N - 1>::ZERO);

template <int N>
bool operator == (const LogicPolynomial<N>& a, const LogicPolynomial<N>& b) {
  return ((a.high == 0 && b.high == 0) || (a.high != 0 && b.high != 0 && *a.high == *b.high))
  && ((a.low == 0 && b.low == 0) || (a.low != 0 && b.low != 0 && *a.low == *b.low));
};

template <int N>
bool operator != (const LogicPolynomial<N>& a, const LogicPolynomial<N>& b) {
  return (a.high == 0 && b.high != 0) 
  || (a.high != 0 && b.high == 0) 
  || (a.low == 0 && b.low != 0) 
  || (a.low != 0 && b.low == 0)
  || (a.high != 0 && b.high != 0 && *a.high != *b.high) 
  || (a.low != 0 && b.low != 0 && *a.low != *b.low);
};

template <int N>
std::ostream& operator << (std::ostream& os, const LogicPolynomial<N>& b) {
  const static char OPAND = '&';
  const static char OPXOR = '+';
  if (b.high) {
    os << 'x' << N;
    if (*b.high != LogicPolynomial<N - 1>::ONE) {
      os << ' ' << OPAND << ' ' << '(' << *b.high << ')';
    }
    if (!b.low->isZero()) {
      os << ' ' << OPXOR << ' ' << *b.low;
    }
  } else {
    os << *b.low;
  }
  return os;
};

template <>
class LogicPolynomial<0> {
private:
  int value;
  
public:
  static const LogicPolynomial<0> ZERO, ONE;

  LogicPolynomial(int _v = 0):value(_v) {};
  LogicPolynomial(const LogicPolynomial<0>& b):value(b.value) {};

  LogicPolynomial<0>& operator = (const LogicPolynomial<0>& b) {
    value = b.value;
    return *this;
  };
  LogicPolynomial& operator &= (const LogicPolynomial<0>& b) {
    value &= b.value;
    return *this;
  };
  LogicPolynomial& operator ^= (const LogicPolynomial<0>& b) {
    value ^= b.value;
    return *this;
  };
  
  inline bool isZero() const {
    return !value;
  };
  
  friend std::ostream& operator << (std::ostream& os, const LogicPolynomial<0>& b);
  friend bool operator != (const LogicPolynomial<0>& a, const LogicPolynomial<0>& b); 
  friend bool operator == (const LogicPolynomial<0>& a, const LogicPolynomial<0>& b);
};

const LogicPolynomial<0> LogicPolynomial<0>::ZERO(0);
const LogicPolynomial<0> LogicPolynomial<0>::ONE(1);

bool operator != (const LogicPolynomial<0>& a, const LogicPolynomial<0>& b) {
  return a.value != b.value;
};

bool operator == (const LogicPolynomial<0>& a, const LogicPolynomial<0>& b) {
  return a.value == b.value;
};

std::ostream& operator << (std::ostream& os, const LogicPolynomial<0>& b) {
  return os << b.value;
};

template <int N>
LogicPolynomial<N> operator ^ (const LogicPolynomial<N>& a, const LogicPolynomial<N>& b) {
  LogicPolynomial<N> result(a);
  result ^= b;
  return result;
};

template <int N>
LogicPolynomial<N> operator & (const LogicPolynomial<N>& a, const LogicPolynomial<N>& b) {
  LogicPolynomial<N> result(a);
  result &= b;
  return result;
};

#endif
