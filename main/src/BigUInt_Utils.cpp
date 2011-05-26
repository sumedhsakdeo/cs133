#include "BigUInt_Utils.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <climits>
#include <cmath>
extern "C" {
#include <stdint.h>
}

using namespace std;

vector<uint32_t>
BigUInt_Utils::StringToVector(const string& str)
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

string
BigUInt_Utils::VectorToString(const vector<uint32_t>& buf)
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

vector<uint32_t>
BigUInt_Utils::AddBignum(vector<uint32_t>& num1, vector<uint32_t>& num2)
{
    uint32_t limit = (num1.size()>num2.size()) ? num2.size() : num1.size();
    uint64_t temp = 0;
    uint32_t carry = 0;
    int i;
    vector<uint32_t> result;

    for (i = 0; i < limit; i++) {
        temp = (uint64_t) num1.at(i) + num2.at(i) + carry;
        carry = 0;
        if (temp > UINT_MAX) {
            temp -= (UINT_MAX + 1);
            carry = 1;
        }
        result.push_back((uint32_t) temp);
    }

    if (num1.size() > limit) {
        while (i < num1.size()) {
            temp = num1.at(i) + carry;
            carry = 0;

            if (temp > UINT_MAX) {
                temp -= (UINT_MAX + 1);
                carry = 1;
            }

            result.push_back((uint32_t) temp);
            i++;
        }
    }

    if (num2.size() > limit) {
        while (i < num2.size()) {
            temp = num2.at(i) + carry;
            carry = 0;

            if (temp > UINT_MAX) {
                temp -= (UINT_MAX + 1);
                carry = 1;
            }

            result.push_back((uint32_t) temp);
            i++;
        }
    }

    if (carry != 0) {
        result.push_back(1);
    }
    
    return result;
}

vector<uint32_t>
BigUInt_Utils::SubtractBignum(vector<uint32_t>& num1, vector<uint32_t>& num2)
{
    vector<uint32_t> result;
    uint32_t borrow = 0;
    uint32_t newborrow = 0;
    uint64_t temp;
    uint32_t limit = (num1.size()>num2.size()) ? num2.size() : num1.size();
    int i;

    //just checking that num1 > num2, else return empty
    if (num1.size() < num2.size()) {
        return result;
    }

    if (num1.size() == num2.size()
        && num1.at(num1.size() - 1) < num2.at(num2.size() - 1)) {
        return result;
    }

    for (i = 0; i < limit; i++) {
        temp = num1.at(i);

        if (num1.at(i) < (num2.at(i) + borrow)) {
            temp += UINT_MAX + 1;
            newborrow = 1;
        } else {
            newborrow = 0;
        }

        temp -= (num2.at(i) + borrow);
        borrow = newborrow;
        result.push_back((uint32_t) temp);
    }
        
    if (num1.size() > limit) {
        while (i < num1.size()) {
            temp = num1.at(i);

            if (num1.at(i) < borrow) {
                temp += UINT_MAX + 1;
                newborrow = 1;
            } else {
                newborrow = 0;
            }

            temp -= borrow;
            borrow = newborrow;
            result.push_back((uint32_t) temp);
            i++;
        }
    }

    //clean up 0s from head
    while (result.size() != 0 && result.back() == 0) {
        result.pop_back();
    }

    return result;

}

vector<uint32_t>
BigUInt_Utils::MultiplyBignum(vector<uint32_t>& num1, vector<uint32_t>& num2)
{
    vector <uint32_t> result;
    //using vedic math urdhwatiryak method

    //first pad zeros to make the input vectors equal sized
    if (num1.size() > num2.size()) {
        while (num1.size() != num2.size()) {
            num2.push_back(0);
        }
    } else if (num2.size() > num1.size()) {
        while (num2.size() != num1.size()) num1.push_back(0);
    }

    uint32_t numOps = 0;
    for (int i = 0; i < ((2 * num1.size()) - 1); i++) {
        vector <uint32_t> intermediate;

        uint32_t index1;
        uint32_t index2;

        (i < num1.size()) ? numOps++ : numOps--;

        if (i < num1.size()) {
            index1 = 0;
            index2 = numOps - 1;
        } else {
            index1 = num1.size() - numOps;
            index2 = num1.size() - 1;
        }

        for (int j = 0; j < numOps; j++) {
            uint64_t temp = (uint64_t) num1.at(index1) * num2.at(index2);
            vector <uint32_t> tmp;
            uint64_t base = UINT_MAX;
            base++;

            if (!(temp / base == 0 && temp % base == 0)) {
                tmp.push_back((uint32_t) (temp % base));
            }

            if (temp / base != 0) {
                tmp.push_back((uint32_t) (temp / base));
            }

            intermediate = AddBignum(tmp, intermediate);
        
            index1++;
            index2--;
        }

        //shift uint32_termediate to left by i uint32_ts
        if (intermediate.size() > 0) {
            for (int j = 0; j < i; j++) {
                intermediate.insert(intermediate.begin(), 1, 0);
            }
        }

        result = AddBignum(intermediate, result);
    }

    //undo padding!
    while (num1.size() != 0 && num1.back() == 0) {
        num1.pop_back();
    }

    while (num2.size() != 0 && num2.back() == 0) {
        num2.pop_back();
    }

    return result;
}

