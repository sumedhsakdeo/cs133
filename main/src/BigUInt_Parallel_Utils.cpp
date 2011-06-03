#include "BigUInt_Parallel_Utils.h"
#include "Common_Utils.h"
#include "types.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <climits>
#include <cmath>
#include "Parallelizer.h"
extern "C" {
#include <stdint.h>
}

//TODO: remove
#include    <iostream>

using namespace std;

vector<uint32_t>
BigUInt_Parallel_Utils::AddBignum(vector<uint32_t>& num1, vector<uint32_t>& num2)
{
    uint32_t limit = MIN(num1.size(),num2.size());
    uint32_t carry = 0;
    int i;
    vector<uint32_t> result;
    vector<uint64_t> temp(MAX(num1.size(),num2.size()));
    vector<uint32_t> dummy;
    Parallelizer::executeBatchRequest<uint32_t,uint64_t>(num1, num2, temp, ADD, limit, dummy);
    
    for (i = 0; i < limit; i++) {
        temp[i] += carry;
        carry = 0;
        if (temp[i] > UINT_MAX) {
            temp[i] -= (UINT_MAX + 1);
            carry = 1;
        }
        result.push_back((uint32_t) temp[i]);
    }

    /*for (i=0; i < limit; i++)   
        cout << num1[i] << " ";
    cout << endl;
    for (i=0; i < limit; i++)   
        cout << num2[i] << " ";
    cout << endl;
    for (i=1;i<limit;i++)
        cout << carrySet[i-1] << " ";
    cout << endl;
    for (i=0; i < limit; i++)   
        cout << temp[i] << " ";
    cout << endl;

    for (i = 1; i < limit; i++) {
        temp[i] += carrySet[i-1];
        result.push_back((uint32_t) temp[i]);
    }

    carry = carrySet[limit-1];*/
    if (num1.size() > limit) {
        while (i < num1.size()) {
            temp[i] = num1.at(i) + carry;
            carry = 0;

            if (temp[i] > UINT_MAX) {
                temp[i] -= (UINT_MAX + 1);
                carry = 1;
            }

            result.push_back((uint32_t) temp[i]);
            i++;
        }
    }

    if (num2.size() > limit) {
        while (i < num2.size()) {
            temp[i] = num2.at(i) + carry;
            carry = 0;

            if (temp[i] > UINT_MAX) {
                temp[i] -= (UINT_MAX + 1);
                carry = 1;
            }

            result.push_back((uint32_t) temp[i]);
            i++;
        }
    }

    if (carry != 0) {
        result.push_back(1);
    }
    
    return result;
}


