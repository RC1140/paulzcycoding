#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv) {
  const int e[6] = {32, 16, 8, 4, 2, 1};

  for (int box = 0; box < 8; ++box) {
    cout << "static WORD sbox" << box << "(const WORD& x) {" << endl;
    cout << "\tWORD result(4);" << endl;
    for (int point = 0; point < 4; ++point) {
      //cout << "\tcout << " << point << "<< endl;" << endl;
      cout << "\tresult[" << point << "] = ";
      bool flag = false;
      for (int i = 0; i < 64; ++i) {
        int p;
        cin >> p;
        if (p) {
          if (i == 0) {
            cout << 1;
            flag = true;
          } else {
            if (flag) cout << " ^ ";
            flag = true;
            bool flag2 = false;
            cout << '(';
            for (int j = 0; j < 6; ++j) {
              if (i & e[j]) {
                if (flag2) cout << " & ";
                flag2 = true;
                cout << "x[" << j << "]";
              }
            }
            cout << ')';
          }
        }
      }
      cout << ";" << endl;
    }
    cout << "\treturn result;" << endl;
    cout << "}" << endl;
  }
  return 0;
}