vector<uint32_t> 
BigUInt_Utils::AndBignum(vector<uint32_t>& num1, vector<uint32_t>& num2)
{
    vector <uint32_t> result;
    uint32_t limit = (num1.size() > num2.size()) ? num2.size() : num1.size();

    for (int i = 0; i < limit; i++) {
        uint32_t temp = num1.at(i) & num2.at(i);
        result.push_back(temp);
    }

    //we ignore the rest, and also not pad with zeros because in our representation, padded zeros are not allowed.

    while (result.size() != 0 && result.back() == 0) {
        result.pop_back();
    }

    return result;
}

vector<uint32_t>
BigUInt_Utils::OrBignum(vector<uint32_t>& num1, vector<uint32_t>& num2)
{
    vector <uint32_t> result;
    uint32_t limit = (num1.size() > num2.size()) ? num2.size() : num1.size();
    int i;

    for (i = 0; i < limit; i++) {
        uint32_t temp = num1.at(i) | num2.at(i);
        result.push_back(temp);
    }

    if (limit < num1.size()) {
        while (i < num1.size()) {
            result.push_back(num1.at(i));
            i++;
        }
    } else if (limit < num2.size()) {
        while (i < num2.size()) {
            result.push_back(num2.at(i));
            i++;
        }
    }

    //just for sanity, though not really required
    while (result.size() != 0 && result.back() == 0) {
        result.pop_back();
    }
    
    return result;
}

vector<uint32_t>
BigUInt_Utils::XorBignum(vector<uint32_t>& num1, vector<uint32_t>& num2)
{
    vector <uint32_t> result;
    uint32_t limit = (num1.size() > num2.size()) ? num2.size() : num1.size();
    int i;

    for (i = 0; i < limit; i++) {
        uint32_t temp = num1.at(i) ^ num2.at(i);
        result.push_back(temp);
    }

    if (limit < num1.size()) {
        while (i < num1.size()) {
            result.push_back(num1.at(i));
            i++;
        }
    } else if (limit < num2.size()) {
        while (i < num2.size()) {
            result.push_back(num2.at(i));
            i++;
        }
    }

    //just for sanity, though not really required
    while (result.size() != 0 && result.back() == 0) {
        result.pop_back();
    }

    return result;
}

vector<uint32_t> 
BigUInt_Utils::NotBignum(vector<uint32_t>& num1)
{
    vector <uint32_t> result;
    
    for (int i = 0; i < num1.size(); i++) {
        uint32_t temp = ~num1.at(i);
        result.push_back(temp);
    }

    //just for sanity, though not really required
    while (result.size() != 0 && result.back() == 0) {
        result.pop_back();
    }

    return result;
}

bool
BigUInt_Utils::EqualBignum(vector<uint32_t>& num1, vector<uint32_t>& num2)
{
    //removing zero padding, just in case
    while (num1.size() != 0 && num1.back() == 0){
        num1.pop_back();
    }

    while (num2.size() != 0 && num2.back() == 0){
        num2.pop_back();
    }

    if (num1.size() != num2.size()) {
        return false;
    }

    for (int i = 0; i < num1.size(); i++) {
        if (num1.at(i) != num2.at(i)) return false;
    }
    
    return true;
}

vector<uint32_t>
BigUInt_Utils::Lshift(vector<uint32_t>& num1, const uint32_t& shift)
{
    vector <uint32_t> result;
    int bitsindigit = sizeof(uint32_t) * 8;
    uint64_t mask = pow((double) 2, bitsindigit) - 1;

    int newdigits = shift / bitsindigit;
    int inshift = shift % bitsindigit;

    for (int i = 0; i < newdigits; i++) {
        result.push_back(0);
    }

    uint64_t temp = 0;
    for (int i = 0; i < num1.size(); i++) {
        temp += (uint64_t) ( (uint64_t) num1.at(i) << inshift);
        result.push_back((uint32_t) (temp & mask));
        temp = temp >> bitsindigit;
    }

    if (temp != 0) {
        result.push_back((uint32_t) temp);
    }

    return result;
}

vector<uint32_t>
BigUInt_Utils::Rshift(vector<uint32_t>& num1, const uint32_t& shift)
{
    vector <uint32_t> result;
    int bitsindigit = sizeof(uint32_t) * 8;
    uint64_t mask = (uint64_t) (pow((double) 2, bitsindigit) - 1) << bitsindigit;

    int newdigits = shift / bitsindigit;
    int inshift = shift % bitsindigit;

    uint64_t temp = 0;
    for (int i = num1.size() - 1; i >= newdigits; i--) {
        temp += (uint64_t) ( (uint64_t) num1.at(i) << bitsindigit) >> inshift;
        result.push_back((uint32_t) (temp >> bitsindigit));
        temp = temp << bitsindigit;
    }
    
    reverse(result.begin(), result.end());
    while (result.size() != 0 && result.back() == 0) {
        result.pop_back();
    }

    return result;
}

