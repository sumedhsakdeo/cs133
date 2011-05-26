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

template <class T, class M>
inline T
OperationThread<T, M>  ::  getOp1()    {
    return this->op1;
}

template <class T, class M>
inline void
OperationThread<T, M>  ::  setOp1(T op1)    {
    this->op1 = op1;
}

template <class T, class M>
inline T
OperationThread<T, M>  ::  getOp2()    {
    return this->op2;
}

template <class T, class M>
inline void
OperationThread<T, M>  ::  setOp2(T op2)    {
    this->op2 = op2;
}

template <class T, class M>
inline M
OperationThread<T, M>  ::  getResult()    {
    return this->result;
}

template <class T, class M>
inline OPERATION
OperationThread<T, M>  ::  getOperation()  {
    return this->operation;    
}

template <class T, class M>
inline void
OperationThread<T, M>  ::  setOperation(OPERATION operation)  {
   this->operation = operation;
}


template <class T, class M>
void
OperationThread<T, M> :: run()   {
    
    switch (operation)  {
        case ADD:
            this->result = this->op1 + this->op2; 
            break;
        case SUB:
            this->result = this->op1 - this->op2;
            break;
    }

}

#endif  // _INC_OP_THREAD_H
