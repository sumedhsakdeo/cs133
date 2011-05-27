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
    //ofstream fout(argv[2], ofstream::out);
    
    int num_tests;
    fin >> num_tests;
    //fout << num_tests << endl;

    for (int i = 0; i < num_tests; ++i) {
        string op1_str, op2_str;

        fin >> op1_str >> op2_str;

        BigUInt op1(op1_str);
        BigUInt op2(op2_str);

        //fout << op1.ToString() << endl;
        //fout << op2.ToString() << endl;

        BigUInt diff;

        diff = op1 - op2;
        string sub_str;
        fin >> sub_str;
        //fout << diff.ToString() << endl;
        if (!sub_str.compare(diff.ToString())) {
            //cout << i << " : " << "Success: Subtraction" << endl;
        } else {
            cerr << i << " : " << "Failure: Subtraction" << endl;
        }
    }

    fin.close();
    //fout.close();

    return 0;
}
