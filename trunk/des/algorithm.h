// This is a naive implement of DES block encription.
// What I'm trying to do is to see how the exact output is compared to the input.
// First I'll try if my implement is right.
// After that, I'll use symbolic calculation to get a result.
// So, I'm using template.
//
// Performance is not what I'm considering.
// I'll keep the program as clear as possible.
//
// XTOg
// Sept 16, 2009
#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include <vector>
#include <iostream>
// In this template, I'll assume that 
// BYTE type supports ^ and & operation.
// In the test, BYTE will be int.

// The encrypt function, the input is the block and key, both 64 bits length,
// the output is the encrypted data, length 64 bits.
template <typename BYTE>
class DES {
public:
  typedef std::vector<BYTE> WORD;

  static WORD encrypt(const WORD& input, const WORD& key) {
    std::vector<WORD> keys = generateKeys(key);
    
    WORD block = input;
//    std::cout << block << std::endl;
    initialPermutation(block);
    //std::cout << block << std::endl;

    WORD l(32), r(32), l2(32), r2(32);

    for (int i = 0; i < 32; ++i) {
      l[i] = block[i];
      r[i] = block[i + 32];
    }

    //std::cout << l << ' ' << r << std::endl;

    for (int i = 0; i < 16; ++i) {
      l2 = r;
      WORD c = cipher(r, keys[i]);
      for (int j = 0; j < 32; ++j) {
        r2[j] = l[j] ^ c[j];
      }
      l = l2;
      r = r2;
      std::cout << l << ' ' << r << std::endl;
    }
    
    for (int i = 0; i < 32; ++i) {
      block[i] = r[i];
      block[i + 32] = l[i];
    }

    revInitPerm(block);

    return block;
  };

  static WORD cipher(const WORD& r, const WORD& key) {
    const int e[48] = {
      32, 1, 2, 3, 4, 5,
      4, 5, 6, 7, 8, 9,
      8, 9, 10, 11, 12, 13,
      12, 13, 14, 15, 16, 17,
      16, 17, 18, 19, 20, 21,
      20, 21, 22, 23, 24, 25,
      24, 25, 26, 27, 28, 29,
      28, 29, 30, 31, 32, 1
    };
    WORD t(48);
    for (int i = 0; i < 48; ++i) t[i] = r[e[i] - 1]; 
    //std::cout << "expand\t" << t << std::endl;
    for (int i = 0; i < 48; ++i) t[i] = t[i] ^ key[i];

    WORD s[8];
    WORD re[8];

    for (int i = 0; i < 8; ++i) {
      s[i] = WORD(6);
      for (int j = 0; j < 6; ++j) {
	s[i][j] = t[i * 6 + j];
      }
    }

    re[0] = sbox0(s[0]);
    std::cout << re[0] << std::endl;
    re[1] = sbox1(s[1]);
    std::cout << re[1] << std::endl;
    re[2] = sbox2(s[2]);
    std::cout << re[2] << std::endl;
    re[3] = sbox3(s[3]);
    std::cout << re[3] << std::endl;
    re[4] = sbox4(s[4]);
    std::cout << re[4] << std::endl;
    re[5] = sbox5(s[5]);
    std::cout << re[5] << std::endl;
    re[6] = sbox6(s[6]);
    std::cout << re[6] << std::endl;
    re[7] = sbox7(s[7]);
    std::cout << re[7] << std::endl;

    /*
    for (int i = 0; i < 8; ++i)
      std::cout << re[i] << ' ';
    std::cout << std::endl;
    */

    WORD result(32);

    for (int i = 0; i < 4; ++i) {
      result[0 + i] = re[0][i];
      result[4 + i] = re[1][i];
      result[8 + i] = re[2][i];
      result[12 + i] = re[3][i];
      result[16 + i] = re[4][i];
      result[20 + i] = re[5][i];
      result[24 + i] = re[6][i];
      result[28 + i] = re[7][i];
    }

    static const int p[32] = {
      16, 7, 20, 21,
      29, 12, 28, 17,
      1, 15, 23, 26,
      5, 18, 31, 10,
      2, 8, 24, 14,
      32, 27, 3, 9,
      19, 13, 30, 6,
      22, 11, 4, 25
    };

    WORD tmp = result;
    for (int i = 0; i < 32; ++i) {
      result[i] = tmp[p[i] - 1];
    }

    return result;
  };

