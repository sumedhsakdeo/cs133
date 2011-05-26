#ifndef _BIG_U_INT_PARALLEL_IMPL_H_
#define _BIG_U_INT_PARALLEL_IMPL_H_

#include <vector>
#include <string>
extern "C" {
#include <stdint.h>
}

#include "BigUInt_Inf.h"

class BigUInt_Parallel_Impl : public BigUInt_Inf {    
private:
    std::vector<uint32_t> buf;
public:
    BigUInt_Parallel_Impl(); 
    BigUInt_Parallel_Impl(const std::string&); 
    BigUInt_Parallel_Impl(const BigUInt_Parallel_Impl&); 
    BigUInt_Parallel_Impl(const std::vector<uint32_t>& buf);
    BigUInt_Inf* operator=(const BigUInt_Inf *);
    BigUInt_Inf* operator+(const BigUInt_Inf *);
    BigUInt_Inf* operator-(const BigUInt_Inf *);
    BigUInt_Inf* operator*(const BigUInt_Inf *);
    BigUInt_Inf* operator/(const BigUInt_Inf *);
    BigUInt_Inf* operator<<(const uint32_t&);
    BigUInt_Inf* operator>>(const uint32_t&);
    BigUInt_Inf* operator&(const BigUInt_Inf *);
    BigUInt_Inf* operator|(const BigUInt_Inf *);
    BigUInt_Inf* operator^(const BigUInt_Inf *);
    BigUInt_Inf* operator~();
    bool operator==(const BigUInt_Inf *);
	std::string ToString();
    virtual ~BigUInt_Parallel_Impl();
};

#endif // _BIG_U_INT_PARALLEL_IMPL_H_ 
