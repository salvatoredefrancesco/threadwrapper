/*

    The ThreadWrapperX classes are wrappers for QThread objects associated with objects of the QObject derived class T; their role
    is to automatically include an object of the QObject derived class T in a QThread.
    In particular they allow us to create and delete QThread-QObject couples from another thread in an easy, fast and secure way, like
    objects of any other class, thanks to the internal automatic controls (using QSemaphore).

    As the QObject derived class T constructor may require some arguments, the ThreadWrapperX class constructor support a maximum
    of 7 arguments, so we have 8 different classes:
        ThreadWrapper0, if the QObjcet derived class constructor does not have any arguments
        ThreadWrapper1, if the QObjcet derived class constructor has 1 argument
        ThreadWrapper2, if the QObjcet derived class constructor has 2 arguments
        ThreadWrapper3, if the QObjcet derived class constructor has 3 arguments
        ThreadWrapper4, if the QObjcet derived class constructor has 4 arguments
        ThreadWrapper5, if the QObjcet derived class constructor has 5 arguments
        ThreadWrapper6, if the QObjcet derived class constructor has 6 arguments
        ThreadWrapper7, if the QObjcet derived class constructor has 7 arguments

    For example, having a QObject derived class constructor with 3 arguments arg1, arg2, arg3 of type Arg1, Arg2, Arg3 respectively,
    we can create a QThread-QObject couple in the following way:
        ThreadWrapper3<Object,Arg1,Arg2,Arg3> *threadWrapperObject;
        threadWrapperObject = new ThreadWrapper3<Object,Arg1,Arg2,Arg3>(arg1,arg2,arg3);
        ....... do stuff .....
        delete threadWrapperObject;
    Obviously we can also define a priority for the thread, changing the second row in the code with the following one
        threadWrapperObject = new ThreadWrapper3<Object,Arg1,Arg2,Arg3>(arg1,arg2,arg3,QThread::HighestPriority);
    In order to get the pointer to the object of QObject type (useful for the signal-slot connections) we must type
    threadWrapperObject->t.

*/


#ifndef THREADWRAPPER_H
#define THREADWRAPPER_H

#include "threadobjectt.h"

template <class T>
class ThreadWrapper0
{

public:
    ThreadWrapper0(QThread::Priority _threadPriority = QThread::InheritPriority){
        initialize(_threadPriority, true);
    }

protected:
    ThreadWrapper0(QThread::Priority _threadPriority, bool _enabled){
        initialize(_threadPriority, _enabled);
    }

private:
    void initialize(QThread::Priority _threadPriority, bool _enabled){
        threadPriority = _threadPriority;
        enabled0 = _enabled;          // if there are arguments, it is obviously false
        if(enabled0){
            createThreadObject();
        }
    }

public:
    ~ThreadWrapper0(){
        if(enabled0){
            deleteThreadObject();
        }
    }

protected:
    T *t_;

protected:
    SemaphoreObject semaphoreObject;
    ThreadObjectTArg0<T> *threadObjectTArg0;
    QThread *thread;
    QThread::Priority threadPriority;
    bool enabled0;

protected:
    void createThreadObject(){
        threadObjectTArg0 = new ThreadObjectTArg0<T>(&t_,&semaphoreObject);
        thread = dynamic_cast<QThread*>(threadObjectTArg0);                // we use the thread variable to simplify the code
        thread->start(threadPriority);
        semaphoreObject.acquireResourceForSemaphoreCreation();          // we wait the resource release for semaphoreCreation from the semaphoreObject inside the thread
    }
    void deleteThreadObject(){
        QObject *objectT = dynamic_cast<QObject*>(t_);
        // now we send a deletion signal to the objectT, so we use the QTimer::singleShot(...)
        QTimer::singleShot(0, objectT, SLOT(deleteLater()));
        this->semaphoreObject.acquireResourceForSemaphoreDeletion();            // we wait the resource release for semaphoreDeletion from the semaphoreObject inside the thread
        thread->quit();     // we inform the thread to stop hisself
        thread->wait();     // then we wait the end of the event loop
        delete thread;
    }

public:
    T* t() const {return t_;}

};


