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

// Global static pointer used to ensure a single instance of the class
template <class T>
ThreadPool<T>* ThreadPool<T>::singletonInstance = NULL; 

// Get the singleton instance of the class
template <class T>
ThreadPool<T>* ThreadPool<T> :: getInstance()    {
   if (!singletonInstance)  {
        singletonInstance = new ThreadPool<T>();
   }
   return singletonInstance;
}

template <class T>
void
ThreadPool<T>  ::  init() {
    
    for (int i = 0; i < POOL_CNT; i++)    {
        struct thread_node *tmp = new struct thread_node;
        tmp->tid    = i;
        tmp->thread = new T(i);
        tmp->next  = free_list;
        free_list = tmp;
    }

}

//  ThreadPool constructor
template <class T>
ThreadPool<T> :: ThreadPool()   {
   pthread_cond_init(&cond_free_list, NULL);
   init();
}

//  ThreadPool destructore
template <class T>
ThreadPool<T> :: ~ThreadPool()   {
   pthread_cond_destroy(&cond_free_list);
}

#endif  // _INC_THREAD_POOL_H

