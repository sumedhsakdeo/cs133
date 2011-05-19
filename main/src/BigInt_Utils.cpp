#include	"BigInt_Utils.h"
#include	<limits.h>

using namespace std;

vector<int> BigInt_Utils :: string_to_vector (const string &str)	{
	
	 long base = INT_MAX + 1L;
    vector<int> representation;
    long dividend = 0;
    string quotient;
    string input(str); 

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
