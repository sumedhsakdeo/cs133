#ifndef _INC_THREAD_H_
#define _INC_THREAD_H_

#include    <pthread.h>
#include    "types.h"

// Abstract class Thread
class Thread    {

private:
    
    pthread_t   thread;             //  actual thread
    int         ID;                 //  ID known to application like ThreadPool
    bool        busy;               //  thread is busy
    pthread_mutex_t  busyLock;   //  thread in THREAD_RUNNING state
    pthread_cond_t cond_schedule;   //  condition variable of each thread.
    pthread_cond_t *cond_callback;  //  condition variable of callback.
    THREAD_STATE   state;           //  stores the current thread state

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

    //  getter setter condition variable might be used for callback
    void  setCondCallback(pthread_cond_t*);

    //  entry function start
    //  This function runs infinitely till it receives a THREAD_KILL signal from calling
    //  process
    static void*        start(void *); 

    //  run method for each thread to execute when triggered
    virtual void      run() = 0;
    
};

#endif // _INC_THREAD_H_
