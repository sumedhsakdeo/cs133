#include    "Parallelizer.h"
#include    <iostream>

using namespace std;

int main(void)  {

    vector<int> v1;
    vector<int> v2;

    v1.push_back(1);
    v1.push_back(1);
    v1.push_back(1);
    v1.push_back(1);

    v2.push_back(1);
    v2.push_back(1);
    v2.push_back(1);
    v2.push_back(1);

   vector<int> v3 = Parallelizer::executeBatchRequest<int,int>(v1, v2, ADD);  
    
   for (int i=0; i < v3.size(); i++)
        cout << v3[i] << endl;

    return 0;
}
