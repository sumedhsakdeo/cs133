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

	BigUInt op1(argv[1]), op2(argv[2]);

	cout << " Sum: "<< (op1+op2).ToString() << endl;
	cout << " Sub: "<< (op1-op2).ToString() << endl;
	cout << " Mult: "<< (op1*op2).ToString() << endl;
	cout << " Div: "<< (op1/op2).ToString() << endl;

    return 0;
}
