#include "BigUInt_Utils.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

vector<unsigned int>
BigUInt_Utils::string_to_vector(const string &str)
{
	long base;
    vector<unsigned int> representation;
    long dividend = 0;
    string quotient;
    string input(str); 

    base = INT_MAX;
    base++;

    do
    {
        while (input.length() > 0)
        {
            while (dividend < base && input.length() > 0)
            {
                dividend = dividend * 10 + (input[0] - 48);
                input.erase(input.begin());
            }
            //now we have a number in dividend that is just greater than base
            quotient.push_back((dividend / base) + 48);
            dividend = dividend % base;
        }
        //dividend contains remainder, quotient is a string that contains quotient
        input.assign(quotient);
        quotient = "";
		  representation.insert(representation.begin(), dividend);
        dividend = 0;
    } while (!(input.length() == 1 && input[0] == '0'));

	return representation;
}

string
ltoa(long arg)
{
    std::string number;
    std::stringstream strstream;
    strstream << arg;
    strstream >> number;
    return number;
}

void
mult(const long num, string& str)
{
    long carry = 0;
    for (int i = str.length() - 1 ; i >= 0; --i) {
        long digit = str.at(i) - 48;
        digit = carry + digit * num;
        carry = digit / 10;
        digit = digit % 10;
        str.at(i) = (char) (digit + 48);
    }

    while (carry != 0) {
        str.insert(0, 1, (char) ((carry % 10) + 48));
        carry = carry / 10;
    }
}

void
add(int num, string& str)
{
    int i = str.length() - 1;
    int carry = 0;
    while (num != 0) {
        int digit = str.at(i) - 48;
        digit = digit + (num % 10) + carry;
        num = num / 10;
        carry = digit / 10;
        digit = digit % 10;
        str.at(i) = (char) (digit + 48);
        --i;
    }

    while (carry != 0) {
        if (i == -1) {
            str.insert(0, 1, (char) (carry + 48));
            carry = 0;
        } else {
            int digit = str.at(i) - 48;
            digit += carry;
            carry = digit / 10;
            digit = digit % 10;
            str.at(i) = (char) (digit + 48);
            --i;
        }
    }
}

string
BigUInt_Utils::vector_to_string(const vector<unsigned int>& buf)
{
    long base;
    base = INT_MAX;
    base++;

    string output("");
    output = ltoa(buf.at(0));
    for (int i = 1; i < buf.size(); i++)
    {
        mult(base, output);
        add(buf.at(i), output);
    }

    return output;
}

vector<unsigned>
BigUInt_Utils::AddBignum(vector<unsigned>& num1, vector<unsigned>& num2)
{
    unsigned limit = (num1.size()>num2.size()) ? num2.size() : num1.size();
    unsigned long temp = 0;
    unsigned carry = 0;
    int i;
    vector<unsigned> result;

    for (i = 0; i < limit; i++) {
        temp = (unsigned long) num1.at(i) + num2.at(i) + carry;
        carry = 0;
        if (temp > UINT_MAX) {
            temp -= (UINT_MAX + 1);
            carry = 1;
        }
        result.push_back((unsigned) temp);
    }

    if (num1.size() > limit) {
        while (i < num1.size()) {
            temp = num1.at(i) + carry;
            carry = 0;

            if (temp > UINT_MAX) {
                temp -= (UINT_MAX + 1);
                carry = 1;
            }

            result.push_back((unsigned) temp);
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

            result.push_back((unsigned) temp);
            i++;
        }
    }

    if (carry != 0) {
        result.push_back(1);
    }
    
    return result;
}

vector<unsigned>
BigUInt_Utils::SubtractBignum(vector<unsigned>& num1, vector<unsigned>& num2)
{
    vector<unsigned> result;
    unsigned borrow = 0;
    unsigned newborrow = 0;
    unsigned long temp;
    unsigned limit = (num1.size()>num2.size()) ? num2.size() : num1.size();
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
        result.push_back((unsigned) temp);
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
            result.push_back((unsigned) temp);
            i++;
        }
    }

    //clean up 0s from head
    while (result.size() != 0 && result.back() == 0) {
        result.pop_back();
    }

    return result;

}

