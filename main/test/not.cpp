#include <iostream>
#include <fstream>
#include <string>
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
    if (argc < 3) {
        cerr << "Error: Invalid argumets." << endl;
        cerr << "\nUsage:"<< endl;
        cerr << "\t" << argv[0] << " <in-filename> <out-filename>" << endl;
        return -1;
    }

    ifstream fin(argv[1], ifstream::in);
    //ofstream fout(argv[2], ofstream::out);

    uint64_t total_time = 0;
    
    int num_tests;
    fin >> num_tests;
    //fout << num_tests << endl;

    for (int i = 0; i < num_tests; ++i) {
        string op1_str;

        fin >> op1_str;

        BigUInt op1(op1_str);

        //fout << op1.ToString() << endl;

        BigUInt notop;

        struct timeval tv_beg, tv_end;
        struct timezone tz;
 
        gettimeofday(&tv_beg, &tz);
        notop = ~op1;
        gettimeofday(&tv_end, &tz);

        total_time += GetTimeDifference(tv_beg, tv_end);

        string not_str;
        fin >> not_str;
        //fout << notop.ToString() << endl;
        if (!not_str.compare(notop.ToString())) {
            //cout << i << " : " << "Success: NOT" << endl;
        } else {
            cerr << i << " : " << "Failure: NOT" << endl;
        }
    }

    fin.close();
    //fout.close();
    cout <<  total_time << endl;

    return 0;
}
