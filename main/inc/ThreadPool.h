#ifndef _INC_THREAD_POOL_H
#define _INC_THREAD_POOL_H

#include    <pthread.h>
#define POOL_CNT    100

//  A class which manages POOL_CNT threads which can be used for performing a
//  computation.
template <class T>
class ThreadPool    {

private:
    struct  thread_node {
       int  tid;
       T    *thread;
       struct thread_list *next;
    } *free_list, *task_queue;
    pthread_cond_t cond_free_list;   //  condition variable to check if free_list is empty.

    ThreadPool();
    void init();
    ~ThreadPool();
    static ThreadPool<T>* singletonInstance; 

    //  Get, Put operations of the free list
    T*   getFreeThread();
    void addThreadFreeList(int);

public:
    static ThreadPool<T>* getInstance();

};



#endif  // _INC_THREAD_POOL_H

