#ifndef _INC_PARALLELIZER_H
#define _INC_PARALLELIZER_H

#include <vector>
#include <time.h>
#include <map>
#include <pthread.h>
#include "OperationThread.h"
#include "ThreadPool.h"
#include <iostream>

#include "types.h"

#define PAUSE 1

class Parallelizer  {
public:
    template <class T, class M>
    static std::vector<M> executeBatchRequest(const std::vector<T>&, const std::vector<T>&, OPERATION); 
    template <class T, class M>
    static void resultCollector(std::vector<M>&, bool);
};

template <class T, class M> 
std::vector<M>
Parallelizer :: executeBatchRequest(const std::vector<T> &oper1, const std::vector<T> &oper2, OPERATION op)    {
    
    std::vector<M> result(oper1.size());
    ThreadPool<OperationThread<T, M> > *tp = ThreadPool<OperationThread<T, M> >::getInstance();
    int count_max = oper1.size();

    for (int i=0; i < oper1.size(); i++)    {

        OperationThread<T, M> *ot;
        while ((ot=tp->getFreeThread()) == NULL) {
           Parallelizer::resultCollector<T,M>(result, false); 
           pthread_yield();
        }
        ot->setOp1(oper1[i]);
        ot->setOp2(oper2[i]);
        ot->setIdx(i);
        ot->setOperation(op);
        ot->setThreadState(THREAD_SCHED);

        while (ot->getThreadState() == THREAD_SCHED) {
            pthread_cond_signal(ot->getCondSchedule());
            pthread_yield();
        }

    }

    Parallelizer::resultCollector<T, M>(result, true);
    return result;
}

//  Result collector which 
//  sets the result of THREAD_DONE thread, and adds it back to the free_list
template <class T, class M>
void
Parallelizer :: resultCollector(std::vector<M> &result, bool blocking)    {
    
   //   getdone threads 
   //   if thread.sz >= 1 and blocking == false return 
   bool allDone = false;
   do   {
       ThreadPool<OperationThread<T, M> > *tp = ThreadPool<OperationThread<T, M> >::getInstance();
       std::vector<struct ThreadPool<OperationThread<T,M> >::thread_node*> v = tp->getDoneThreads(allDone);
       for (int i = 0; i < v.size(); i++)   {
            result[v[i]->thread->getIdx()] = v[i]->thread->getResult();
       }
       tp->addFreeThreads(v);
   } while (blocking && !allDone);

}

#endif  //  _INC_PARALLELIZER_H
