#ifndef _INC_PARALLELIZER_H
#define _INC_PARALLELIZER_H

#include <vector>
#include <time.h>
#include <map>
#include <pthread.h>
#include "OperationThread.h"
#include "ThreadPool.h"
#include <iostream>
#include <cstdio>

#include "types.h"

class Parallelizer  {
public:
    //  + - / < > == 
    template <class T, class M>
    static void executeBatchRequest(const std::vector<T>&, const std::vector<T>&, std::vector<M>&, OPERATION, int, std::vector<T> &carrySet); 

    //  << >>
    template <class T, class M>
    static void executeBatchRequest(const std::vector<T>&, const int&, std::vector<M>&, OPERATION, int, std::vector<T> &carrySet); 

    //  *
    template <class T, class M>
    static std::vector<std::vector<M> > executeBatchRequest(const std::vector<T>&, const std::vector<T>&, OPERATION); 

    template <class T, class M>
    static void ThreadGarbageCollector(bool);

    template <class T, class M>
    static void scheduler(const std::vector<T>&, const std::vector<T>&, std::vector<M>*, std::vector<T>*, OPERATION, int, int, bool isShift = false, int shift= 0);

    template <class T, class M>
    static void scheduler(const std::vector<T>&, const T&, std::vector<T>*, OPERATION);

};

template<class T, class M>
void
Parallelizer :: scheduler(const std::vector<T> &v1, const T &op2, std::vector<T> *intermediateResult, OPERATION op)   {

        ThreadPool<OperationThread<T, M> > *tp = ThreadPool<OperationThread<T, M> >::getInstance();
        OperationThread<T, M> *ot;
        while ((ot=tp->getFreeThread()) == NULL) {
           Parallelizer::ThreadGarbageCollector<T,M>(false); 
           pthread_yield();
        }
                
        ot->setOp1(v1);
        ot->setMultiplier(op2);
        ot->setStIdx(0);
        ot->setEndIdx(v1.size());
        ot->setOperation(op);
        ot->setResult(intermediateResult);
        ot->setThreadState(THREAD_SCHED);

        while (ot->getThreadState() == THREAD_SCHED) {
       //     pthread_mutex_lock(ot->getBusyLock());
            pthread_cond_signal(ot->getCondSchedule());
       //     pthread_mutex_unlock(ot->getBusyLock());
            pthread_yield();
        }
   
}

template<class T, class M>
std::vector<std::vector<M> >
Parallelizer :: executeBatchRequest(const std::vector<T>& v1, const std::vector<T>& v2, OPERATION op)   {

    std::vector<std::vector<M> >    toReturn;

    for (int i = 0; i < v2.size(); i++) {
        std::vector<M> intermediateResult;
        T op2 = v2[i];
        ThreadPool<OperationThread<T, M> > *tp = ThreadPool<OperationThread<T, M> >::getInstance();
        OperationThread<T, M> *ot;
        while ((ot=tp->getFreeThread()) == NULL) {
           Parallelizer::ThreadGarbageCollector<T,M>(false); 
           pthread_yield();
        }
                
        ot->setOp1(v1);
        ot->setMultiplier(op2);
        ot->setStIdx(0);
        ot->setEndIdx(v1.size());
        ot->setOperation(op);
        ot->setResult(&intermediateResult);
        ot->setThreadState(THREAD_SCHED);

        while (ot->getThreadState() == THREAD_SCHED) {
       //     pthread_mutex_lock(ot->getBusyLock());
            pthread_cond_signal(ot->getCondSchedule());
       //     pthread_mutex_unlock(ot->getBusyLock());
            pthread_yield();
        }

//        scheduler(v1, op2, &intermediateResult, op);
        toReturn.push_back(intermediateResult);
    }

    //  barrier
    Parallelizer::ThreadGarbageCollector<T, M>(true);
    return toReturn;
}

