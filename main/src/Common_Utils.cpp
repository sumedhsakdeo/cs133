#include "Common_Utils.h"
#include <sstream>
#include <climits>
#include <algorithm>
#include <cmath>
extern "C" {
#include <stdint.h>
}
using namespace std;

string
ltoa(uint64_t arg)
{
    std::string number;
    std::stringstream strstream;
    strstream << arg;
    strstream >> number;
    return number;
}

void
mult(const uint64_t num, string* str)
{
    uint64_t carry = 0;
    for (int i = str->length() - 1 ; i >= 0; i--) {
        uint64_t digit = str->at(i) - 48;
        digit = carry + digit * num;
        carry = digit / 10;
        digit = digit % 10;
        str->at(i) = (char) (digit + 48);
    }

    while (carry != 0) {
        str->insert(0, 1, (char) ((carry % 10) + 48));
        carry = carry / 10;
    }
}

void
add(uint32_t num, string* str)
{
    uint32_t i = str->size() - 1;
    uint32_t carry = 0;

    while (num != 0) {
        uint32_t digit = str->at(i) - 48;
        digit = digit + (num % 10) + carry;
        num = num / 10;
        carry = digit / 10;
        digit = digit % 10;
        str->at(i) = (char) (digit + 48);
        i--;
    }

    while (carry != 0) {
        if (i == -1) {
            str->insert(0, 1, (char) (carry + 48));
            carry = 0;
        } else {
            uint32_t digit = str->at(i) - 48;
            digit += carry;
            carry = digit / 10;
            digit = digit % 10;
            str->at(i) = (char) (digit + 48);
            --i;
        }
    }
}

vector<uint32_t>
Common_Utils::StringToVector(const string& str)
{
    uint64_t base;
    vector<uint32_t> representation;
    string input(str); 

    base = UINT_MAX;
    base++;

    uint64_t dividend = 0;
    string quotient;

    do
    {
        bool firstflag = false;
        while (input.length() > 0) {
            if (firstflag == false) {
                while (dividend < base && input.length() > 0) {
                    dividend = dividend * 10 + (input[0] - 48);
                    input.erase(input.begin());
                    firstflag = true;
                }
            } else if (input.length() > 0) {
                dividend = dividend * 10 + (input[0] - 48);
                input.erase(input.begin());
            }

            //now we have a number in dividend that is just greater than base
            quotient.push_back((dividend / base) + 48);
            dividend = dividend % base;
        }

        //dividend contains remainder, quotient is a string that contains quotient
        input.clear();
        input.assign(quotient);
        quotient.clear();
        representation.push_back(dividend);
        dividend = 0;
    } while (!(input.length() == 1 && input[0] == '0'));

    return representation;
}

string
Common_Utils::VectorToString(const vector<uint32_t>& buf)
{
    if (buf.size() == 0) {
        return string();
    }

    vector<uint32_t> num = buf; 
    reverse(num.begin(), num.end());

    uint64_t base = UINT_MAX;
    base++;

    string* output = new string("");
    *output = ltoa(num.at(0));
    for (int i = 1; i < num.size(); ++i) {
        mult(base, output);
        add(num.at(i), output);
    }

    return *output;
}
