#ifndef _INC_PARALLELIZER_H
#define _INC_PARALLELIZER_H

#include <vector>
#include <pthread.h>
#include "OperationThread.h"
#include "ThreadPool.h"

#include "types.h"

class Parallelizer  {
public:
    template <class T, class M>
    static std::vector<M> executeBatchRequest(const std::vector<T>&, const std::vector<T>&, OPERATION); 
};

template <class T, class M> 
std::vector<M>
Parallelizer :: executeBatchRequest(const std::vector<T> &oper1, const std::vector<T> &oper2, OPERATION op)    {
    
    std::vector<M> result(oper1.size());
    ThreadPool<OperationThread<T, M> > *tp = ThreadPool<OperationThread<T, M> >::getInstance();

    for (int i=0; i < oper1.size(); i++)    {

        pthread_cond_t      cond_callback = PTHREAD_COND_INITIALIZER;
        pthread_mutex_t     my_lock       = PTHREAD_MUTEX_INITIALIZER;    

        OperationThread<T, M> *ot = tp->getFreeThread();
        ot->setOp1(oper1[i]);
        ot->setOp2(oper2[i]);
        ot->setOperation(op);
        ot->setThreadState(THREAD_SCHED);
        ot->setCondCallback(&cond_callback);

        pthread_cond_signal(ot->getCondSchedule());

        pthread_mutex_lock (&my_lock);
        pthread_cond_wait(&cond_callback, &my_lock); 
        pthread_mutex_unlock (&my_lock);

        result[i] = ot->getResult();
        tp->addThreadFreeList(ot->getThreadID());
        pthread_mutex_destroy (&my_lock);
        pthread_cond_destroy (&cond_callback);
    }

    return result;
}
#endif  //  _INC_PARALLELIZER_H
