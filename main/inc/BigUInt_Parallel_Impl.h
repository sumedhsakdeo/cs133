#ifndef _BIG_U_INT_SERIAL_IMPL_H_
#define _BIG_U_INT_SERIAL_IMPL_H_

#include <vector>
#include <string>

#include "BigUInt_Inf.h"

class BigUInt_Parallel_Impl : public BigUInt_Inf {    
private:
    std::vector<unsigned int> buf;
public:
    BigUInt_Parallel_Impl(); 
    BigUInt_Parallel_Impl(const std::string&); 
    BigUInt_Parallel_Impl(const BigUInt_Parallel_Impl&); 
    BigUInt_Parallel_Impl(const std::vector<unsigned int>& buf);
    BigUInt_Inf* operator+(const BigUInt_Inf *);
    BigUInt_Inf* operator-(const BigUInt_Inf *);
    BigUInt_Inf* operator*(const BigUInt_Inf *);
    BigUInt_Inf* operator/(const BigUInt_Inf *);
    BigUInt_Inf* operator<<(const unsigned int&);
    BigUInt_Inf* operator>>(const unsigned int&);
    BigUInt_Inf* operator&(const BigUInt_Inf *);
    BigUInt_Inf* operator|(const BigUInt_Inf *);
    BigUInt_Inf* operator^(const BigUInt_Inf *);
    BigUInt_Inf* operator~();
    bool operator==(const BigUInt_Inf *);   
    virtual ~BigUInt_Parallel_Impl();
};

#endif // _BIG_U_INT_SERIAL_IMPL_H_ 
