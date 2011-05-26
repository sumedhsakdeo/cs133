#include <iostream>
#include <string>
#include <fstream>
extern "C" {
#include <stdint.h>
}

#include <climits>
#include <BigUInt.h>

using namespace std;

int main(int argc, char **argv)  {

    ifstream fin(argv[1], ifstream::in);

    int i = 0;
    BigUInt zero("0");
    BigUInt sum("0");
    while (i < 100)
    {
        string op;
        fin>>op;
        BigUInt b(op);
        sum = sum + b;
        i++;
    }
    string result;
    fin >> result;
    if (!result.compare(sum.ToString())) {
        cout << "sum sucess" << endl;
    } else { 
        cerr << "sum failure" << endl;
    }

    BigUInt sub;
    sub = sum - sum;
    if (!sub.ToString().compare(zero.ToString())) {
        cout << "SUB Success" << endl;
    } else {
        cerr << "SUB Failure" << endl;
    }


    BigUInt anded;
    anded = zero & sum;
    if (!anded.ToString().compare(zero.ToString())) {
        cout << "And Success" << endl;
    } else {
        cerr << "And Failure" << endl;
    }
    
    BigUInt ored;
    ored = zero | sum;
    if (!ored.ToString().compare(sum.ToString())) {
        cout << "OR Success" << endl;
    } else {
        cerr << "OR Failure" << endl;
    }

    BigUInt xored;
    xored = zero ^ sum;
    if (!xored.ToString().compare(sum.ToString())) {
        cout << "XOR Success" << endl;
    } else {
        cerr << "XOR Failure" << endl;
    }
    
    BigUInt noted("18446744073709551615");
    noted = ~noted;
    if (!noted.ToString().compare(zero.ToString())) {
        cout << "NOT Success" << endl;
    } else {
        cerr << "NOT Failure" << endl;
    }


/*    BigUInt op1("123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789");
    BigUInt op2("123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789");

    BigUInt sum; 
    sum = op1 + op2;
    cout << op1.ToString() << " + " << op2.ToString() << " = " << sum.ToString() << endl;

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
