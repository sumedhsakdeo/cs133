#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <climits>

using namespace std;

string ltoa(unsigned long arg)
{
    std::string number;
    std::stringstream strstream;
    strstream << arg;
    strstream >> number;
    return number;
}

void mult(const unsigned long num, string* str)
{
    unsigned long carry = 0;
    for (int i = str->length() - 1 ; i >= 0; i--)
    {
        unsigned long digit = str->at(i) - 48;
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

void add(unsigned num, string* str)
{
    unsigned i = str->size() - 1;
    unsigned carry = 0;
    while (num != 0)
    {
        unsigned digit = str->at(i) - 48;
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
            unsigned digit = str->at(i) - 48;
            digit += carry;
            carry = digit / 10;
            digit = digit % 10;
            str->at(i) = (char) (digit + 48);
            --i;
        }
    }
}


void bignum2string(vector <unsigned> num)
{
    //vector<unsigned> num;
    //num.push_back(32767);
    //num.push_back(32767);
    //num.push_back(32767);
    //unsigned temp;
    //do {
    //    cin>>temp;
    //    if (temp == -1) break;
    //    num.push_back(temp);
    //} while(1);

    if (num.size() == 0)
    {
        cout<<"0"<<endl;
        return;
    }

    reverse(num.begin(), num.end());

    unsigned long base = UINT_MAX;
    base++;

    string* output = new string("");
    *output = ltoa(num.at(0));
    for (int i = 1; i < num.size(); i++)
    {
        mult(base, output);
        add(num.at(i), output);
    }

    cout<<*output<<endl;
}


vector<unsigned> string2bignum()
{
    unsigned long base = UINT_MAX;
    base++;
    string input;

    cin >> input;
    
    vector<unsigned> representation;

    unsigned long dividend = 0;
    string quotient;

   
    do
    {
        bool firstflag = false;
        while (input.length() > 0)
        {
            if (firstflag == false)
            {
                while (dividend < base && input.length() > 0)
                {
                    dividend = dividend * 10 + (input[0] - 48);
                    input.erase(input.begin());
                    firstflag = true;
                }
            }
            else if (input.length() > 0)
            {
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
        //cout<<"New string "<<input<<endl;
        quotient.clear();
        //cout<<"Pushed "<<dividend<<endl;
        representation.push_back(dividend);
        dividend = 0;
    } while (!(input.length() == 1 && input[0] == '0'));

    //for (int i = 0; i < representation.size(); i++)
    //{
    //    cout<<representation.at(i)<<endl;
    //}

    //cout << input;
    return representation;
}

vector<unsigned> addBignum(vector<unsigned> num1, vector<unsigned> num2)
{
    unsigned limit = (num1.size()>num2.size()) ? num2.size() : num1.size();
    unsigned long temp = 0;
    unsigned carry = 0;
    int i;
    vector<unsigned> result;

    for (i = 0; i < limit; i++)
    {
        temp = (unsigned long) num1.at(i) + num2.at(i) + carry;
        carry = 0;
        if (temp > UINT_MAX)
        {
            temp -= (UINT_MAX + 1);
            carry = 1;
        }
        result.push_back((unsigned) temp);
    }

    if (num1.size() > limit)
    {
        while (i < num1.size())
        {
            temp = num1.at(i) + carry;
            carry = 0;
            if (temp > UINT_MAX)
            {
                temp -= (UINT_MAX + 1);
                carry = 1;
            }
            result.push_back((unsigned) temp);
            i++;
        }
    }

    if (num2.size() > limit)
    {
        while (i < num2.size())
        {
            temp = num2.at(i) + carry;
            carry = 0;
            if (temp > UINT_MAX)
            {
                temp -= (UINT_MAX + 1);
                carry = 1;
            }
            result.push_back((unsigned) temp);
            i++;
        }
    }

    if (carry != 0) result.push_back(1);
    
    return result;
}

vector<unsigned> subtractBignum(vector<unsigned> num1, vector<unsigned> num2)
{
    vector<unsigned> result;
    unsigned borrow = 0;
    unsigned newborrow = 0;
    unsigned long temp;
    unsigned limit = (num1.size()>num2.size()) ? num2.size() : num1.size();
    int i;

    //just checking that num1 > num2, else return empty
    if (num1.size() < num2.size()) return result;
    if (num1.size() == num2.size()
        && num1.at(num1.size() - 1) < num2.at(num2.size() - 1)) 
        return result;
    
    for (i = 0; i < limit; i++)
    {
        temp = num1.at(i);
        if (num1.at(i) < (num2.at(i) + borrow)) 
        {
            temp += UINT_MAX + 1;
            newborrow = 1;
        }
        else
        {
            newborrow = 0;
        }
        temp -= (num2.at(i) + borrow);
        borrow = newborrow;
        result.push_back((unsigned) temp);
    }
        
    if (num1.size() > limit)
    {
        while (i < num1.size())
        {
            temp = num1.at(i);
            if (num1.at(i) < borrow)
            {
                temp += UINT_MAX + 1;
                newborrow = 1;
            }
            else
            {
                newborrow = 0;
            }
            temp -= borrow;
            borrow = newborrow;
            result.push_back((unsigned) temp);
            i++;
        }
    }

    //clean up 0s from head
    while (result.size() != 0 && result.back() == 0)
    {
        result.pop_back();
    }

    return result;

}

vector <unsigned> multiplyBignum(vector <unsigned> num1, vector <unsigned> num2)
{
    vector <unsigned> result;
    //using vedic math urdhwatiryak method

    //first pad zeros to make the input vectors equal sized
    if (num1.size() > num2.size())
    {
        while (num1.size() != num2.size()) num2.push_back(0);
    }
    else if (num2.size() > num1.size())
    {
        while (num2.size() != num1.size()) num1.push_back(0);
    }

    unsigned numOps = 0;
    for (int i = 0; i < ((2 * num1.size()) - 1); i++)
    {
        if (i < num1.size()) numOps++;
        else numOps--;
        
        vector <unsigned> unsignedermediate;

        unsigned index1;
        unsigned index2;
        if (i < num1.size())
        {
            index1 = 0;
            index2 = numOps - 1;
        }
        else
        {
            index1 = num1.size() - numOps;
            index2 = num1.size() - 1;

        }

        for (int j = 0; j < numOps; j++)
        {
            unsigned long temp = (unsigned long) num1.at(index1) * num2.at(index2);
            vector <unsigned> tmp;
            unsigned long base = UINT_MAX;
            base++;
            if (!(temp / base == 0 && temp % base == 0)) tmp.push_back((unsigned) (temp % base));
            if (temp / base != 0) tmp.push_back((unsigned) (temp / base));
            //cout << "tmp:"<<temp%(UINT_MAX+1)<<" "<<temp/(UINT_MAX+1)<<" "<<temp<<" "<<num1.at(index1)<<" "<<num2.at(index2)<<" "<<temp-(temp/(UINT_MAX+1))*(UINT_MAX+1)<<endl;
            unsignedermediate = addBignum(tmp, unsignedermediate);
        
            //cout<<index1<<","<<index2<<endl;

            index1++;
            index2--;
        }
        //shift unsignedermediate to left by i unsigneds
        if (unsignedermediate.size() > 0)
        {
            for (int j = 0; j < i; j++) 
                unsignedermediate.insert(unsignedermediate.begin(), 1, 0);
        }

        //for (int j = 0; j < unsignedermediate.size(); j++)
        //    cout<<unsignedermediate.at(j)<<"-";
        //cout<<endl;

        result = addBignum(unsignedermediate, result);
        //for (int j = 0; j < result.size(); j++)
        //    cout<<result.at(j)<<"=";
        //cout<<endl;
    }


    //undo padding!
    while (num1.size() != 0 && num1.back() == 0)
    {
        num1.pop_back();
    }
    while (num2.size() != 0 && num2.back() == 0)
    {
        num2.pop_back();
    }


    return result;
}

vector <unsigned> andBignum(vector <unsigned> num1, vector <unsigned> num2)
{
    vector <unsigned> result;
    unsigned limit = (num1.size() > num2.size()) ? num2.size() : num1.size();

    for (int i = 0; i < limit; i++)
    {
        unsigned temp = num1.at(i) & num2.at(i);
        result.push_back(temp);
    }

    //we ignore the rest, and also not pad with zeros because in our representation, padded zeros are not allowed.

    while (result.size() != 0 && result.back() == 0)
    {
        result.pop_back();
    }
    return result;

}

vector <unsigned> orBignum(vector <unsigned> num1, vector <unsigned> num2)
{
    vector <unsigned> result;
    unsigned limit = (num1.size() > num2.size()) ? num2.size() : num1.size();
    int i;

    for (i = 0; i < limit; i++)
    {
        unsigned temp = num1.at(i) | num2.at(i);
        result.push_back(temp);
    }

    if (limit < num1.size())
    {
        while (i < num1.size())
        {
            result.push_back(num1.at(i));
            i++;
        }
    }
    else if (limit < num2.size())
    {
        while (i < num2.size())
        {
            result.push_back(num2.at(i));
            i++;
        }
    }

    //just for sanity, though not really required
    while (result.size() != 0 && result.back() == 0)
    {
        result.pop_back();
    }
    return result;

}

vector <unsigned> xorBignum(vector <unsigned> num1, vector <unsigned> num2)
{
    vector <unsigned> result;
    unsigned limit = (num1.size() > num2.size()) ? num2.size() : num1.size();
    int i;

    for (i = 0; i < limit; i++)
    {
        unsigned temp = num1.at(i) ^ num2.at(i);
        result.push_back(temp);
    }

    if (limit < num1.size())
    {
        while (i < num1.size())
        {
            result.push_back(num1.at(i));
            i++;
        }
    }
    else if (limit < num2.size())
    {
        while (i < num2.size())
        {
            result.push_back(num2.at(i));
            i++;
        }
    }

    //just for sanity, though not really required
    while (result.size() != 0 && result.back() == 0)
    {
        result.pop_back();
    }
    return result;

}

vector <unsigned> notBignum(vector <unsigned> num1)
{
    vector <unsigned> result;
    
    for (int i = 0; i < num1.size(); i++)
    {
        unsigned temp = ~num1.at(i);
        result.push_back(temp);
    }

    //just for sanity, though not really required
    while (result.size() != 0 && result.back() == 0)
    {
        result.pop_back();
    }
    return result;
}

bool equalBignum(vector <unsigned> num1, vector <unsigned> num2)
{
    //removing zero padding, just in case
    while (num1.size() != 0 && num1.back() == 0)
    {
        num1.pop_back();
    }
    while (num2.size() != 0 && num2.back() == 0)
    {
        num2.pop_back();
    }

    if (num1.size() != num2.size()) return false;

    for (int i = 0; i < num1.size(); i++)
    {
        if (num1.at(i) != num2.at(i)) return false;
    }
    
    return true;
}

int main()
{
    for (int i = 0; i < 100; i++)
    {
        vector <unsigned> num1 = string2bignum();
        vector <unsigned> num2 = string2bignum();
        bignum2string(num1);
        bignum2string(num2);
        int ans = -1;
        cin >> ans;
        bool ans1 = equalBignum(num1, num2);
        if (ans1) ans = 1;
        else ans = 0;
        cout << ans <<endl;
 
    }

    return 0;
}

int notmain()
{
    for (int i = 0; i < 100; i++)
    {
        vector <unsigned> num = string2bignum();
        bignum2string(num);
        vector <unsigned> ans = string2bignum();
        ans.clear();
        ans = notBignum(num);
        bignum2string(ans);
    }
    return 0;
}

int andmain()
{
    for (int i = 0; i < 100; i++)
    {
        vector <unsigned> oper1 = string2bignum();
        vector <unsigned> oper2 = string2bignum();
        vector <unsigned> ans1 = string2bignum();
        vector <unsigned> ans2 = string2bignum();
        vector <unsigned> ans3 = string2bignum();
        ans1.clear();
        ans2.clear();
        ans3.clear();
        bignum2string(oper1);
        bignum2string(oper2);
        ans1 = andBignum(oper1, oper2);
        ans2 = orBignum(oper1, oper2);
        ans3 = xorBignum(oper1, oper2);
        bignum2string(ans1);
        bignum2string(ans2);
        bignum2string(ans3);
    }
    return 0;
}

int multmain()
{
    for (int i = 0; i < 100; i++)
    {
        vector <unsigned> oper1 = string2bignum();
        vector <unsigned> oper2 = string2bignum();
        vector <unsigned> ans = string2bignum();
        ans.clear();
        bignum2string(oper1);
        bignum2string(oper2);
        ans = multiplyBignum(oper1, oper2);
            //for (int j = 0; j < ans.size(); j++)
            //    cout<<ans.at(j)<<"=";
            //cout<<endl;
        bignum2string(ans);
    } 
    return 0;
}

int submain()
{
    for (int i = 0; i < 100; i++)
    {
        vector <unsigned> oper1 = string2bignum();
        vector <unsigned> oper2 = string2bignum();
        vector <unsigned> ans = string2bignum();
        ans.clear();
        bignum2string(oper1);
        bignum2string(oper2);
        ans = subtractBignum(oper1, oper2);

        //for (int i = 0; i < oper1.size(); i++) cout<<oper1.at(i)<<"-";
        //cout<<endl;

        //for (int i = 0; i < oper2.size(); i++) cout<<oper2.at(i)<<"-";
        //cout<<endl;

        //for (int i = 0; i < ans.size(); i++) cout<<ans.at(i)<<"-";
        //cout<<endl;
        bignum2string(ans);
    }
}

int addmain()
{
    int i = 0;
    vector<unsigned> sum;
    //cout<<INT_MAX<<" "<<sizeof(int)<<" "<<sizeof(long)<<LONG_MAX<<endl;
    while (i < 100)
    {
        vector <unsigned> oper = string2bignum();
        sum = addBignum(oper, sum);
        //cout<<sum.size();
        bignum2string(oper);

        //for (int j = 0; j < sum.size(); j++) cout<<sum.at(j)<<"x";
        //cout<<endl;

        //bignum2string(sum);
        //cout<<++i<<endl;
        i++;
    }
    bignum2string(sum);
    //cout<<INT_MAX;
    return 0;
}
