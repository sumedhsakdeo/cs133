#ifndef _INC_TYPES_H_
#define _INC_TYPES_H_

typedef enum {
        ADD = 0,
        SUB,
        MULT,
        DIV,
        AND,
        OR,
        XOR,
        NOT,
        EQ,
        GT,
        LT
        } OPERATION;

typedef enum {
        THREAD_START = 0,
        THREAD_SCHED,
        THREAD_STOP, 
        THREAD_RUNNING,
        THREAD_WAITING,
        THREAD_DONE
        } THREAD_STATE;

#endif  //  _INC_TYPES_H_