template <class T, class Arg1>
class ThreadWrapper1: public ThreadWrapper0<T>
{

public:
    ThreadWrapper1(Arg1 _arg1, QThread::Priority _threadPriority = QThread::InheritPriority) :
      ThreadWrapper0<T>(_threadPriority, false){
        initialize(_arg1, true);
    }

protected:
    ThreadWrapper1(Arg1 _arg1, QThread::Priority _threadPriority, bool _enabled) :
      ThreadWrapper0<T>(_threadPriority, false){
        initialize(_arg1, _enabled);
    }

private:
    void initialize(Arg1 _arg1, bool _enabled){
        arg1 = _arg1;
        enabled1 = _enabled;              // if the argument number is greater than 1, it is obviously false
        if(enabled1){
            createThreadObject();
        }
    }

public:
    ~ThreadWrapper1(){
        if(enabled1){
            this->deleteThreadObject();
        }
    }

protected:
    bool enabled1;
    Arg1 arg1;
    ThreadObjectTArg1<T,Arg1> *threadObjectTArg1;

protected:
    void createThreadObject(){
        threadObjectTArg1 = new ThreadObjectTArg1<T,Arg1>(&(this->t_),arg1,&(this->semaphoreObject));
        this->thread = dynamic_cast<QThread*>(threadObjectTArg1);
        this->thread->start(this->threadPriority);
        this->semaphoreObject.acquireResourceForSemaphoreCreation();
    }

};


template <class T, class Arg1, class Arg2>
class ThreadWrapper2: public ThreadWrapper1<T,Arg1>
{

public:
    ThreadWrapper2(Arg1 _arg1, Arg2 _arg2, QThread::Priority _threadPriority = QThread::InheritPriority) :
        ThreadWrapper1<T,Arg1>(_arg1, _threadPriority, false){
        initialize(_arg2, true);
    }

protected:
    ThreadWrapper2(Arg1 _arg1, Arg2 _arg2, QThread::Priority _threadPriority, bool _enabled) :
      ThreadWrapper1<T,Arg1>(_arg1, _threadPriority, false){
        initialize(_arg2, _enabled);
    }

private:
    void initialize(Arg2 _arg2, bool _enabled){
        arg2 = _arg2;
        enabled2 = _enabled;              // if the argument number is greater than 2, it is obviously false
        if(enabled2){
            createThreadObject();
        }
    }

public:
    ~ThreadWrapper2(){
        if(enabled2){
            this->deleteThreadObject();
        }
    }

protected:
    bool enabled2;
    Arg2 arg2;
    ThreadObjectTArg2<T,Arg1,Arg2> *threadObjectTArg2;

protected:
    void createThreadObject(){
        threadObjectTArg2 = new ThreadObjectTArg2<T,Arg1,Arg2>(&(this->t_),this->arg1,arg2,&(this->semaphoreObject));
        this->thread = dynamic_cast<QThread*>(threadObjectTArg2);
        this->thread->start(this->threadPriority);
        this->semaphoreObject.acquireResourceForSemaphoreCreation();
    }

};


template <class T, class Arg1, class Arg2, class Arg3>
class ThreadWrapper3: public ThreadWrapper2<T,Arg1,Arg2>
{

public:
    ThreadWrapper3(Arg1 _arg1, Arg2 _arg2, Arg3 _arg3, QThread::Priority _threadPriority = QThread::InheritPriority) :
        ThreadWrapper2<T,Arg1,Arg2>(_arg1, _arg2, _threadPriority, false){
        initialize(_arg3, true);
    }

protected:
    ThreadWrapper3(Arg1 _arg1, Arg2 _arg2, Arg3 _arg3, QThread::Priority _threadPriority, bool _enabled) :
      ThreadWrapper2<T,Arg1,Arg2>(_arg1, _arg2, _threadPriority, false){
        initialize(_arg3, _enabled);
    }

private:
    void initialize(Arg3 _arg3, bool _enabled){
        arg3 = _arg3;
        enabled3 = _enabled;              // if the argument number is greater than 3, it is obviously false
        if(enabled3){
            createThreadObject();
        }
    }

public:
    ~ThreadWrapper3(){
        if(enabled3){
            this->deleteThreadObject();
        }
    }

protected:
    bool enabled3;
    Arg3 arg3;
    ThreadObjectTArg3<T,Arg1,Arg2,Arg3> *threadObjectTArg3;

protected:
    void createThreadObject(){
        threadObjectTArg3 = new ThreadObjectTArg3<T,Arg1,Arg2,Arg3>(&(this->t_),this->arg1,this->arg2,arg3,&(this->semaphoreObject));
        this->thread = dynamic_cast<QThread*>(threadObjectTArg3);
        this->thread->start(this->threadPriority);
        this->semaphoreObject.acquireResourceForSemaphoreCreation();
    }

};


