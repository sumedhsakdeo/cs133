#ifndef _BIG_INT_UTILS_H_
#define _BIG_INT_UTILS_H_

#include <vector>
#include <string>
extern "C" {
#include <stdint.h>
}

class BigUInt_Utils	{
public:
    static std::vector<unsigned> AddBignum(std::vector<unsigned>& num1, std::vector<unsigned>& num2);
    static std::vector<unsigned> SubtractBignum(std::vector<unsigned>& num1, std::vector<unsigned>& num2);
    static std::vector<unsigned> MultiplyBignum(std::vector<unsigned>& num1, std::vector<unsigned>& num2);
    static std::vector<unsigned> AndBignum(std::vector<unsigned>& num1, std::vector<unsigned>& num2);
    static std::vector<unsigned> OrBignum(std::vector<unsigned>& num1, std::vector<unsigned>& num2);
    static std::vector<unsigned> XorBignum(std::vector<unsigned>& num1, std::vector<unsigned>& num2);
    static std::vector<unsigned> NotBignum(std::vector<unsigned>& num1);
    static bool EqualBignum(std::vector<unsigned>& num1, std::vector<unsigned>& num2);
    static std::vector<unsigned> Lshift(std::vector<unsigned>& num1, const unsigned& shift);
    static std::vector<unsigned> Rshift(std::vector<unsigned>& num1, const unsigned& shift);
    static bool GreaterThan(std::vector<uint32_t>& num1, std::vector<uint32_t>& num2);
    static bool LessThan(std::vector<uint32_t>& num1, std::vector<uint32_t>& num2);
};

#endif //_BIG_INT_UTILS_H_

