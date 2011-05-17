#include <iostream>
#include "BigNum.h"

using namespace std;

int main()
{
    //char *num = new char[19];
    //num[6] = 'o';
    //cout<<sizeof(num)<<"Hello World\n";
    
    string input;
    cin >> input;

    BigNum* bn = new BigNum(input.c_str());
    bn->print();
    
    return 0;
}

