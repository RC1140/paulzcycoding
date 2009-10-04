#include <iostream>
#include "sboxdata.h"

int main(int argc, char** argv) {
  static const char e[16][5] = {
    "0000",
    "0001",
    "0010",
    "0011",
    "0100",
    "0101",
    "0110",
    "0111",
    "1000",
    "1001",
    "1010",
    "1011",
    "1100",
    "1101",
    "1110",
    "1111"
  };

  for (int box = 0; box < 8; ++box) {
    for (int p = 0; p < 4; ++p) {
      for (int k = 0; k < 64; ++k) {
	int l = ((k & 0x20) >> 4) + (k & 0x1);
	int m = (k & 0x1e) >> 1;
	//    cout << k << '\t' << l << '\t' << m << '\t';
	std::cout << e[sbox[box][l][m]][p] << std::endl; 
      }
    }
  }
  return 0;
}
