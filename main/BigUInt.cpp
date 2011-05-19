#include "BigUInt.h"
#include "BigUInt_Serial_Impl.h"

#define SERIAL 1

using namespace std;

BigUInt::BigUInt()
{
#ifdef SERIAL
    bui = new BigUInt_Serial_Impl();
#elif PARALLEL
    bui = new BigUInt_Parallel_Impl();
#endif
}

BigUInt::BigUInt(const string &str)
{
#ifdef SERIAL
    bui = new BigUInt_Serial_Impl(str);
#elif PARALLEL
    bui = new BigUInt_Parallel_Impl();
#endif
}

BigUInt::~BigUInt()
{
    delete bui;
}

BigUInt
BigUInt::operator+(const BigUInt& op2)
{
    BigUInt_Inf *tempbui;    
#ifdef SERIAL
    tempbui = new BigUInt_Serial_Impl();
#elif PARALLEL
    tempbui = new BigUInt_Parallel_Impl();
#endif

    tempbui = bui->operator+(op2.bui);

    BigUInt temp;
    temp.SetBui(tempbui);
    return temp;
}

BigUInt
BigUInt::operator-(const BigUInt& op2)
{
    BigUInt temp;
    return temp;
}

BigUInt
BigUInt::operator*(const BigUInt& op2)
{

    BigUInt temp;
    return temp;
}

BigUInt
BigUInt::operator/(const BigUInt& op2)
{

    BigUInt temp;
    return temp;
}

BigUInt
BigUInt::operator<<(const BigUInt & op2)
{

    BigUInt temp;
    return temp;
}
 
BigUInt
BigUInt::operator>>(const BigUInt& op2)
{

    BigUInt temp;
    return temp;
}

BigUInt
BigUInt::operator&(const BigUInt& op2)
{

    BigUInt temp;
    return temp;
}

BigUInt
BigUInt::operator|(const BigUInt& op2)
{

    BigUInt temp;
    return temp;
}

BigUInt
BigUInt::operator^(const BigUInt& op2)
{

    BigUInt temp;
    return temp;
}

BigUInt
BigUInt::operator~()
{

    BigUInt temp;
    return temp;
}
   
bool
BigUInt::operator==(const BigUInt& op)
{
    return true;
}

void
BigUInt::SetBui(BigUInt_Inf *b)
{
    bui = b;
}

