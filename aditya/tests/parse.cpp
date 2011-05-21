#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <climits>

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


void bignum2string(vector <int> num)
{
    //vector<int> num;
    //num.push_back(32767);
    //num.push_back(32767);
    //num.push_back(32767);
    //int temp;
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

    long base = INT_MAX;
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


vector<int> string2bignum()
{
    long base = INT_MAX;
    base++;
    string input;

    cin >> input;
    
    vector<int> representation;

    long dividend = 0;
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

vector<int> addBignum(vector<int> num1, vector<int> num2)
{
    int limit = (num1.size()>num2.size()) ? num2.size() : num1.size();
    long temp = 0;
    int carry = 0;
    int i;
    vector<int> result;

    for (i = 0; i < limit; i++)
    {
        temp = (long) num1.at(i) + num2.at(i) + carry;
        carry = 0;
        if (temp > INT_MAX)
        {
            temp -= (INT_MAX + 1);
            carry = 1;
        }
        result.push_back((int) temp);
    }

    if (num1.size() > limit)
    {
        while (i < num1.size())
        {
            temp = num1.at(i) + carry;
            carry = 0;
            if (temp > INT_MAX)
            {
                temp -= (INT_MAX + 1);
                carry = 1;
            }
            result.push_back((int) temp);
            i++;
        }
    }

    if (num2.size() > limit)
    {
        while (i < num2.size())
        {
            temp = num2.at(i) + carry;
            carry = 0;
            if (temp > INT_MAX)
            {
                temp -= (INT_MAX + 1);
                carry = 1;
            }
            result.push_back((int) temp);
            i++;
        }
    }

    if (carry != 0) result.push_back(1);
    
    return result;
}

vector<int> subtractBignum(vector<int> num1, vector<int> num2)
{
    vector<int> result;
    int borrow = 0;
    int newborrow = 0;
    long temp;
    int limit = (num1.size()>num2.size()) ? num2.size() : num1.size();
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
            temp += INT_MAX + 1;
            newborrow = 1;
        }
        else
        {
            newborrow = 0;
        }
        temp -= (num2.at(i) + borrow);
        borrow = newborrow;
        result.push_back((int) temp);
    }
        
    if (num1.size() > limit)
    {
        while (i < num1.size())
        {
            temp = num1.at(i);
            if (num1.at(i) < borrow)
            {
                temp += INT_MAX + 1;
                newborrow = 1;
            }
            else
            {
                newborrow = 0;
            }
            temp -= borrow;
            borrow = newborrow;
            result.push_back((int) temp);
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

vector <int> multiplyBignum(vector <int> num1, vector <int> num2)
{
    vector <int> result;
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

    int numOps = 0;
    for (int i = 0; i < ((2 * num1.size()) - 1); i++)
    {
        if (i < num1.size()) numOps++;
        else numOps--;
        
        vector <int> intermediate;

        int index1;
        int index2;
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
            long temp = (long) num1.at(index1) * num2.at(index2);
            vector <int> tmp;
            long base = INT_MAX;
            base++;
            if (!(temp / base == 0 && temp % base == 0)) tmp.push_back((int) (temp % base));
            if (temp / base != 0) tmp.push_back((int) (temp / base));
            //cout << "tmp:"<<temp%(INT_MAX+1)<<" "<<temp/(INT_MAX+1)<<" "<<temp<<" "<<num1.at(index1)<<" "<<num2.at(index2)<<" "<<temp-(temp/(INT_MAX+1))*(INT_MAX+1)<<endl;
            intermediate = addBignum(tmp, intermediate);
        
            //cout<<index1<<","<<index2<<endl;

            index1++;
            index2--;
        }
        //shift intermediate to left by i ints
        if (intermediate.size() > 0)
        {
            for (int j = 0; j < i; j++) 
                intermediate.insert(intermediate.begin(), 1, 0);
        }

        //for (int j = 0; j < intermediate.size(); j++)
        //    cout<<intermediate.at(j)<<"-";
        //cout<<endl;

        result = addBignum(intermediate, result);
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

int main()
{
    for (int i = 0; i < 100; i++)
    {
        vector <int> oper1 = string2bignum();
        vector <int> oper2 = string2bignum();
        vector <int> ans = string2bignum();
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

int mainForSub()
{
    for (int i = 0; i < 100; i++)
    {
        vector <int> oper1 = string2bignum();
        vector <int> oper2 = string2bignum();
        vector <int> ans = string2bignum();
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

int mainForAdd()
{
    int i = 0;
    vector<int> sum;
    //cout<<INT_MAX<<" "<<sizeof(int)<<" "<<sizeof(long)<<LONG_MAX<<endl;
    while (i < 100)
    {
        vector <int> oper = string2bignum();
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
