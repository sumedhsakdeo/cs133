/**
 * Arbitarary Multiprecision Unsigned Integer Arethmatic Lib
 */

#ifndef _BIG_U_INT_INF_H_
#define _BIG_U_INT_INF_H_


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
    virtual ~BigUInt_Inf();
};

#endif // _BIG_U_INT_INF_H_ 
