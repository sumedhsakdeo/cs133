#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string ltoa(long arg)
{
    std::string number;
    std::stringstream strstream;
    strstream << arg;
    strstream >> number;
    return number;
}

void mult(const long num, string* str)
{
    long carry = 0;
    for (int i = str->length() - 1 ; i >= 0; i--)
    {
        long digit = str->at(i) - 48;
        digit = carry + digit * num;
        carry = digit / 10;
        digit = digit % 10;
        str->at(i) = (char) (digit + 48);
    }
    while (carry != 0)
    {
        str->insert(0, 1, (char) ((carry % 10) + 48));
        carry = carry / 10;
    }
}

void add(int num, string* str)
{
    int i = str->size() - 1;
    int carry = 0;
    while (num != 0)
    {
        int digit = str->at(i) - 48;
        digit = digit + (num % 10) + carry;
        num = num / 10;
        carry = digit / 10;
        digit = digit % 10;
        str->at(i) = (char) (digit + 48);
        i--;
    }
    while (carry != 0)
    {
        if (i == -1)
        {
            str->insert(0, 1, (char) (carry + 48));
            carry = 0;
        }
        else 
        {
            int digit = str->at(i) - 48;
            digit += carry;
            carry = digit / 10;
            digit = digit % 10;
            str->at(i) = (char) (digit + 48);
            --i;
        }
    }
}


int main()
{
    vector<int> num;
    num.push_back(32767);
    num.push_back(32767);
    num.push_back(32767);

    long base = 32768;

    string* output = new string("");
    *output = ltoa(num.at(0));
    for (int i = 1; i < num.size(); i++)
    {
        mult(base, output);
        add(num.at(i), output);
    }

    cout<<*output<<endl;

    return 0;
}
