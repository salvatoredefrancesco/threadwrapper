# threadwrapper

A convenient class to use QObject in a QThread


    The ThreadWrapperX classes are wrappers for QThread objects associated with objects of the QObject derived class T; their role is to automatically include an object of the QObject derived class T in a QThread.
    In particular they allow us to create and delete QThread-QObject couples from another thread in an easy, fast and secure way, like objects of any other class, thanks to the internal automatic controls (using QSemaphore).

    As the QObject derived class T constructor may require some arguments, the ThreadWrapperX class constructor support a maximum of 7 arguments, so we have 8 different classes:
        ThreadWrapper0, if the QObjcet derived class constructor does not have any arguments
        ThreadWrapper1, if the QObjcet derived class constructor has 1 argument
        ThreadWrapper2, if the QObjcet derived class constructor has 2 arguments
        ThreadWrapper3, if the QObjcet derived class constructor has 3 arguments
        ThreadWrapper4, if the QObjcet derived class constructor has 4 arguments
        ThreadWrapper5, if the QObjcet derived class constructor has 5 arguments
        ThreadWrapper6, if the QObjcet derived class constructor has 6 arguments
        ThreadWrapper7, if the QObjcet derived class constructor has 7 arguments

    For example, having a QObject derived class constructor with 3 arguments arg1, arg2, arg3 of type Arg1, Arg2, Arg3 respectively, we can create a QThread-QObject couple in the following way:
        ThreadWrapper3<Object,Arg1,Arg2,Arg3> *threadWrapperObject;
        threadWrapperObject = new ThreadWrapper3<Object,Arg1,Arg2,Arg3>(arg1,arg2,arg3);
        ....... do stuff .....
        delete threadWrapperObject;
    Obviously we can also define a priority for the thread, changing the second row in the code with the following one
        threadWrapperObject = new ThreadWrapper3<Object,Arg1,Arg2,Arg3>(arg1,arg2,arg3,QThread::HighestPriority);
    In order to get the pointer to the object of QObject type (useful for the signal-slot connections) we must type
    threadWrapperObject->t().
