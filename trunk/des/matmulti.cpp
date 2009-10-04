#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv) {
  ifstream fin("sboxinvmat");
  int A[64][64];
  int b[64];
  for (int i = 0; i < 64; ++i) {
    for (int j = 0; j < 64; ++j) {
      fin >> A[i][j];
    }
  }

  for (int k = 0; k < 32; ++k) {
    for (int i = 0; i < 64; ++i) {
      cin >> b[i];
    }
    for (int i = 0; i < 64; ++i) {
      int r = 0;
      for (int j = 0; j < 64; ++j) {
	r += A[i][j] * b[j];
      }
      cout << r % 2 << endl;
    }
  }

  return 0;
}
