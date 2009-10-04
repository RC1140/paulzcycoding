#include "logic.h"
#include "algorithm.h"
#include <iostream>

using namespace std;

ostream& operator << (ostream& os, const vector<LogicPolynomial<128> >& v) {
  for (vector<LogicPolynomial<128> >::const_iterator i = v.begin(); i != v.end(); ++i) {
    os << i->size() << ' ';
  }
  return os;
};

int main(int argc, char** argv) {
  typedef DES<LogicPolynomial<128> > des;
  des::WORD key(64);
  des::WORD plain(64);

  for (int i = 0; i < 64; ++i) {
    LogicMonomial<128> kbit(1), pbit(1);
    kbit[i + 1 + 64] = 1;
    key[i] = LogicPolynomial<128>(kbit);
    pbit[i + 1] = 1;
    plain[i] = LogicPolynomial<128>(pbit);
  }
  cout << plain << endl << key << endl;
  des::WORD cipher = des::encrypt(plain, key);
  return 0;
}
