#include "logic.h"
#include "algorithm.h"
#include <iostream>

using namespace std;

ostream& operator << (ostream& os, const vector<LogicPolynomial<128> >& v) {
  return os << v;
};

int main(int argc, char** argv) {
  typedef DES<LogicPolynomial<128> > des;
  des::WORD key(64);
  des::WORD plain(64);

  for (int i = 0; i < 64; ++i) {
    key[i] = LogicPolynomial<128>(LogicPolynomial<i + 1>::X);
    plain[i] = LogicPolynomial<128>(LogicPolynomial<i + 65>::X);
  }
  cout << plain << endl << key << endl;
  des::WORD cipher = des::encrypt(plain, key);
  return 0;
}
