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
    BigUInt sum("0");
    while (i < 100)
    {
        string op;
        fin>>op;
        BigUInt b(op);
        sum = sum + b;
        i++;
    }
    
    cout << sum.ToString();
    string result;
    fin >> result;
    if (!result.compare(sum.ToString())) {
        cout << "Sucess" << endl;
    } else { 
        cerr << "Failure" << endl;
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
