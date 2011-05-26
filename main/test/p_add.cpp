#include <iostream>
#include <string>
extern "C" {
#include <stdint.h>
}

#include <BigUInt.h>

using namespace std;

int main(void)  {

    BigUInt op1("123456789123456789");
    BigUInt op2("123456789123456789");

    BigUInt sum; 
    sum = op1 + op2;
    cout << op1.ToString() << " + " << op2.ToString() << " = " << sum.ToString() << endl;
/*
    int count = 1000;
    while(count--)  {
        vector<int> v1(100);
        vector<int> v2(100);

        for (int i=0; i<100; i++) {
            v1[i] = i;
            v2[i] = i;
        }

       vector<int> v3 = Parallelizer::executeBatchRequest<int,int>(v1, v2, ADD, v1.size());  
       for (int i=0; i < v3.size(); i++)
            cout << v3[i] << endl;
    }
    */
    return 0;
}
