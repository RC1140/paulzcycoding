#include "logicpolynomial/logic.h"
#include "algorithm.h"
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

ostream& operator << (ostream& os, const vector<LogicPolynomial<128> >& v) {
  copy(v.begin(), v.end(), ostream_iterator<LogicPolynomial<128> >(os, ","));
  return os;
};

int main(int argc, char* argv[]) {
  typedef DES<LogicPolynomial<128> > des;
  des::WORD key(64);
  des::WORD plain(64);

key[0] = LogicPolynomial<128>(LogicPolynomial<65>::X);
key[1] = LogicPolynomial<128>(LogicPolynomial<66>::X);
key[2] = LogicPolynomial<128>(LogicPolynomial<67>::X);
key[3] = LogicPolynomial<128>(LogicPolynomial<68>::X);
key[4] = LogicPolynomial<128>(LogicPolynomial<69>::X);
key[5] = LogicPolynomial<128>(LogicPolynomial<70>::X);
key[6] = LogicPolynomial<128>(LogicPolynomial<71>::X);
key[7] = LogicPolynomial<128>(LogicPolynomial<72>::X);
key[8] = LogicPolynomial<128>(LogicPolynomial<73>::X);
key[9] = LogicPolynomial<128>(LogicPolynomial<74>::X);
key[10] = LogicPolynomial<128>(LogicPolynomial<75>::X);
key[11] = LogicPolynomial<128>(LogicPolynomial<76>::X);
key[12] = LogicPolynomial<128>(LogicPolynomial<77>::X);
key[13] = LogicPolynomial<128>(LogicPolynomial<78>::X);
key[14] = LogicPolynomial<128>(LogicPolynomial<79>::X);
key[15] = LogicPolynomial<128>(LogicPolynomial<80>::X);
key[16] = LogicPolynomial<128>(LogicPolynomial<81>::X);
key[17] = LogicPolynomial<128>(LogicPolynomial<82>::X);
key[18] = LogicPolynomial<128>(LogicPolynomial<83>::X);
key[19] = LogicPolynomial<128>(LogicPolynomial<84>::X);
key[20] = LogicPolynomial<128>(LogicPolynomial<85>::X);
key[21] = LogicPolynomial<128>(LogicPolynomial<86>::X);
key[22] = LogicPolynomial<128>(LogicPolynomial<87>::X);
key[23] = LogicPolynomial<128>(LogicPolynomial<88>::X);
key[24] = LogicPolynomial<128>(LogicPolynomial<89>::X);
key[25] = LogicPolynomial<128>(LogicPolynomial<90>::X);
key[26] = LogicPolynomial<128>(LogicPolynomial<91>::X);
key[27] = LogicPolynomial<128>(LogicPolynomial<92>::X);
key[28] = LogicPolynomial<128>(LogicPolynomial<93>::X);
key[29] = LogicPolynomial<128>(LogicPolynomial<94>::X);
key[30] = LogicPolynomial<128>(LogicPolynomial<95>::X);
key[31] = LogicPolynomial<128>(LogicPolynomial<96>::X);
key[32] = LogicPolynomial<128>(LogicPolynomial<97>::X);
key[33] = LogicPolynomial<128>(LogicPolynomial<98>::X);
key[34] = LogicPolynomial<128>(LogicPolynomial<99>::X);
key[35] = LogicPolynomial<128>(LogicPolynomial<100>::X);
key[36] = LogicPolynomial<128>(LogicPolynomial<101>::X);
key[37] = LogicPolynomial<128>(LogicPolynomial<102>::X);
key[38] = LogicPolynomial<128>(LogicPolynomial<103>::X);
key[39] = LogicPolynomial<128>(LogicPolynomial<104>::X);
key[40] = LogicPolynomial<128>(LogicPolynomial<105>::X);
key[41] = LogicPolynomial<128>(LogicPolynomial<106>::X);
key[42] = LogicPolynomial<128>(LogicPolynomial<107>::X);
key[43] = LogicPolynomial<128>(LogicPolynomial<108>::X);
key[44] = LogicPolynomial<128>(LogicPolynomial<109>::X);
key[45] = LogicPolynomial<128>(LogicPolynomial<110>::X);
key[46] = LogicPolynomial<128>(LogicPolynomial<111>::X);
key[47] = LogicPolynomial<128>(LogicPolynomial<112>::X);
key[48] = LogicPolynomial<128>(LogicPolynomial<113>::X);
key[49] = LogicPolynomial<128>(LogicPolynomial<114>::X);
key[50] = LogicPolynomial<128>(LogicPolynomial<115>::X);
key[51] = LogicPolynomial<128>(LogicPolynomial<116>::X);
key[52] = LogicPolynomial<128>(LogicPolynomial<117>::X);
key[53] = LogicPolynomial<128>(LogicPolynomial<118>::X);
key[54] = LogicPolynomial<128>(LogicPolynomial<119>::X);
key[55] = LogicPolynomial<128>(LogicPolynomial<120>::X);
key[56] = LogicPolynomial<128>(LogicPolynomial<121>::X);
key[57] = LogicPolynomial<128>(LogicPolynomial<122>::X);
key[58] = LogicPolynomial<128>(LogicPolynomial<123>::X);
key[59] = LogicPolynomial<128>(LogicPolynomial<124>::X);
key[60] = LogicPolynomial<128>(LogicPolynomial<125>::X);
key[61] = LogicPolynomial<128>(LogicPolynomial<126>::X);
key[62] = LogicPolynomial<128>(LogicPolynomial<127>::X);
key[63] = LogicPolynomial<128>(LogicPolynomial<128>::X);
/*
plain[0] = LogicPolynomial<128>(LogicPolynomial<1>::X);
plain[1] = LogicPolynomial<128>(LogicPolynomial<2>::X);
plain[2] = LogicPolynomial<128>(LogicPolynomial<3>::X);
plain[3] = LogicPolynomial<128>(LogicPolynomial<4>::X);
plain[4] = LogicPolynomial<128>(LogicPolynomial<5>::X);
plain[5] = LogicPolynomial<128>(LogicPolynomial<6>::X);
plain[6] = LogicPolynomial<128>(LogicPolynomial<7>::X);
plain[7] = LogicPolynomial<128>(LogicPolynomial<8>::X);
plain[8] = LogicPolynomial<128>(LogicPolynomial<9>::X);
plain[9] = LogicPolynomial<128>(LogicPolynomial<10>::X);
plain[10] = LogicPolynomial<128>(LogicPolynomial<11>::X);
plain[11] = LogicPolynomial<128>(LogicPolynomial<12>::X);
plain[12] = LogicPolynomial<128>(LogicPolynomial<13>::X);
plain[13] = LogicPolynomial<128>(LogicPolynomial<14>::X);
plain[14] = LogicPolynomial<128>(LogicPolynomial<15>::X);
plain[15] = LogicPolynomial<128>(LogicPolynomial<16>::X);
plain[16] = LogicPolynomial<128>(LogicPolynomial<17>::X);
plain[17] = LogicPolynomial<128>(LogicPolynomial<18>::X);
plain[18] = LogicPolynomial<128>(LogicPolynomial<19>::X);
plain[19] = LogicPolynomial<128>(LogicPolynomial<20>::X);
plain[20] = LogicPolynomial<128>(LogicPolynomial<21>::X);
plain[21] = LogicPolynomial<128>(LogicPolynomial<22>::X);
plain[22] = LogicPolynomial<128>(LogicPolynomial<23>::X);
plain[23] = LogicPolynomial<128>(LogicPolynomial<24>::X);
plain[24] = LogicPolynomial<128>(LogicPolynomial<25>::X);
plain[25] = LogicPolynomial<128>(LogicPolynomial<26>::X);
plain[26] = LogicPolynomial<128>(LogicPolynomial<27>::X);
plain[27] = LogicPolynomial<128>(LogicPolynomial<28>::X);
plain[28] = LogicPolynomial<128>(LogicPolynomial<29>::X);
plain[29] = LogicPolynomial<128>(LogicPolynomial<30>::X);
plain[30] = LogicPolynomial<128>(LogicPolynomial<31>::X);
plain[31] = LogicPolynomial<128>(LogicPolynomial<32>::X);
plain[32] = LogicPolynomial<128>(LogicPolynomial<33>::X);
plain[33] = LogicPolynomial<128>(LogicPolynomial<34>::X);
plain[34] = LogicPolynomial<128>(LogicPolynomial<35>::X);
plain[35] = LogicPolynomial<128>(LogicPolynomial<36>::X);
plain[36] = LogicPolynomial<128>(LogicPolynomial<37>::X);
plain[37] = LogicPolynomial<128>(LogicPolynomial<38>::X);
plain[38] = LogicPolynomial<128>(LogicPolynomial<39>::X);
plain[39] = LogicPolynomial<128>(LogicPolynomial<40>::X);
plain[40] = LogicPolynomial<128>(LogicPolynomial<41>::X);
plain[41] = LogicPolynomial<128>(LogicPolynomial<42>::X);
plain[42] = LogicPolynomial<128>(LogicPolynomial<43>::X);
plain[43] = LogicPolynomial<128>(LogicPolynomial<44>::X);
plain[44] = LogicPolynomial<128>(LogicPolynomial<45>::X);
plain[45] = LogicPolynomial<128>(LogicPolynomial<46>::X);
plain[46] = LogicPolynomial<128>(LogicPolynomial<47>::X);
plain[47] = LogicPolynomial<128>(LogicPolynomial<48>::X);
plain[48] = LogicPolynomial<128>(LogicPolynomial<49>::X);
plain[49] = LogicPolynomial<128>(LogicPolynomial<50>::X);
plain[50] = LogicPolynomial<128>(LogicPolynomial<51>::X);
plain[51] = LogicPolynomial<128>(LogicPolynomial<52>::X);
plain[52] = LogicPolynomial<128>(LogicPolynomial<53>::X);
plain[53] = LogicPolynomial<128>(LogicPolynomial<54>::X);
plain[54] = LogicPolynomial<128>(LogicPolynomial<55>::X);
plain[55] = LogicPolynomial<128>(LogicPolynomial<56>::X);
plain[56] = LogicPolynomial<128>(LogicPolynomial<57>::X);
plain[57] = LogicPolynomial<128>(LogicPolynomial<58>::X);
plain[58] = LogicPolynomial<128>(LogicPolynomial<59>::X);
plain[59] = LogicPolynomial<128>(LogicPolynomial<60>::X);
plain[60] = LogicPolynomial<128>(LogicPolynomial<61>::X);
plain[61] = LogicPolynomial<128>(LogicPolynomial<62>::X);
plain[62] = LogicPolynomial<128>(LogicPolynomial<63>::X);
plain[63] = LogicPolynomial<128>(LogicPolynomial<64>::X);
*/
  for (int i = 0; i < 64; ++i)
    plain[i] = LogicPolynomial<128>::ZERO;
  cout << plain << endl << key << endl;
  cout << des::encrypt(plain, key) << endl;
  return 0;
}
