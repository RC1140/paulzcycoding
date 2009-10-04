#include "algorithm.h"
#include "logic.h"
#include <iostream>
using namespace std;
inline int t(char c) {
	if ('0' <= c && c <= '9') return c - '0';
	if ('a' <= c && c <= 'f') return c - 'a' + 10;
	if ('A' <= c && c <= 'F') return c - 'A' + 10;
}

ostream& operator << (ostream& os, const vector<int>& v) {
  static const char e[16] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
  };
  for (vector<int>::const_iterator i = v.begin(); i != v.end(); i += 4) {
    os << e[*i * 8 + *(i+1) * 4 + *(i+2)*2 + *(i+3)];
  }
  return os;
};

int main(int argc, char** argv) {
  typedef DES<int> des;
  des::WORD plain(64);

  int p = 0;
  for (int i = 0; i < 64; ++i) {
    if (i % 8 == 7) continue;
    des::WORD key(64);
    key[i] = 1;
    for (int j = 0; j < 8; ++j) {
      if (j != i / 8) key[j * 8 + 7] = 1;
    }
    cout << p++ << '\t' << key << ' ' << des::encrypt(plain, key) << endl;
    
  }

  return 0;
}

