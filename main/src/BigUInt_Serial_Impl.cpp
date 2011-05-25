#include "BigUInt_Serial_Impl.h"
#include "BigUInt_Utils.h"

using namespace std;

BigUInt_Serial_Impl::BigUInt_Serial_Impl()
{
	
}

BigUInt_Serial_Impl::BigUInt_Serial_Impl(const string& str)
{
	this->buf = BigUInt_Utils::StringToVector(str);	
}

BigUInt_Serial_Impl::BigUInt_Serial_Impl(const BigUInt_Serial_Impl &to_copy)
{
	vector<unsigned int> buf(to_copy.buf);
	this->buf = buf;
}

BigUInt_Serial_Impl::BigUInt_Serial_Impl(const vector<unsigned int>& buf)
{
    this->buf = buf;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator+(const BigUInt_Inf * op2)
{
    const BigUInt_Serial_Impl* sop2 = dynamic_cast<const BigUInt_Serial_Impl *>(op2);
    vector<unsigned int> num1 = buf;
    vector<unsigned int> num2 = sop2->buf;

    vector<unsigned int> result = BigUInt_Utils::AddBignum(num1, num2);

    BigUInt_Inf* ret = new BigUInt_Serial_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator-(const BigUInt_Inf * op2)
{
    const BigUInt_Serial_Impl* sop2 = dynamic_cast<const BigUInt_Serial_Impl *>(op2);
    vector<unsigned int> num1 = buf;
    vector<unsigned int> num2 = sop2->buf;

    vector<unsigned int> result = BigUInt_Utils::SubtractBignum(num1, num2);
   
    BigUInt_Inf *ret = new BigUInt_Serial_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator*(const BigUInt_Inf * op2)
{
    const BigUInt_Serial_Impl* sop2 = dynamic_cast<const BigUInt_Serial_Impl *>(op2);
    vector<unsigned int> num1 = buf;
    vector<unsigned int> num2 = sop2->buf;

    vector<unsigned int> result = BigUInt_Utils::MultiplyBignum(num1, num2);

    BigUInt_Inf *ret = new BigUInt_Serial_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator/(const BigUInt_Inf * op2)
{
    BigUInt_Inf * temp;
    return temp;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator<<(const unsigned int& op2)
{
    vector<unsigned int> num1 = buf;

    vector<unsigned int> result = BigUInt_Utils::Lshift(num1, op2);

    BigUInt_Inf *ret = new BigUInt_Serial_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator>>(const unsigned int& op2)
{
    vector<unsigned int> num1 = buf;

    vector<unsigned int> result = BigUInt_Utils::Rshift(num1, op2);

    BigUInt_Inf *ret = new BigUInt_Serial_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator&(const BigUInt_Inf * op2)
{
    const BigUInt_Serial_Impl* sop2 = dynamic_cast<const BigUInt_Serial_Impl *>(op2);
    vector<unsigned int> num1 = buf;
    vector<unsigned int> num2 = sop2->buf;

    vector<unsigned int> result = BigUInt_Utils::AndBignum(num1, num2);

    BigUInt_Inf *ret = new BigUInt_Serial_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator|(const BigUInt_Inf * op2)
{
    const BigUInt_Serial_Impl* sop2 = dynamic_cast<const BigUInt_Serial_Impl *>(op2);
    vector<unsigned int> num1 = buf;
    vector<unsigned int> num2 = sop2->buf;

    vector<unsigned int> result = BigUInt_Utils::OrBignum(num1, num2);

    BigUInt_Inf *ret = new BigUInt_Serial_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator^(const BigUInt_Inf * op2)
{
    const BigUInt_Serial_Impl* sop2 = dynamic_cast<const BigUInt_Serial_Impl *>(op2);
    vector<unsigned int> num1 = buf;
    vector<unsigned int> num2 = sop2->buf;

    vector<unsigned int> result = BigUInt_Utils::XorBignum(num1, num2);

    BigUInt_Inf *ret = new BigUInt_Serial_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Serial_Impl::operator~()
{
    vector<unsigned int> num1 = buf;

    vector<unsigned int> result = BigUInt_Utils::NotBignum(num1);

    BigUInt_Inf *ret = new BigUInt_Serial_Impl(result);
    return ret;
}

bool
BigUInt_Serial_Impl::operator==(const BigUInt_Inf * op2)
{
    const BigUInt_Serial_Impl* sop2 = dynamic_cast<const BigUInt_Serial_Impl *>(op2);
    vector<unsigned int> num1 = buf;
    vector<unsigned int> num2 = sop2->buf;

    return BigUInt_Utils::EqualBignum(num1, num2);
}

string
BigUInt_Serial_Impl::ToString()
{
	return BigUInt_Utils::VectorToString(buf);
}

BigUInt_Serial_Impl::~BigUInt_Serial_Impl()
{
	buf.clear();
}

