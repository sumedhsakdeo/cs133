/**
 * Arbitrary Multiprecision Unsigned Integer Arithmetic Lib
 */

#ifndef _BIG_U_INT_INF_H_
#define _BIG_U_INT_INF_H_

#include <string>

class BigUInt_Inf {
public:
    virtual BigUInt_Inf* operator+(const BigUInt_Inf *) = 0;
    virtual BigUInt_Inf* operator-(const BigUInt_Inf *) = 0;
    virtual BigUInt_Inf* operator*(const BigUInt_Inf *) = 0;
    virtual BigUInt_Inf* operator/(const BigUInt_Inf *) = 0;
    virtual BigUInt_Inf* operator<<(const unsigned int&) = 0;
    virtual BigUInt_Inf* operator>>(const unsigned int&) = 0;
    virtual BigUInt_Inf* operator&(const BigUInt_Inf *) = 0;
    virtual BigUInt_Inf* operator|(const BigUInt_Inf *) = 0;
    virtual BigUInt_Inf* operator^(const BigUInt_Inf *) = 0;
    virtual BigUInt_Inf* operator~() = 0;
    virtual bool operator==(const BigUInt_Inf *) = 0;
	virtual std::string ToString() = 0;
    virtual ~BigUInt_Inf();
};

#endif // _BIG_U_INT_INF_H_ 
