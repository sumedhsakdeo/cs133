#include "BigInt_Utils.h"
#include <string>
#include <sstream>
#include <climits>

using namespace std;

vector<int>
BigInt_Utils::string_to_vector(const string &str)
{
	long base;
    vector<int> representation;
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
BigInt_Utils::vector_to_string(const vector<int>& buf)
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
