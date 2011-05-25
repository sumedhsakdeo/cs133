#include    "OperationThread.h"

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

