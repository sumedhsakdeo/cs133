#ifndef _INC_THREAD_H_
#define _INC_THREAD_H_

#include    <pthread.h>
#include    "types.h"
#include    <iostream>

// Abstract class Thread
class Thread    {

private:
    
    pthread_t   thread;               //  actual thread
    int         ID;                   //  ID known to application like ThreadPool
    bool        busy;                 //  thread is busy
    pthread_mutex_t  busyLock;        //  thread in THREAD_RUNNING state
    pthread_cond_t cond_schedule;     //  condition variable of each thread.
    THREAD_STATE   state;             //  stores the current thread state

public:
    
    Thread(int);
    virtual ~Thread();
    
    //  getter setter for ThreadID
    pthread_t   getThreadID();
    void        setThreadID(int);

    //  getter setter for BusyFlag
    bool        getBusyFlag();
    void        setBusyFlag(bool);
    
    //  getter setter for THREAD_STATE
    THREAD_STATE getThreadState();
    void         setThreadState(THREAD_STATE state);
   
    //  getter condition variable might be used for signaling
    pthread_cond_t*   getCondSchedule();

    //  getter busy lock variable
    pthread_mutex_t*   getBusyLock();

    //  setter condition variable might be used for callback
    void  setCondCallback(pthread_cond_t*);

    //  entry function start
    //  This function runs infinitely till it receives a THREAD_KILL signal from calling
    //  process
    static void*        start(void *); 

    //  run method for each thread to execute when triggered
    virtual void      run() = 0;
    
};

Thread  ::  Thread(int ID)    {

    setThreadID(ID);
    setBusyFlag(false);
    setThreadState(THREAD_WAITING);
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

inline pthread_mutex_t*
Thread  ::  getBusyLock()   {
    return &this->busyLock;
}


//  This thread runs infinitely and waits for a signal THREAD_START before it runs.
void * 
Thread  :: start(void *self) {
    
    bool exitFlag = false;
    Thread *t = (Thread*) self;

    while(1)    {
        pthread_mutex_lock(&t->busyLock);
        while (t->getThreadState() == THREAD_WAITING)   {
            pthread_cond_wait(t->getCondSchedule(), &t->busyLock);
        }
        switch (t->getThreadState())   {
            case THREAD_STOP:
                exitFlag = true;
                t->state = THREAD_STOP;
                break;
            case THREAD_SCHED:
                t->run();
                break;
        }
        pthread_mutex_unlock(&t->busyLock);
        if  (exitFlag)
            break;
    }

    pthread_exit(NULL);
}

#endif // _INC_THREAD_H_
