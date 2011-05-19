#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main()
{
    long base = 32768;
    string input;

    cin >> input;
    
    vector<int> representation;

    long dividend = 0;
    string quotient;
   
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
        representation.push_back(dividend);
        dividend = 0;
    } while (!(input.length() == 1 && input[0] == '0'));

    for (int i = 0; i < representation.size(); i++)
    {
        cout<<representation.at(i)<<endl;
    }

    //cout << input;

    return 0;
}
