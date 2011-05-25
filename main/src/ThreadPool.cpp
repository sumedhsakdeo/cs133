#include    "ThreadPool.h"

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
//  Pick up the next free thread from the pool
template <class T>
T*
ThreadPool<T>  ::  getFreeThread()  {

    if (free_list == NULL)  
        pthread_cond_wait (&cond_free_list, NULL);
    struct thread_node *tmp = free_list;
    T   *to_return = tmp->thread;
    //  remove from free_list
    free_list  = free_list->next;
    //  add it to the ask_que
    tmp-> next = task_queue;
    task_queue = tmp;
    return to_return;  
}

//  Add the thread back to free_list and remove from task queue
template <class T>
void
ThreadPool<T> :: addThreadFreeList(int tid) {
    
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
        }
        prev = tmp;
        tmp = tmp->next;
   }
   pthread_cond_signal(&cond_free_list);

}
