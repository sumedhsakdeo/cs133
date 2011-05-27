#ifndef _INC_THREAD_POOL_H
#define _INC_THREAD_POOL_H
#include    <iostream>
#include    <pthread.h>
#define POOL_CNT    30

//  A class which manages POOL_CNT threads which can be used for performing a
//  computation.
template <class T>
class ThreadPool    {

public:
    static ThreadPool<T>* getInstance();

    struct  thread_node {
       int  tid;
       T    *thread;
       struct thread_node *next;
    } ;


    //  Get, Put operations of the free list
    T*   getFreeThread();
    void addThreadFreeList(int);
    //  first parameter: set if all the task_queue is done, and second parameter is true
    std::vector<struct thread_node*>  getDoneThreads(bool&);
    void addFreeThreads(std::vector<struct thread_node*>&);

    ~ThreadPool();

private:
    pthread_cond_t cond_free_list;   //  condition variable to check if free_list is empty.
    pthread_mutex_t mutex_free_list; //  mutex variable to check if free_list is locaked

    ThreadPool();
    void init();
    static ThreadPool<T>* singletonInstance; 
    
    struct thread_node *free_list, *task_queue;


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
    
	task_queue = NULL;
	free_list  = NULL;
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
   std::cout << "*******thread constructor\n";
   pthread_mutex_init(&mutex_free_list, NULL);
   pthread_cond_init(&cond_free_list, NULL);
   init();
}

//  ThreadPool destructore
template <class T>
ThreadPool<T> :: ~ThreadPool()   {
   std::cout << "**********thread destructor\n";
   struct thread_node *tmp = free_list;
   while (free_list)    {
        free_list = free_list->next;
        delete tmp;
        tmp = free_list;
   }
   tmp = task_queue;
   while (task_queue)    {
        task_queue = task_queue->next;
        delete tmp;
        tmp = task_queue;
   }
   pthread_mutex_destroy(&mutex_free_list);
   pthread_cond_destroy(&cond_free_list);
}

//  Pick up the next free thread from the pool
template <class T>
T*
ThreadPool<T>  ::  getFreeThread()  {

    //pthread_mutex_lock(&mutex_free_list);
    if (free_list == NULL)  
        return NULL;
    //pthread_cond_wait (&cond_free_list, &mutex_free_list);
    struct thread_node *tmp = free_list;
    T   *to_return = tmp->thread;
    //  remove from free_list
    free_list  = free_list->next;
    //  add it to the ask_que
    tmp-> next = task_queue;
    task_queue = tmp;
    //pthread_mutex_unlock(&mutex_free_list);
    return to_return;  
}



//  Add the thread back to free_list and remove from task queue
template <class T>
void
ThreadPool<T> :: addThreadFreeList(int tid) {
    
   pthread_mutex_lock(&mutex_free_list);
   struct thread_node *tmp = task_queue;
   struct thread_node *prev = NULL;
   while (tmp)  {
        if (tmp->tid == tid) {
           if (prev != NULL) {
                //  tid is the any middle or last node in task_queue
               prev->next = tmp->next;
               tmp->next = free_list;
               free_list = tmp;
           } else   {
                // tid is the first node in the list
               task_queue = tmp->next;
               tmp->next = free_list;
               free_list = tmp;
           }
           break;
        }
        prev = tmp;
        tmp = tmp->next;
   }
   pthread_mutex_unlock(&mutex_free_list);
   pthread_cond_signal(&cond_free_list);
}

template<class T>
std::vector<struct ThreadPool<T>::thread_node*>
ThreadPool<T> :: getDoneThreads(bool &allDone)    {
    
    std::vector<struct thread_node*> toReturn;
    struct thread_node *tmp = task_queue;
    struct thread_node *prev = NULL;
    if (tmp == NULL)
        allDone = true;
    while (tmp) {
        if (tmp->thread != NULL && tmp->thread->getThreadState() == THREAD_DONE)   {
           toReturn.push_back(tmp); 
           if (prev != NULL)    {
                prev->next = tmp->next;
           } else   {
                task_queue = task_queue->next;
           }
           tmp = tmp->next;
           continue;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    if (task_queue == NULL)
        allDone = true;
    else    
        allDone = false;
    return toReturn;
}

template<class T>
void
ThreadPool<T> ::  addFreeThreads(std::vector<struct thread_node*> &toAdd) {
    
    for (int i=0; i < toAdd.size(); i++)    {
        if (free_list == NULL)  {            
            toAdd[i]->next = NULL;
            free_list = toAdd[i];
        } else {
            toAdd[i]->next = free_list;
            free_list = toAdd[i];
        }
        toAdd[i]->thread->setThreadState(THREAD_WAITING);
    }

}

#endif  // _INC_THREAD_POOL_H

