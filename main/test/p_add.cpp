#include    "Parallelizer.h"
#include    <iostream>

using namespace std;

int main(void)  {

    int count = 1000;
    while(count--)  {
        vector<int> v1(100);
        vector<int> v2(100);

        for (int i=0; i<100; i++) {
            v1[i] = i;
            v2[i] = i;
        }

       vector<int> v3 = Parallelizer::executeBatchRequest<int,int>(v1, v2, ADD);  
       for (int i=0; i < v3.size(); i++)
            cout << v3[i] << endl;
    }
    return 0;
}
