#include "BigUInt_Parallel_Impl.h"
#include "Common_Utils.h"
#include "BigUInt_Parallel_Utils.h"

//TODO
#include    <iostream>

using namespace std;

BigUInt_Parallel_Impl::BigUInt_Parallel_Impl()
{
    buf.push_back(0);	
}

BigUInt_Parallel_Impl::BigUInt_Parallel_Impl(const string& str)
{
	this->buf = Common_Utils::StringToVector(str);	
    /* std::cout << "----------";
    for (int i=0; i < this->buf.size(); i++)    
        std::cout << this->buf[i] << "\t";*/
}

BigUInt_Parallel_Impl::BigUInt_Parallel_Impl(const BigUInt_Parallel_Impl &to_copy)
{
	vector<uint32_t> buf(to_copy.buf);
	this->buf = buf;
}

BigUInt_Parallel_Impl::BigUInt_Parallel_Impl(const vector<uint32_t>& buf)
{
    this->buf = buf;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator=(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    buf = sop2->buf;
    BigUInt_Inf* ret = new BigUInt_Parallel_Impl(buf);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator+(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<uint32_t> num1 = buf;
    vector<uint32_t> num2 = sop2->buf;

    vector<uint32_t> result = BigUInt_Parallel_Utils::AddBignum(num1, num2);

    BigUInt_Inf* ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator-(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<uint32_t> num1 = buf;
    vector<uint32_t> num2 = sop2->buf;

    vector<uint32_t> result = BigUInt_Parallel_Utils::SubtractBignum(num1, num2);
   
    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator*(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<uint32_t> num1 = buf;
    vector<uint32_t> num2 = sop2->buf;

    vector<uint32_t> result = BigUInt_Parallel_Utils::MultiplyBignum(num1, num2);

    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator/(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<uint32_t> num1 = buf;
    vector<uint32_t> num2 = sop2->buf;

    vector<uint32_t> result = BigUInt_Parallel_Utils::DivideBignum(num1, num2);

    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator<<(const uint32_t& op2)
{
    vector<uint32_t> num1 = buf;

    vector<uint32_t> result = BigUInt_Parallel_Utils::Lshift(num1, op2);

    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator>>(const uint32_t& op2)
{
    vector<uint32_t> num1 = buf;

    vector<uint32_t> result = BigUInt_Parallel_Utils::Rshift(num1, op2);

    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator&(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<uint32_t> num1 = buf;
    vector<uint32_t> num2 = sop2->buf;

    vector<uint32_t> result = BigUInt_Parallel_Utils::AndBignum(num1, num2);

    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator|(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<uint32_t> num1 = buf;
    vector<uint32_t> num2 = sop2->buf;

    vector<uint32_t> result = BigUInt_Parallel_Utils::OrBignum(num1, num2);

    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator^(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<uint32_t> num1 = buf;
    vector<uint32_t> num2 = sop2->buf;

    vector<uint32_t> result = BigUInt_Parallel_Utils::XorBignum(num1, num2);

    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator~()
{
    vector<uint32_t> num1 = buf;

    vector<uint32_t> result = BigUInt_Parallel_Utils::NotBignum(num1);

    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

bool
BigUInt_Parallel_Impl::operator==(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<uint32_t> num1 = buf;
    vector<uint32_t> num2 = sop2->buf;

    return BigUInt_Parallel_Utils::EqualBignum(num1, num2);
}

bool
BigUInt_Parallel_Impl::operator>(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<uint32_t> num1 = buf;
    vector<uint32_t> num2 = sop2->buf;

    return BigUInt_Parallel_Utils::GreaterThan(num1, num2);
}

bool
BigUInt_Parallel_Impl::operator<(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<uint32_t> num1 = buf;
    vector<uint32_t> num2 = sop2->buf;

    return BigUInt_Parallel_Utils::LessThan(num1, num2);
}

string
BigUInt_Parallel_Impl::ToString()
{
	return Common_Utils::VectorToString(buf);
}

BigUInt_Parallel_Impl::~BigUInt_Parallel_Impl()
{
	buf.clear();
}

