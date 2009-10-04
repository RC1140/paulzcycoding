#include "logic.h"
#include <iostream>
using namespace std;

int main() {
  LogicPolynomial<10> a, b;
  a & b;
  a ^ b;
  1 ^ a;
  return 0;
}