  static std::vector<WORD> generateKeys(const WORD& key) {
    static const int PC1[2][28] = { {
      57, 49, 41, 33, 25, 17, 9,
      1, 58, 50, 42, 34, 26, 18,
      10, 2, 59, 51, 43, 35, 27,
      19, 11, 3, 60, 52, 44, 36
    }, {
      63, 55, 47, 39, 31, 23, 15,
      7, 62, 54, 46, 38, 30, 22,
      14, 6, 61, 53, 45, 37, 29,
      21, 13, 5, 28, 20, 12, 4
    } };

    static const int PC2[48] = {
      14, 17, 11, 24, 1, 5,
      3, 28, 15, 6, 21, 10,
      23, 19, 12, 4, 26, 8,
      16, 7, 27, 20, 13, 2,
      41, 52, 31, 37, 47, 55,
      30, 40, 51, 45, 33, 48,
      44, 49, 39, 56, 34, 53,
      46, 42, 50, 36, 29, 32
    };

    const int times[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    WORD c(28), d(28);
    std::vector<WORD> result(16);

    for (int i = 0; i < 28; ++i) {
      c[i] = key[PC1[0][i] - 1];
      d[i] = key[PC1[1][i] - 1];
    }

    for (int i = 0; i < 16; ++i) {
      c = leftshift(c, times[i]);
      d = leftshift(d, times[i]);
      //cout << c << d << endl;

      result[i] = WORD(48);

      WORD tmp(56);
      for (int j = 0; j < 28; ++j) {
	tmp[j] = c[j];
	tmp[j + 28] = d[j];
      }
      for (int j = 0; j < 48; ++j) {
        result[i][j] = tmp[PC2[j] - 1];
      }
    }

    return result;
  }

  static WORD leftshift(const WORD& a, int times) {
    WORD result = a;
    
    for (int i = 0; i < times; ++i) {
      BYTE tmp = result[0];
      for (int j = 1; j < 28; ++j) {
        result[j - 1] = result[j];
      }
      result[27] = tmp;
    }

    return result;
  }

  static void initialPermutation(WORD& block) {
    WORD tmp = block;
    const int IP[64] = {
      58, 50, 42, 34, 26, 18, 10, 2,
      60, 52, 44, 36, 28, 20, 12, 4,
      62, 54, 46, 38, 30, 22, 14, 6,
      64, 56, 48, 40, 32, 24, 16, 8,
      57, 49, 41, 33, 25, 17, 9, 1,
      59, 51, 43, 35, 27, 19, 11, 3,
      61, 53, 45, 37, 29, 21, 13, 5,
      63, 55, 47, 39, 31, 23, 15, 7
    };
    for (int i = 0; i < 64; ++i) {
      block[i] = tmp[IP[i] - 1];
    }
  }

  static void revInitPerm(WORD& block) {
    static const int RIP[64] = {
      40, 8, 48, 16, 56, 24, 64, 32,
      39, 7, 47, 15, 55, 23, 63, 31,
      38, 6, 46, 14, 54, 22, 62, 30,
      37, 5, 45, 13, 53, 21, 61, 29,
      36, 4, 44, 12, 52, 20, 60, 28,
      35, 3, 43, 11, 51, 19, 59, 27,
      34, 2, 42, 10, 50, 18, 58, 26,
      33, 1, 41, 9, 49, 17, 57, 25
    };

    WORD tmp = block;
    for (int i = 0; i < 64; ++i) {
      block[i] = tmp[RIP[i] - 1];
    }
  }

#include "sboxfunction.h"
};

#endif