template <class T, class Arg1, class Arg2, class Arg3, class Arg4>
class ThreadWrapper4: public ThreadWrapper3<T,Arg1,Arg2,Arg3>
{

public:
    ThreadWrapper4(Arg1 _arg1, Arg2 _arg2, Arg3 _arg3, Arg4 _arg4, QThread::Priority _threadPriority = QThread::InheritPriority) :
        ThreadWrapper3<T,Arg1,Arg2,Arg3>(_arg1, _arg2, _arg3, _threadPriority, false){
        initialize(_arg4, true);
    }

protected:
    ThreadWrapper4(Arg1 _arg1, Arg2 _arg2, Arg3 _arg3, Arg4 _arg4, QThread::Priority _threadPriority, bool _enabled) :
      ThreadWrapper3<T,Arg1,Arg2,Arg3>(_arg1, _arg2, _arg3, _threadPriority, false){
        initialize(_arg4, _enabled);
    }

private:
    void initialize(Arg4 _arg4, bool _enabled){
        arg4 = _arg4;
        enabled4 = _enabled;              // if the argument number is greater than 4, it is obviously false
        if(enabled4){
            createThreadObject();
        }
    }

public:
    ~ThreadWrapper4(){
        if(enabled4){
            this->deleteThreadObject();
        }
    }

protected:
    bool enabled4;
    Arg4 arg4;
    ThreadObjectTArg4<T,Arg1,Arg2,Arg3,Arg4> *threadObjectTArg4;

protected:
    void createThreadObject(){
        threadObjectTArg4 = new ThreadObjectTArg4<T,Arg1,Arg2,Arg3,Arg4>(&(this->t_),this->arg1,this->arg2,this->arg3,arg4,&(this->semaphoreObject));
        this->thread = dynamic_cast<QThread*>(threadObjectTArg4);
        this->thread->start(this->threadPriority);
        this->semaphoreObject.acquireResourceForSemaphoreCreation();
    }

};


template <class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class ThreadWrapper5: public ThreadWrapper4<T,Arg1,Arg2,Arg3,Arg4>
{

public:
    ThreadWrapper5(Arg1 _arg1, Arg2 _arg2, Arg3 _arg3, Arg4 _arg4, Arg5 _arg5, QThread::Priority _threadPriority = QThread::InheritPriority) :
        ThreadWrapper4<T,Arg1,Arg2,Arg3,Arg4>(_arg1, _arg2, _arg3, _arg4, _threadPriority, false){
        initialize(_arg5, true);
    }

protected:
    ThreadWrapper5(Arg1 _arg1, Arg2 _arg2, Arg3 _arg3, Arg4 _arg4, Arg5 _arg5, QThread::Priority _threadPriority, bool _enabled) :
      ThreadWrapper4<T,Arg1,Arg2,Arg3,Arg4>(_arg1, _arg2, _arg3, _arg4, _threadPriority, false){
        initialize(_arg5, _enabled);
    }

private:
    void initialize(Arg5 _arg5, bool _enabled){
        arg5 = _arg5;
        enabled5 = _enabled;              // if the argument number is greater than 5, it is obviously false
        if(enabled5){
            createThreadObject();
        }
    }

public:
    ~ThreadWrapper5(){
        if(enabled5){
            this->deleteThreadObject();
        }
    }

protected:
    bool enabled5;
    Arg5 arg5;
    ThreadObjectTArg5<T,Arg1,Arg2,Arg3,Arg4,Arg5> *threadObjectTArg5;

protected:
    void createThreadObject(){
        threadObjectTArg5 = new ThreadObjectTArg5<T,Arg1,Arg2,Arg3,Arg4,Arg5>(&(this->t_),this->arg1,this->arg2,this->arg3,this->arg4,arg5,&(this->semaphoreObject));
        this->thread = dynamic_cast<QThread*>(threadObjectTArg5);
        this->thread->start(this->threadPriority);
        this->semaphoreObject.acquireResourceForSemaphoreCreation();
    }

};


