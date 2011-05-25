#include "Thread.h"


Thread  ::  Thread(int ID)    {

    setThreadID(ID);
    setBusyFlag(false);
    pthread_create(&thread, NULL, &start, (void*) this); 
    pthread_mutex_init(&busyLock, NULL);
    pthread_cond_init(&cond_schedule, NULL);

}

Thread  ::  ~Thread()   {

    pthread_join(thread, NULL);
    pthread_mutex_destroy(&busyLock);
    pthread_cond_destroy(&cond_schedule);

}

inline pthread_t 
Thread :: getThreadID()   {
    return this->ID; 
}

inline void
Thread :: setThreadID(int ID)    {
    this->ID = ID;
}

inline bool
Thread  :: getBusyFlag()    {
    return this->busy;
}

inline void
Thread  :: setBusyFlag(bool busy)   {
    this->busy = busy;
}

inline THREAD_STATE
Thread  ::  getThreadState()    {
    return this->state;
}

inline  void
Thread  ::  setThreadState(THREAD_STATE state)    {
    this->state = state;
}

inline pthread_cond_t*
Thread  ::  getCondSchedule()   {
    return &this->cond_schedule;
}

inline void
Thread  ::  setCondCallback(pthread_cond_t *cond_callback)  {
    this->cond_callback = cond_callback;
}

//  This thread runs infinitely and waits for a signal THREAD_START before it runs.
void * 
Thread  :: start(void *self) {
    
    bool exitFlag = false;
    Thread *t = (Thread*) self;

    while(1)    {
        pthread_cond_wait(&t->cond_schedule, &t->busyLock);
        switch (t->getThreadState())   {
            case THREAD_STOP:
                exitFlag = true;
                t->state = THREAD_STOP;
                pthread_mutex_unlock(&t->busyLock);
                break;
            case THREAD_SCHED:
                t->state = THREAD_RUNNING;
                t->run();
                pthread_cond_signal(t->cond_callback);
                break;
        }
        if  (exitFlag)
            break;
        t->state = THREAD_WAITING;
    }
    
}
