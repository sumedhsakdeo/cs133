#include    "BigUInt_Parallel_Impl.h"
#include	"BigUInt_Utils.h"

using namespace std;

BigUInt_Parallel_Impl::BigUInt_Parallel_Impl()
{
}

BigUInt_Parallel_Impl::BigUInt_Parallel_Impl(const string &str)
{
	this->buf = BigUInt_Utils::string_to_vector(str);	
}

BigUInt_Parallel_Impl::BigUInt_Parallel_Impl(const BigUInt_Parallel_Impl &to_copy)
{
	vector<unsigned int> buf(to_copy.buf);
	this->buf = buf;
}

BigUInt_Parallel_Impl::BigUInt_Parallel_Impl(const vector<unsigned int>& buf)
{
    this->buf = buf;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator+(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<unsigned int> num1 = buf;
    vector<unsigned int> num2 = sop2->buf;

    vector<unsigned int> result = BigUInt_Utils::AddBignum(num1, num2);

    BigUInt_Inf* ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator-(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<unsigned int> num1 = buf;
    vector<unsigned int> num2 = sop2->buf;

    vector<unsigned int> result = BigUInt_Utils::SubtractBignum(num1, num2);
   
    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator*(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<unsigned int> num1 = buf;
    vector<unsigned int> num2 = sop2->buf;

    vector<unsigned int> result = BigUInt_Utils::MultiplyBignum(num1, num2);

    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator/(const BigUInt_Inf * op2)
{
    BigUInt_Inf * temp;
    return temp;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator<<(const unsigned int& op2)
{
    vector<unsigned int> num1 = buf;

    vector<unsigned int> result = BigUInt_Utils::Lshift(num1, op2);

    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator>>(const unsigned int& op2)
{
    vector<unsigned int> num1 = buf;

    vector<unsigned int> result = BigUInt_Utils::Rshift(num1, op2);

    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator&(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<unsigned int> num1 = buf;
    vector<unsigned int> num2 = sop2->buf;

    vector<unsigned int> result = BigUInt_Utils::AndBignum(num1, num2);

    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator|(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<unsigned int> num1 = buf;
    vector<unsigned int> num2 = sop2->buf;

    vector<unsigned int> result = BigUInt_Utils::OrBignum(num1, num2);

    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator^(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<unsigned int> num1 = buf;
    vector<unsigned int> num2 = sop2->buf;

    vector<unsigned int> result = BigUInt_Utils::XorBignum(num1, num2);

    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

BigUInt_Inf *
BigUInt_Parallel_Impl::operator~()
{
    vector<unsigned int> num1 = buf;

    vector<unsigned int> result = BigUInt_Utils::NotBignum(num1);

    BigUInt_Inf *ret = new BigUInt_Parallel_Impl(result);
    return ret;
}

bool
BigUInt_Parallel_Impl::operator==(const BigUInt_Inf * op2)
{
    const BigUInt_Parallel_Impl* sop2 = dynamic_cast<const BigUInt_Parallel_Impl *>(op2);
    vector<unsigned int> num1 = buf;
    vector<unsigned int> num2 = sop2->buf;

    return BigUInt_Utils::EqualBignum(num1, num2);
}

BigUInt_Parallel_Impl::~BigUInt_Parallel_Impl()
{

}