template <class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class ThreadWrapper6: public ThreadWrapper5<T,Arg1,Arg2,Arg3,Arg4,Arg5>
{

public:
    ThreadWrapper6(Arg1 _arg1, Arg2 _arg2, Arg3 _arg3, Arg4 _arg4, Arg5 _arg5, Arg6 _arg6, QThread::Priority _threadPriority = QThread::InheritPriority) :
        ThreadWrapper5<T,Arg1,Arg2,Arg3,Arg4,Arg5>(_arg1, _arg2, _arg3, _arg4, _arg5, _threadPriority, false){
        initialize(_arg6, true);
    }

protected:
    ThreadWrapper6(Arg1 _arg1, Arg2 _arg2, Arg3 _arg3, Arg4 _arg4, Arg5 _arg5, Arg6 _arg6, QThread::Priority _threadPriority, bool _enabled) :
      ThreadWrapper5<T,Arg1,Arg2,Arg3,Arg4,Arg5>(_arg1, _arg2, _arg3, _arg4, _arg5, _threadPriority, false){
        initialize(_arg6, _enabled);
    }

private:
    void initialize(Arg6 _arg6, bool _enabled){
        arg6 = _arg6;
        enabled6 = _enabled;              // if the argument number is greater than 6, it is obviously false
        if(enabled6){
            createThreadObject();
        }
    }

public:
    ~ThreadWrapper6(){
        if(enabled6){
            this->deleteThreadObject();
        }
    }

protected:
    bool enabled6;
    Arg6 arg6;
    ThreadObjectTArg6<T,Arg1,Arg2,Arg3,Arg4,Arg5,Arg6> *threadObjectTArg6;

protected:
    void createThreadObject(){
        threadObjectTArg6 = new ThreadObjectTArg6<T,Arg1,Arg2,Arg3,Arg4,Arg5,Arg6>(&(this->t_),this->arg1,this->arg2,this->arg3,this->arg4,this->arg5,arg6,&(this->semaphoreObject));
        this->thread = dynamic_cast<QThread*>(threadObjectTArg6);
        this->thread->start(this->threadPriority);
        this->semaphoreObject.acquireResourceForSemaphoreCreation();
    }

};


template <class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
class ThreadWrapper7: public ThreadWrapper6<T,Arg1,Arg2,Arg3,Arg4,Arg5,Arg6>
{

public:
    ThreadWrapper7(Arg1 _arg1, Arg2 _arg2, Arg3 _arg3, Arg4 _arg4, Arg5 _arg5, Arg6 _arg6, Arg7 _arg7, QThread::Priority _threadPriority = QThread::InheritPriority) :
        ThreadWrapper6<T,Arg1,Arg2,Arg3,Arg4,Arg5,Arg6>(_arg1, _arg2, _arg3, _arg4, _arg5, _arg6, _threadPriority, false){
        initialize(_arg7, true);
    }

protected:
    ThreadWrapper7(Arg1 _arg1, Arg2 _arg2, Arg3 _arg3, Arg4 _arg4, Arg5 _arg5, Arg6 _arg6, Arg7 _arg7, QThread::Priority _threadPriority, bool _enabled) :
      ThreadWrapper6<T,Arg1,Arg2,Arg3,Arg4,Arg5,Arg6>(_arg1, _arg2, _arg3, _arg4, _arg5, _arg6, _threadPriority, false){
        initialize(_arg7, _enabled);
    }

private:
    void initialize(Arg7 _arg7, bool _enabled){
        arg7 = _arg7;
        enabled7 = _enabled;              // if the argument number is greater than 7, it is obviously false
        if(enabled7){
            createThreadObject();
        }
    }

public:
    ~ThreadWrapper7(){
        if(enabled7){
            this->deleteThreadObject();
        }
    }

protected:
    bool enabled7;
    Arg7 arg7;
    ThreadObjectTArg7<T,Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7> *threadObjectTArg7;

protected:
    void createThreadObject(){
        threadObjectTArg7 = new ThreadObjectTArg7<T,Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7>(&(this->t_),this->arg1,this->arg2,this->arg3,this->arg4,this->arg5,this->arg6,arg7,&(this->semaphoreObject));
        this->thread = dynamic_cast<QThread*>(threadObjectTArg7);
        this->thread->start(this->threadPriority);
        this->semaphoreObject.acquireResourceForSemaphoreCreation();
    }

};






#endif // THREADWRAPPER_H
