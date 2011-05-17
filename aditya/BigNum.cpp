#include "BigNum.h"
#include <iostream>

using namespace std;

BigNum::BigNum(const char* num)
{
    this->size = strlen(num) + 1;
    this->arr = new char[this->size];
    strcpy(this->arr, num);
}

BigNum::BigNum(const BigNum &oper)
{

}

BigNum BigNum::operator+(const BigNum &oper)
{

}

BigNum BigNum::operator-(const BigNum &oper)
{

}

BigNum BigNum::operator*(const BigNum &oper)
{

}

BigNum BigNum::operator/(const BigNum &oper)
{

}

BigNum BigNum::operator<<(const BigNum &oper)
{

}

BigNum BigNum::operator>>(const BigNum &oper)
{

}

BigNum BigNum::operator&(const BigNum &oper)
{

}

BigNum BigNum::operator|(const BigNum &oper)
{

}
 
BigNum BigNum::operator^(const BigNum &oper)
{

}
 
BigNum BigNum::operator~()
{

}

BigNum BigNum::operator==(const BigNum &oper)
{

}

void BigNum::print()
{
    cout<<arr;
}
