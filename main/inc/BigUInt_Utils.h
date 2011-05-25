#ifndef _BIG_INT_UTILS_H_
#define _BIG_INT_UTILS_H_

#include <vector>
#include <string>

class BigUInt_Utils	{
public:
    static std::vector<unsigned int> StringToVector(const std::string &);
    static std::string VectorToString(const std::vector<unsigned int>& buf);
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
};

#endif //_BIG_INT_UTILS_H_

