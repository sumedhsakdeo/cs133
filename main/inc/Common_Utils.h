#ifndef _INC_COMMON_UTILS_H_
#define _INC_COMMON_UTILS_H_

#include <vector>
#include <string>

#define MAX(a1, a2) ((a1) > (a2) ? (a1) : (a2))
#define MIN(a1, a2) ((a1) < (a2) ? (a1) : (a2))

class Common_Utils  {
public:
    static std::vector<unsigned int> StringToVector(const std::string &);
    static std::string VectorToString(const std::vector<unsigned int>& buf);
};

#endif  //  _INC_COMMON_UTILS_H_



