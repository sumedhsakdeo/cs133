#ifndef _INC_COMMON_UTILS_H_
#define _INC_COMMON_UTILS_H_

#include <vector>
#include <string>
#include <stdint.h>

#define MAX(a1, a2) ((a1) > (a2) ? (a1) : (a2))
#define MIN(a1, a2) ((a1) < (a2) ? (a1) : (a2))

class Common_Utils  {
public:
    static std::vector<unsigned int> StringToVector(const std::string &);
    static std::string VectorToString(const std::vector<unsigned int>& buf);
};

uint64_t
GetTimeDifference(struct timeval tv_beg, struct timeval tv_end);

#endif  //  _INC_COMMON_UTILS_H_



