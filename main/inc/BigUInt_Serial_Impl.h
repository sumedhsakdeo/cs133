#ifndef _BIG_U_INT_SERIAL_IMPL_H_
#define _BIG_U_INT_SERIAL_IMPL_H_

#include <vector>
#include <string>
extern "C" {
#include <stdint.h>
}

#include "BigUInt_Inf.h"

class BigUInt_Serial_Impl : public BigUInt_Inf {    
private:
    std::vector<uint32_t> buf;
public:
    BigUInt_Serial_Impl(); 
    BigUInt_Serial_Impl(const std::string&); 
    BigUInt_Serial_Impl(const BigUInt_Serial_Impl&); 
    BigUInt_Serial_Impl(const std::vector<uint32_t>& buf);
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
    bool operator>(const BigUInt_Inf *);
    bool operator<(const BigUInt_Inf *);
	std::string ToString();
    virtual ~BigUInt_Serial_Impl();
};

#endif // _BIG_U_INT_SERIAL_IMPL_H_ 
