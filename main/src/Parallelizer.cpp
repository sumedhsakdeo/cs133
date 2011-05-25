#include    "Parallelizer.h"
#include    "OperationThread.h"
#include    "ThreadPool.h"
#include    <pthread.h>

using namespace std;

template <class T, class M> 
vector<M>
Parallelizer :: executeBatchRequest(const vector<T> &oper1, const vector<T> &oper2, OPERATION op)    {
    
    vector<M> result(oper1.size());
    ThreadPool<OperationThread<T, M> > *tp = ThreadPool<OperationThread<T, M> >::getInstance();

    for (int i=0; i < oper1.size(); i++)    {

        pthread_cond_t      cond_callback = PTHREAD_COND_INITIALIZER;
        OperationThread<T, M> *ot = tp->getFreeThread();
        ot->setOp1(oper1[i]);
        ot->setOp2(oper2[i]);
        ot->setOperation(op);
        ot->setThreadState(THREAD_SCHED);
        ot->setCondCallback(&cond_callback);

        pthread_cond_signal(ot->getCondSchedule());
        pthread_cond_wait(&cond_callback, NULL); 

        result[i] = ot->getResult();
        tp->addThreadFreeList(ot);
    }

    return result;
}
