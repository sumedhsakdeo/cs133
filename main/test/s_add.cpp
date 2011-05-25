#include    "BigUInt.h"
#include    <string>

using namespace std;

int main () {
   
    string s1("100");
    string s2("200");
    BigUInt b1(s1);
    BigUInt b2(s2);
    BigUInt b3 = b1 + b2;
    
    b3.print();

    return 0;
}
