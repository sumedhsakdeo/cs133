#include "BigUInt_Serial_Impl.h"

using namespace std;

BigUInt_Serial_Impl::BigUInt_Serial_Impl()
{
	
}

BigUInt_Serial_Impl::BigUInt_Serial_Impl(const string &str)
{
	this->buf = BigInt_Utils::string_to_vector(str);	
}

BigUInt_Serial_Impl::BigUInt_Serial_Impl(const BigUInt_Serial_Impl &to_copy)
{
	vector<int> buf(to_copy.buf);
	this->buf = buf;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator+(const BigUInt_Inf * op2)
{
    BigUInt_Inf* temp;
    return temp;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator-(const BigUInt_Inf * op2)
{
    BigUInt_Inf * temp;
    return temp;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator*(const BigUInt_Inf * op2)
{
    BigUInt_Inf * temp;
    return temp;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator/(const BigUInt_Inf * op2)
{
    BigUInt_Inf * temp;
    return temp;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator<<(const BigUInt_Inf * op2)
{
    BigUInt_Inf * temp;
    return temp;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator>>(const BigUInt_Inf * op2)
{
    BigUInt_Inf * temp;
    return temp;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator&(const BigUInt_Inf * op2)
{
    BigUInt_Inf * temp;
    return temp;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator|(const BigUInt_Inf * op2)
{
    BigUInt_Inf * temp;
    return temp;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator^(const BigUInt_Inf * op2)
{
    BigUInt_Inf * temp;
    return temp;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator~()
{
    BigUInt_Inf * temp;
    return temp;
}

bool
BigUInt_Serial_Impl::operator==(const BigUInt_Inf * op2)
{
    return true;
}

BigUInt_Serial_Impl::~BigUInt_Serial_Impl()
{
}

