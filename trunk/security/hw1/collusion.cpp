#include <iostream>
using namespace std;

int main() {
  const double N = 65535;
  double result = 1;
  for (double n = 1; result > 0.1; n += 1.) {
    result = 1;
    for (double i = 0; i < n; i += 1) {
      result *= (N - n - i)/(N - i);
    }
    cout << n << '\t' << (1 - result) << endl;
  }
  return 0;
}
