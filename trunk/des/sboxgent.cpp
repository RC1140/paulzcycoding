#include <iostream>
using namespace std;

int main(int argc, char** argv) {
  const int e[6] = {1, 2, 4, 8, 16, 32};

  for (int i = 0; i < 64; ++i) {
    for (int j = 0; j < 64; ++j) {
      int r = 1;
      for (int k = 0; k < 6; ++k) {
        if (j & e[k]) {
          r = r && (i & e[k]);
        }
      }
      cout << r << ' ';
    }
    cout << endl;
  }
  return 0;
}
