#include    "ThreadPool.h"

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