vector<unsigned>
BigUInt_Utils::MultiplyBignum(vector<unsigned>& num1, vector<unsigned>& num2)
{
    vector <unsigned> result;
    //using vedic math urdhwatiryak method

    //first pad zeros to make the input vectors equal sized
    if (num1.size() > num2.size()) {
        while (num1.size() != num2.size()) {
            num2.push_back(0);
        }
    } else if (num2.size() > num1.size()) {
        while (num2.size() != num1.size()) num1.push_back(0);
    }

    unsigned numOps = 0;
    for (int i = 0; i < ((2 * num1.size()) - 1); i++) {
        vector <unsigned> intermediate;

        unsigned index1;
        unsigned index2;

        (i < num1.size()) ? numOps++ : numOps--;

        if (i < num1.size()) {
            index1 = 0;
            index2 = numOps - 1;
        } else {
            index1 = num1.size() - numOps;
            index2 = num1.size() - 1;
        }

        for (int j = 0; j < numOps; j++) {
            unsigned long temp = (unsigned long) num1.at(index1) * num2.at(index2);
            vector <unsigned> tmp;
            unsigned long base = UINT_MAX;
            base++;

            if (!(temp / base == 0 && temp % base == 0)) {
                tmp.push_back((unsigned) (temp % base));
            }

            if (temp / base != 0) {
                tmp.push_back((unsigned) (temp / base));
            }

            intermediate = AddBignum(tmp, intermediate);
        
            index1++;
            index2--;
        }

        //shift unsignedermediate to left by i unsigneds
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

vector<unsigned> 
BigUInt_Utils::AndBignum(vector<unsigned>& num1, vector<unsigned>& num2)
{
    vector <unsigned> result;
    unsigned limit = (num1.size() > num2.size()) ? num2.size() : num1.size();

    for (int i = 0; i < limit; i++) {
        unsigned temp = num1.at(i) & num2.at(i);
        result.push_back(temp);
    }

    //we ignore the rest, and also not pad with zeros because in our representation, padded zeros are not allowed.

    while (result.size() != 0 && result.back() == 0) {
        result.pop_back();
    }

    return result;
}

vector<unsigned>
BigUInt_Utils::OrBignum(vector<unsigned>& num1, vector<unsigned>& num2)
{
    vector <unsigned> result;
    unsigned limit = (num1.size() > num2.size()) ? num2.size() : num1.size();
    int i;

    for (i = 0; i < limit; i++) {
        unsigned temp = num1.at(i) | num2.at(i);
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

vector<unsigned>
BigUInt_Utils::XorBignum(vector<unsigned>& num1, vector<unsigned>& num2)
{
    vector <unsigned> result;
    unsigned limit = (num1.size() > num2.size()) ? num2.size() : num1.size();
    int i;

    for (i = 0; i < limit; i++) {
        unsigned temp = num1.at(i) ^ num2.at(i);
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

vector<unsigned> 
BigUInt_Utils::NotBignum(vector<unsigned>& num1)
{
    vector <unsigned> result;
    
    for (int i = 0; i < num1.size(); i++) {
        unsigned temp = ~num1.at(i);
        result.push_back(temp);
    }

    //just for sanity, though not really required
    while (result.size() != 0 && result.back() == 0) {
        result.pop_back();
    }

    return result;
}

bool
BigUInt_Utils::EqualBignum(vector<unsigned>& num1, vector<unsigned>& num2)
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

vector<unsigned>
BigUInt_Utils::Lshift(vector<unsigned>& num1, const unsigned& shift)
{
    vector <unsigned> result;
    int bitsindigit = sizeof(unsigned) * 8;
    long mask = pow((double) 2, bitsindigit) - 1;

    int newdigits = shift / bitsindigit;
    int inshift = shift % bitsindigit;

    for (int i = 0; i < newdigits; i++) {
        result.push_back(0);
    }

    long temp = 0;
    for (int i = 0; i < num1.size(); i++) {
        temp += (long) ( (long) num1.at(i) << inshift);
        result.push_back((unsigned) (temp & mask));
        temp = temp >> bitsindigit;
    }

    if (temp != 0) {
        result.push_back((unsigned) temp);
    }

    return result;
}

vector<unsigned>
BigUInt_Utils::Rshift(vector<unsigned>& num1, const unsigned& shift)
{
    vector <unsigned> result;
    int bitsindigit = sizeof(unsigned) * 8;
    long mask = (long) (pow((double) 2, bitsindigit) - 1) << bitsindigit;

    int newdigits = shift / bitsindigit;
    int inshift = shift % bitsindigit;

    unsigned long temp = 0;
    for (int i = num1.size() - 1; i >= newdigits; i--) {
        temp += (unsigned long) ( (unsigned long) num1.at(i) << bitsindigit) >> inshift;
        result.push_back((unsigned) (temp >> bitsindigit));
        temp = temp << bitsindigit;
    }
    
    reverse(result.begin(), result.end());
    while (result.size() != 0 && result.back() == 0) {
        result.pop_back();
    }

    return result;
}

