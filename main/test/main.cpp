#include <iostream>
#include <fstream>
#include <string>
extern "C" {
#include <stdint.h>
}

#include <BigUInt.h>

using namespace std;

int
main(int argc, char **argv)
{
    if (argc < 3) {
        cerr << "Error: Invalid argumets." << endl;
        cerr << "\nUsage:"<< endl;
        cerr << "\t" << argv[0] << " <in-filename> <out-filename>" << endl;
        return -1;
    }

    ifstream fin(argv[1], ifstream::in);
    ofstream fout(argv[2], ofstream::out);
    
    int num_tests;
    fin >> num_tests;
    fout << num_tests << endl;

    for (int i = 0; i < num_tests; ++i) {
        string op1_str, op2_str;
        uint32_t shift;

        fin >> op1_str >> op2_str >> shift;

        BigUInt op1(op1_str);
        BigUInt op2(op2_str);

        fout << op1.ToString() << endl;
        fout << op2.ToString() << endl;
        fout << shift << endl;

        BigUInt sum, diff, mul, and_num, or_num, xor_num, not_num, lshift, rshift;

        sum = op1 + op2;
        string add_str;
        fin >> add_str;
        fout << sum.ToString() << endl;
        if (!add_str.compare(sum.ToString())) {
            cout << i << " : " << "Success: Addition" << endl;
        } else {
            cerr << i << " : " << "Failure: Addition" << endl;
        }

        diff = op1 - op2;
        string diff_str;
        fin >> diff_str;
        fout << diff.ToString() << endl;
        if (!diff_str.compare(diff.ToString())) {
            cout << i << " : " << "Success: Subtraction" << endl;
        } else {
            cerr << i << " : " << "Failure: Subtraction" << endl;
        }

        mul = op1 * op2;
        string mul_str;
        fin >> mul_str;
        fout << mul.ToString() << endl;
        if (!mul_str.compare(mul.ToString())) {
            cout << i << " : " << "Success: Multiplication" << endl;
        } else {
            cerr << i << " : " << "Failure: Multiplication" << endl;
        }

        and_num = op1 & op2;
        string and_str;
        fin >> and_str;
        fout << and_num.ToString() << endl;
        if (!and_str.compare(and_num.ToString())) {
            cout << i << " : " << "Success: AND" << endl;
        } else {
            cerr << i << " : " << "Failure: AND" << endl;
        }

        or_num = op1 | op2;
        string or_str;
        fin >> or_str;
        fout << or_num.ToString() << endl;
        if (!or_str.compare(or_num.ToString())) {
            cout << i << " : " << "Success: OR" << endl;
        } else {
            cerr << i << " : " << "Failure: OR" << endl;
        }

        xor_num = op1 ^ op2;
        string xor_str;
        fin >> xor_str;
        fout << xor_num.ToString() << endl;
        if (!xor_str.compare(xor_num.ToString())) {
            cout << i << " : " << "Success: XOR" << endl;
        } else {
            cerr << i << " : " << "Failure: XOR" << endl;
        }

        not_num = ~op1;
        string not_str;
        fin >> not_str;
        fout << not_num.ToString() << endl;
        if (!not_str.compare(not_num.ToString())) {
            cout << i << " : " << "Success: NOT" << endl;
        } else {
            cerr << i << " : " << "Failure: NOT" << endl;
        }

        lshift = op1 << shift;
        string lshift_str;
        fin >> lshift_str;
        fout << lshift.ToString() << endl;
        if (!lshift_str.compare(lshift.ToString())) {
            cout << i << " : " << "Success: LSHIFT" << endl;
        } else {
            cerr << i << " : " << "Failure: LSHIFT" << endl;
        }

        rshift = op1 >> shift;
        string rshift_str;
        fin >> rshift_str;
        fout << rshift.ToString() << endl;
        if (!rshift_str.compare(rshift.ToString())) {
            cout << i << " : " << "Success: RSHIFT" << endl;
        } else {
            cerr << i << " : " << "Failure: RSHIFT" << endl;
        }

        int isEqual = (op1 == op2) ? 1 : 0;
        int res;
        fin >> res;
        fout << isEqual << endl;
        if (res == isEqual) {
            cout << i << " : " << "Success: EQUALS" << endl;
        } else {
            cerr << i << " : " << "Failure: EQUALS" << endl;
        }

    }


    return 0;
}
