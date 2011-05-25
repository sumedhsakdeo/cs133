#ifndef _INC_PARALLELIZER_H
#define _INC_PARALLELIZER_H

#include <vector>
#include "types.h"

class Parallelizer  {
public:
    template <class T, class M>
    static std::vector<M> executeBatchRequest(const std::vector<T>&, const std::vector<T>&, OPERATION); 
};

#endif  //  _INC_PARALLELIZER_H