vector<uint32_t>
BigUInt_Parallel_Utils::SubtractBignum(vector<uint32_t>& num1, vector<uint32_t>& num2)
{
    vector<uint32_t> result;
    uint32_t borrow = 0;
    uint32_t newborrow = 0;
    uint32_t limit = MIN(num1.size(),num2.size());
    vector<int64_t> temp(MAX(num1.size(),num2.size()));
    bool    sign = false;
    int i;

    //just checking that num1 < num2, swapping and setting sign flag
    if (BigUInt_Parallel_Utils::LessThan(num1,num2)) {
        //num1.swap(num2);
        //sign = true;
        return result;
    }
    
    vector<uint32_t> dummy;
    Parallelizer::executeBatchRequest<uint32_t,int64_t>(num1, num2, temp, SUB, limit, dummy);

    for (i = 0; i < limit; i++) {
        if (temp[i] < 0)    {
            temp[i] += UINT_MAX + 1;
            newborrow = 1;
        } else  {
            newborrow = 0;
        }
        temp[i] -= borrow;
        borrow = newborrow;
        result.push_back((uint32_t) temp[i]);
    }
        
    if (num1.size() > limit) {
        while (i < num1.size()) {
            temp[i] = num1.at(i);

            if (num1.at(i) < borrow) {
                temp[i] += UINT_MAX + 1;
                newborrow = 1;
            } else {
                newborrow = 0;
            }

            temp[i] -= borrow;
            borrow = newborrow;
            result.push_back((uint32_t) temp[i]);
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
BigUInt_Parallel_Utils::MultiplyBignum(vector<uint32_t>& num1, vector<uint32_t>& num2)
{
    vector<uint32_t>    result;
    //  normal multiplication

    //  if any vector is zero return empty
    if (!num1.size() || !num2.size())
        return result;

    //  if one vector size is greater than other vector swap for efficient
    //  parallelization.
    if (num1.size() > num2.size())  
        num1.swap(num2);

    vector<vector<uint32_t> >  intermediateResults = Parallelizer::executeBatchRequest<uint32_t,uint32_t>(num1, num2, MULT); 
    
    //  shifting intermediate results
    for (int i = 0; i < intermediateResults.size(); i++)    {
        vector<uint32_t> intermediate = intermediateResults[i];
        int j = i;
        while (j--)   {
            intermediate.insert(intermediate.begin(), 0);
        }
    }

    //  addition intermediate results
    result = intermediateResults[0];
    for (int i = 1; i < intermediateResults.size(); i++)    {
        result = AddBignum (result, intermediateResults[i]);
    }

    return result;    
}

/*  vector<uint32_t>
BigUInt_Parallel_Utils::MultiplyBignum(vector<uint32_t>& num1, vector<uint32_t>& num2)
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
}*/

vector<uint32_t>
BigUInt_Parallel_Utils::DivideBignum(vector<uint32_t>& num1, vector<uint32_t>& num2)
{
   return num1;
}

vector<uint32_t> 
BigUInt_Parallel_Utils::AndBignum(vector<uint32_t>& num1, vector<uint32_t>& num2)
{
    uint32_t limit = (num1.size() > num2.size()) ? num2.size() : num1.size();
    vector <uint32_t> result(limit);
    vector<uint32_t> dummy;
    Parallelizer::executeBatchRequest<uint32_t,uint32_t>(num1, num2, result, AND, limit, dummy);

    //we ignore the rest, and also not pad with zeros because in our representation, padded zeros are not allowed.
    while (result.size() != 0 && result.back() == 0) {
        result.pop_back();
    }

    return result;
}

vector<uint32_t>
BigUInt_Parallel_Utils::OrBignum(vector<uint32_t>& num1, vector<uint32_t>& num2)
{
    uint32_t limit = MIN(num1.size(),num2.size());
    vector <uint32_t> result(limit);
    vector<uint32_t> dummy;
    Parallelizer::executeBatchRequest<uint32_t,uint32_t>(num1, num2, result, OR, limit, dummy);

    int i = limit;
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
BigUInt_Parallel_Utils::XorBignum(vector<uint32_t>& num1, vector<uint32_t>& num2)
{
    uint32_t limit = MIN(num1.size(),num2.size());
    vector <uint32_t> result(limit);
    vector<uint32_t> dummy;
    Parallelizer::executeBatchRequest<uint32_t,uint32_t>(num1, num2, result, XOR, limit, dummy);

    int i = limit;
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
BigUInt_Parallel_Utils::NotBignum(vector<uint32_t>& num1)
{
    vector <uint32_t> result(num1.size());
    vector<uint32_t> dummy;
    //  second vector argument is dummy and shall not be used.
    Parallelizer::executeBatchRequest<uint32_t,uint32_t>(num1, num1, result, NOT, num1.size(), dummy);
    
    //just for sanity, though not really required
    while (result.size() != 0 && result.back() == 0) {
        result.pop_back();
    }

    return result;
}

bool
BigUInt_Parallel_Utils::EqualBignum(vector<uint32_t>& num1, vector<uint32_t>& num2)
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
    vector <bool> result(num1.size());
    vector <uint32_t> dummy;
    Parallelizer::executeBatchRequest<uint32_t,bool>(num1, num2, result, EQ, num1.size(), dummy);
    for (int i = 0; i < num1.size(); i++) {
        if (!result[i]) return false;
    }
    
    return true;
}

bool
BigUInt_Parallel_Utils::GreaterThan(vector<uint32_t>& num1, vector<uint32_t>& num2)
{
    while (num1.size() != 0 && num1.back() == 0) {
        num1.pop_back();
    }

    while (num2.size() != 0 && num2.back() == 0) {
        num2.pop_back();
    }

    if (num1.size() < num2.size()) {
        return false;
    } else if (num1.size() > num2.size()) {
        return true;
    }

    vector <short> result(num1.size());
    vector <uint32_t> dummy;
    Parallelizer::executeBatchRequest<uint32_t,short>(num1, num2, result, GT, num1.size(), dummy);
    for (int i = num1.size() - 1; i >= 0; --i) {
        if (result[i] < 0)  {
            return false;
        } else if(result[i] > 0) {
            return true;
        }
    }
    return false;
}

bool
BigUInt_Parallel_Utils::LessThan(vector<uint32_t>& num1, vector<uint32_t>& num2)
{
    while (num1.size() != 0 && num1.back() == 0) {
        num1.pop_back();
    }

    while (num2.size() != 0 && num2.back() == 0) {
        num2.pop_back();
    }

    if (num1.size() > num2.size()) {
        return false;
    } else if (num1.size() < num2.size()) {
        return true;
    }

    vector <short> result(num1.size());
    vector <uint32_t> dummy;
    Parallelizer::executeBatchRequest<uint32_t,short>(num1, num2, result, LT, num1.size(), dummy);
    for (int i = num1.size() - 1; i >= 0; --i) {
        if (result[i] > 0)  {
            return false;
        } else if(result[i] < 0) {
            return true;
        }
    }
    return false;

}

vector<uint32_t>
BigUInt_Parallel_Utils::Lshift(vector<uint32_t>& num1, const uint32_t& shift)
{
    vector <uint32_t> result;
    int bitsindigit = sizeof(uint32_t) * 8;
    uint64_t mask = pow((double) 2, bitsindigit) - 1;

    int newdigits = shift / bitsindigit;
    int inshift = shift % bitsindigit;

    for (int i = 0; i < newdigits; i++) {
        result.push_back(0);
    }

    vector <uint32_t> dummy;
    vector <uint64_t> temp(num1.size());
    Parallelizer::executeBatchRequest<uint32_t,uint64_t>(num1, inshift, temp, LSHIFT, num1.size(), dummy);

    uint64_t val_temp = 0;
    for (int i = 0; i < num1.size(); i++) {
        val_temp += (uint64_t) temp[i];
        result.push_back((uint32_t) (val_temp & mask));
        val_temp = val_temp >> bitsindigit;
    }

    if (val_temp != 0) {
        result.push_back((uint32_t) val_temp);
    }

    return result;
}

vector<uint32_t>
BigUInt_Parallel_Utils::Rshift(vector<uint32_t>& num1, const uint32_t& shift)
{
    vector <uint32_t> result;
    int bitsindigit = sizeof(uint32_t) * 8;
    uint64_t mask = (uint64_t) (pow((double) 2, bitsindigit) - 1) << bitsindigit;

    int newdigits = shift / bitsindigit;
    int inshift = shift % bitsindigit;

    vector <uint64_t> temp(num1.size());
    vector <uint32_t> dummy;
    Parallelizer::executeBatchRequest<uint32_t,uint64_t>(num1, inshift, temp, RSHIFT, num1.size(), dummy);
    
    uint64_t val_temp = 0;
    for (int i = num1.size() - 1; i >= newdigits; i--) {
        val_temp += (uint64_t) temp[i];
        result.push_back((uint32_t) (val_temp >> bitsindigit));
        val_temp = val_temp << bitsindigit;
    }
    
    reverse(result.begin(), result.end());
    while (result.size() != 0 && result.back() == 0) {
        result.pop_back();
    }

    return result;
}

