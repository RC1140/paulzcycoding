#include "algorithm.h"
#include "logic.h"
#include <iostream>
using namespace std;

typedef DES<int> des;

inline int t(char c) {
	if ('0' <= c && c <= '9') return c - '0';
	if ('a' <= c && c <= 'f') return c - 'a' + 10;
	if ('A' <= c && c <= 'F') return c - 'A' + 10;
};

template <int N>
char* word2char(const des::WORD& d, char* c) {
  static const char e[16] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
  };
  for (int i = 0; i < N / 4; ++i) {
    c[i] = e[d[4 * i] * 8 + d[4 * i + 1] * 4 + d[4 * i + 2] * 2 + d[4 * i + 3]];
  }
  c[N / 4] = '\0';
  return c;
};

template <int N>
des::WORD& char2word(const char* c, des::WORD& d) {
  static const int e[4] = {8, 4, 2, 1};

  for (int i = 0; i < N / 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (t(c[i]) & e[j]) {
	d[4 * i + j] = 1;
      } else {
	d[4 * i + j] = 0;
      }
    }
  }

  return d;
};

void usage() {
  cout << "des [-k key] [-p plain]" << endl;
};

int main(int argc, char** argv) {
  const static int KEYSIZE = 64;

  char key[KEYSIZE / 4 + 1], plain[KEYSIZE / 4 + 1];
  des::WORD Plain(KEYSIZE), Key(KEYSIZE);
  char cipher[KEYSIZE / 4 + 1];

  char* k = 0;
  char* p = 0;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      switch(argv[i][1]) {
	case 'k':
	  k = argv[++i];
	  break;
	case 'p':
	  p = argv[++i];
	  break;
	default:
	  usage();
	  return 1;
      };
    } else {
      usage();
      return 1;
    }
  }

  if (p && k) {
    char2word<64>(p, Plain);
    char2word<64>(k, Key);

    word2char<64>(des::encrypt(Plain, Key), cipher);
    cout << p << ' ' << k << ' ' << cipher << endl;
  } else if (p) {
    char2word<64>(p, Plain);
    while (cin >> key) {
      char2word<64>(key, Key);
      word2char<64>(des::encrypt(Plain, Key), cipher);
      cout << p << ' ' << key << ' ' << cipher << endl;
    }
  } else if (k) {
    char2word<64>(k, Key);
    while (cin >> plain) {
      char2word<64>(plain, Plain);
      word2char<64>(des::encrypt(Plain, Key), cipher);
      cout << plain << ' ' << k << ' ' << cipher << endl;
    }
  } else {
    while (cin >> plain >> key) {
      char2word<64>(key, Key);
      char2word<64>(plain, Plain);
      word2char<64>(des::encrypt(Plain, Key), cipher);
      cout << plain << ' ' << key << ' ' << cipher << endl;
    }
  }

  return 0;
}

