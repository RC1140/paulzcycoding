#ifndef __LOGIC_H__
#define __LOGIC_H__

#include <set>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <bitset>

template <int N>
class LogicMonomial:public std::bitset<1 + N> {
  public:
    LogicMonomial(unsigned long val = 0ul):std::bitset<1 + N>(val) {};
    LogicMonomial(const std::bitset<1 + N>& b):std::bitset<1 + N>(b) {};

    const static LogicMonomial<N> ZERO;
    const static LogicMonomial<N> ONE;
};

template <int N> const LogicMonomial<N> LogicMonomial<N>::ZERO(0);
template <int N> const LogicMonomial<N> LogicMonomial<N>::ONE(1);

template <int N>
LogicMonomial<N> operator &(const LogicMonomial<N>& a, const LogicMonomial<N>& b) {
  if (a[0] == 0 || b[0] == 0) {
    return LogicMonomial<N>::ZERO;
  } else {
    return a | b;
  }
};

template <int N>
inline bool operator < (const LogicMonomial<N>& a, const LogicMonomial<N>& b) {
  int i = 0;
  for (; i < 1 + N && a[i] == b[i]; ++i) ;
  return i < 1 + N && a[i] < b[i];
};

template <int N>
std::ostream& operator << (std::ostream& os, const LogicMonomial<N>& b) {
  const static char c[2][2][2][2] = {{{{'0', '1'}, {'2', '3'}}, {{'4', '5'}, {'6', '7'}}},
    {{{'8', '9'}, {'A', 'B'}}, {{'C', 'D'}, {'E', 'F'}}}};
  os << b[0];
  for (int i = 1; i < N; i += 4)
    os << c[b[i]][b[i + 1]][b[i + 2]][b[i + 3]];

  return os; 
};

template <int N>
class LogicPolynomial:public std::set<LogicMonomial<N> > {
  public:
    const static LogicPolynomial ZERO;
    const static LogicPolynomial ONE;

    LogicPolynomial() {
      insert(LogicMonomial<N>::ZERO);
    };

    LogicPolynomial(const LogicMonomial<N>& p) {
      insert(p);
    };
};

template <int N> const LogicPolynomial<N> LogicPolynomial<N>::ZERO(LogicMonomial<N>::ZERO);
template <int N> const LogicPolynomial<N> LogicPolynomial<N>::ONE(LogicMonomial<N>::ONE);

template <int N>
LogicPolynomial<N> operator ^ (int a, const LogicPolynomial<N>& b) {
  if (a) {
    return LogicPolynomial<N>::ONE ^ b;
  } else {
    return b;
  }
};

template <int N>
LogicPolynomial<N> operator & (const LogicPolynomial<N>& a, const LogicPolynomial<N>& b) {
  LogicPolynomial<N> result;
  for (typename LogicPolynomial<N>::const_iterator i = a.begin(); i != a.end(); ++i) {
    for (typename LogicPolynomial<N>::const_iterator j = b.begin(); j != b.end(); ++j) {
      result.insert(*i & *j);
    }
  }

  if (result.size() > 1) result.erase(LogicMonomial<N>::ZERO);

  return result;
};

template <int N>
LogicPolynomial<N> operator ^ (const LogicPolynomial<N>& a, const LogicPolynomial<N>& b) {
  LogicPolynomial<N> result;
  std::set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(),
      std::inserter<LogicPolynomial<N> >(result, result.begin()));
  if (result.size() > 1) result.erase(LogicMonomial<N>::ZERO);
  return result;
};

template <int N>
inline std::ostream& operator <<(std::ostream& os, const LogicPolynomial<N>& v) {
  typename LogicPolynomial<N>::const_iterator i = v.end();
  --i;
  os << '[';
  std::copy(v.begin(), i, std::ostream_iterator<LogicMonomial<N> >(os, " + "));
  os << *i;
  return os << ']';
};

#endif
