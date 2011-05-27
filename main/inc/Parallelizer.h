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

class Parallelizer  {
public:
    template <class T, class M>
    static void executeBatchRequest(const std::vector<T>&, const std::vector<T>&, std::vector<M>&, OPERATION, int, std::vector<short> &carrySet); 
    template <class T, class M>
    static void resultCollector(bool);
    template <class T, class M>
    static void scheduler(const std::vector<T>&, const std::vector<T>&, std::vector<M>*, OPERATION, int, int);

};

template <class T, class M>
void
Parallelizer :: scheduler(const std::vector<T> &block_v1, const std::vector<T> &block_v2, std::vector<M> *result, OPERATION op, int st_idx, int end_idx)    {
 
        ThreadPool<OperationThread<T, M> > *tp = ThreadPool<OperationThread<T, M> >::getInstance();
        OperationThread<T, M> *ot;
        while ((ot=tp->getFreeThread()) == NULL) {
           Parallelizer::resultCollector<T,M>(false); 
        //   pthread_yield();
        }
                
        ot->setOp1(block_v1);
        ot->setOp2(block_v2);
        ot->setStIdx(st_idx);
        ot->setEndIdx(end_idx);
        ot->setOperation(op);
        ot->setResult(result);
        ot->setThreadState(THREAD_SCHED);

        while (ot->getThreadState() == THREAD_SCHED) {
            pthread_cond_signal(ot->getCondSchedule());
         //   pthread_yield();
        }

}

template <class T, class M> 
void
Parallelizer :: executeBatchRequest(const std::vector<T> &oper1, const std::vector<T> &oper2, std::vector<M> &result, OPERATION op, int limit, std::vector<short> &carrySet)    {
    
    ThreadPool<OperationThread<T, M> > *tp = ThreadPool<OperationThread<T, M> >::getInstance();
    int blocks = limit/BLOCK_SIZE;
    int mod    = limit % BLOCK_SIZE;
    int i = 0;

    for (i = 0; i < blocks; i++)    {
        std::vector<T>   block_v1(&oper1[i*BLOCK_SIZE], &oper1[i*BLOCK_SIZE + BLOCK_SIZE]);
        std::vector<T>   block_v2(&oper2[i*BLOCK_SIZE], &oper2[i*BLOCK_SIZE + BLOCK_SIZE]);
        scheduler (block_v1, block_v2, &result, op, i * BLOCK_SIZE,i * BLOCK_SIZE + BLOCK_SIZE); 
    }
    if (mod != 0)   {
        std::vector<T>   block_v1(&oper1[i*BLOCK_SIZE], &oper1[limit]);
        std::vector<T>   block_v2(&oper2[i*BLOCK_SIZE], &oper2[limit]);
        scheduler (block_v1, block_v2, &result, op, i * BLOCK_SIZE, limit); 
    }
    Parallelizer::resultCollector<T, M>(true);

}

//  Result collector which 
//  sets the result of THREAD_DONE thread, and adds it back to the free_list
template <class T, class M>
void
Parallelizer :: resultCollector(bool blocking)    {
    
   bool allDone = false;
   do   {
       ThreadPool<OperationThread<T, M> > *tp = ThreadPool<OperationThread<T, M> >::getInstance();
       std::vector<struct ThreadPool<OperationThread<T,M> >::thread_node*> v = tp->getDoneThreads(allDone);
/*       for (int i = 0; i < v.size(); i++)   {
            for (int i = v[i]->thread->getStIdx(), j = 0; i < v[i]->thread->getEndIdx(); i++)
                result[i] = v[i]->thread->getResult()[j++];
       }*/
       tp->addFreeThreads(v);
   } while (blocking && !allDone);

}

#endif  //  _INC_PARALLELIZER_H