template <class T, class M>
void
Parallelizer :: scheduler(const std::vector<T> &block_v1, const std::vector<T> &block_v2, std::vector<M> *result, std::vector<T> *carry, OPERATION op, int st_idx, int end_idx, bool isShift, int shift)    {
 
        ThreadPool<OperationThread<T, M> > *tp = ThreadPool<OperationThread<T, M> >::getInstance();
        OperationThread<T, M> *ot;
        while ((ot=tp->getFreeThread()) == NULL) {
           Parallelizer::ThreadGarbageCollector<T,M>(false); 
           pthread_yield();
        }
                
        ot->setOp1(block_v1);
        if (!isShift)
         ot->setOp2(block_v2);
        else
         ot->setShift(shift);
        ot->setStIdx(st_idx);
        ot->setEndIdx(end_idx);
        ot->setOperation(op);
        ot->setResult(result);
        ot->setCarry(carry);
        ot->setThreadState(THREAD_SCHED);

        while (ot->getThreadState() == THREAD_SCHED) {
       //     pthread_mutex_lock(ot->getBusyLock());
            pthread_cond_signal(ot->getCondSchedule());
       //     pthread_mutex_unlock(ot->getBusyLock());
            pthread_yield();
        }
}

template <class T, class M> 
void
Parallelizer :: executeBatchRequest(const std::vector<T> &oper1, const std::vector<T> &oper2, std::vector<M> &result, OPERATION op, int limit, std::vector<T> &carrySet)    {
    
    ThreadPool<OperationThread<T, M> > *tp = ThreadPool<OperationThread<T, M> >::getInstance();
    int blocks = limit/BLOCK_SIZE;
    int mod    = limit % BLOCK_SIZE;
    int i = 0;

    for (i = 0; i < blocks; i++)    {
        std::vector<T>   block_v1(&oper1[i*BLOCK_SIZE], &oper1[i*BLOCK_SIZE + BLOCK_SIZE]);
        std::vector<T>   block_v2(&oper2[i*BLOCK_SIZE], &oper2[i*BLOCK_SIZE + BLOCK_SIZE]);
        scheduler (block_v1, block_v2, &result, &carrySet, op, i * BLOCK_SIZE,i * BLOCK_SIZE + BLOCK_SIZE); 
    }
    if (mod != 0)   {
        std::vector<T>   block_v1(&oper1[i*BLOCK_SIZE], &oper1[limit]);
        std::vector<T>   block_v2(&oper2[i*BLOCK_SIZE], &oper2[limit]);
        scheduler (block_v1, block_v2, &result, &carrySet, op, i * BLOCK_SIZE, limit); 
    }

    Parallelizer::ThreadGarbageCollector<T, M>(true);
}

template <class T, class M> 
void
Parallelizer :: executeBatchRequest(const std::vector<T> &oper1, const int &shift, std::vector<M> &result, OPERATION op, int limit, std::vector<T> &carrySet)    {
    
    ThreadPool<OperationThread<T, M> > *tp = ThreadPool<OperationThread<T, M> >::getInstance();
    int blocks = limit/BLOCK_SIZE;
    int mod    = limit % BLOCK_SIZE;
    int i = 0;
    std::vector<T> dummy;

    for (i = 0; i < blocks; i++)    {
        std::vector<T>   block_v1(&oper1[i*BLOCK_SIZE], &oper1[i*BLOCK_SIZE + BLOCK_SIZE]);
        scheduler (block_v1, dummy, &result, &carrySet, op, i * BLOCK_SIZE,i * BLOCK_SIZE + BLOCK_SIZE, true, shift); 
    }
    if (mod != 0)   {
        std::vector<T>   block_v1(&oper1[i*BLOCK_SIZE], &oper1[limit]);
        scheduler (block_v1, dummy, &result, &carrySet, op, i * BLOCK_SIZE, limit, true, shift); 
    }
    //  like a barrier
    Parallelizer::ThreadGarbageCollector<T, M>(true);
}

//  Result collector which 
//  sets the result of THREAD_DONE thread, and adds it back to the free_list
template <class T, class M>
void
Parallelizer :: ThreadGarbageCollector(bool blocking)    {
    
   bool allDone = false;
   do   {
       ThreadPool<OperationThread<T, M> > *tp = ThreadPool<OperationThread<T, M> >::getInstance();
       std::vector<struct ThreadPool<OperationThread<T,M> >::thread_node*> v = tp->getDoneThreads(allDone);
       tp->addFreeThreads(v);
   } while (blocking && !allDone);

}

#endif  //  _INC_PARALLELIZER_H
