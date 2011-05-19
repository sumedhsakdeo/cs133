#ifndef _BIG_U_INT_SERIAL_IMPL_H_
#define _BIG_U_INT_SERIAL_IMPL_H_

#include <vector>
#include <string>

#include "BigUInt_Inf.h"
#include	"BigInt_Utils.h"

class BigUInt_Serial_Impl : public BigUInt_Inf {    
private:
    std::vector<int> buf;
public:
    BigUInt_Serial_Impl(); 
    BigUInt_Serial_Impl(const std::string&); 
    BigUInt_Serial_Impl(const BigUInt_Serial_Impl&); 
    BigUInt_Inf* operator+(const BigUInt_Inf *);
    BigUInt_Inf* operator-(const BigUInt_Inf *);
    BigUInt_Inf* operator*(const BigUInt_Inf *);
    BigUInt_Inf* operator/(const BigUInt_Inf *);
    BigUInt_Inf* operator<<(const BigUInt_Inf *);
    BigUInt_Inf* operator>>(const BigUInt_Inf *);
    BigUInt_Inf* operator&(const BigUInt_Inf *);
    BigUInt_Inf* operator|(const BigUInt_Inf *);
    BigUInt_Inf* operator^(const BigUInt_Inf *);
    BigUInt_Inf* operator~();
    bool operator==(const BigUInt_Inf *);   
    virtual ~BigUInt_Serial_Impl();
};

#endif // _BIG_U_INT_SERIAL_IMPL_H_ 
