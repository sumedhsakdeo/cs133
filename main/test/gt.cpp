#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
extern "C" {
#include <stdint.h>
#include <sys/time.h>
#include <unistd.h>
}

#include <BigUInt.h>
#include <Common_Utils.h>

using namespace std;


int
main(int argc, char **argv)
{
    if (argc < 2) {
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

    uint64_t total_time = 0;

    for (int i = 0; i < num_tests; ++i) {
        string op1_str, op2_str;

        fin >> op1_str >> op2_str;

        BigUInt op1(op1_str);
        BigUInt op2(op2_str);

        //fout << op1.ToString() << endl;
        //fout << op2.ToString() << endl;
        bool eq;

        struct timeval tv_beg, tv_end;
        struct timezone tz;
 
        gettimeofday(&tv_beg, &tz);
        eq = (op1 > op2);
        gettimeofday(&tv_end, &tz);

        total_time += GetTimeDifference(tv_beg, tv_end);

        string eq_str;
        fin >> eq_str;

        bool testeq;


        if (atoi(eq_str.c_str())) {
            testeq = true;
        }
        else {
            testeq = false;
        }

        //fout << sum.ToString() << endl;
        if (eq == testeq) {
            //cout << i << " : " << "Success: Addition" << endl;
        } else {
            cerr << i << " : " << "Failure: Greater Than" << endl;
        }

    }

    fin.close();
    //fout.close();
    cout <<  total_time << endl;

    return 0;
}
