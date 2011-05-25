#ifndef _INC_OP_THREAD_H
#define _INC_OP_THREAD_H

#include    "Thread.h"

// This class is child class of abstract Thread which is templatized.
// It contains two operands, and operation enum, and placeholder for result of the
// computation.
template <class T, class M>
class OperationThread   : public Thread {
    
private:
    T       op1, op2; 
    M       result;
    OPERATION operation;

public:

    //  input paramete is the thread ID
    OperationThread(int);
    ~OperationThread();

    //  runs when a thread waiting on a condition variable is scheduled i.e. thread state
    //  is THREAD_RUNNING
    void run();
    
    // getter setter for operand 1 
    T      getOp1();
    void   setOp1(T op1);

    // getter setter for operand 2 
    T      getOp2();
    void   setOp2(T op2);

    //  getter for result
    M      getResult();
    
    // getter setter for operation
    OPERATION        getOperation();
    void             setOperation(OPERATION);


};

#endif  // _INC_OP_THREAD_H
