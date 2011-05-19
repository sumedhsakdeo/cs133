#ifndef _BIG_INT_UTILS_H_
#define _BIG_INT_UTILS_H_

#include <vector>
#include <string>

class BigInt_Utils	{
public:
    static std::vector<int> string_to_vector(const std::string &);
    static std::string vector_to_string(const std::vector<int>& buf);
};

#endif //_BIG_INT_UTILS_H_

