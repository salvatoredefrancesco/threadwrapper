/*

    The ThreadObjectTArgX classes include an object of a QObject derived class T in a QThread.

    Depending on the arguments used for the object, we can distinguish between 8 classes:
        ThreadObjectTArg0, that does not use any argument
        ThreadObjectTArg1, that use 1 argument
        ThreadObjectTArg2, that use 2 argument
        ThreadObjectTArg3, that use 3 argument
        ThreadObjectTArg4, that use 4 argument
        ThreadObjectTArg5, that use 5 argument
        ThreadObjectTArg6, that use 6 argument
        ThreadObjectTArg7, that use 7 argument
    These classes are used by the ThreadWrapperX classes to generate the wrappers responsible for creating of a QThread associated
    with an object of a QObject derived class T.

*/


#ifndef THREADOBJECTT_H
#define THREADOBJECTT_H

#include <QThread>
#include <QSemaphore>
#include <QTimer>
#include "semaphoreobject.h"


template <class T>
class ThreadObjectTArg0: public QThread
{

public:
    ThreadObjectTArg0(T **_t, SemaphoreObject *_semaphoreObject){
        t = _t;
        semaphoreObjectReceived = _semaphoreObject;
    }
    ~ThreadObjectTArg0(){
        delete semaphoreObject;
    }

public:
    T **t;

private:
    SemaphoreObject *semaphoreObjectReceived;
    SemaphoreObject *semaphoreObject;

protected:
    void run(){
        createSemaphoreObject();          /* the semaphoreObject creation is always before the t creation, because the first
                                               thing in the event loop needs to be the releaseResourceForSemaphoreCreation (and
                                               not a possible t "delayed" slot) */
        createObjectT();
        createConnections();
        QThread::exec();
    }

protected:
    void createSemaphoreObject(){
        // we use semaphoreObject instead of simple semaphores because (as we can see in a few rows) we need to use a slot,
        // so we need to use a QObject; moreover the slot needs to stay inside this thread, so here's why we need to call
        // the constructor at this point
        semaphoreObject = new SemaphoreObject(semaphoreObjectReceived->semaphoreCreation, semaphoreObjectReceived->semaphoreDeletion);
        // now we say to the semaphoreObject to release a resource for the semaphoreCreation, and as the resource must be released
        // after the exec() command, we use the QMetaObject::invokeMethod with QueuedConnection
        QMetaObject::invokeMethod(semaphoreObject, "releaseResourceForSemaphoreCreation", Qt::QueuedConnection);
    }
    void createConnections(){
        QObject *objectT = dynamic_cast<QObject*>(*t);   /* useful, because during the destruction it must advise semaphoreObject on releasing
                                                            a resource for the semaphoreDeletion */
        connect(objectT, SIGNAL(destroyed()), semaphoreObject, SLOT(releaseResourceForSemaphoreDeletion()), Qt::QueuedConnection);
    }

public slots:
    void createObjectT(){
        //qDebug() << "ObjectTArg0 creation";
        *t = new T();
    }

};


template <class T, class Arg1>
class ThreadObjectTArg1: public ThreadObjectTArg0<T>
{

public:
    ThreadObjectTArg1(T **_t, Arg1 _arg1, SemaphoreObject *_semaphoreObject) :
      ThreadObjectTArg0<T>(_t,_semaphoreObject){
        arg1 = _arg1;
    }

protected:
    Arg1 arg1;

protected:
    void run(){
        this->createSemaphoreObject();          /* the semaphoreObject creation is always before the t creation, because the first
                                               thing in the event loop needs to be the releaseResourceForSemaphoreCreation (and
                                               not a possible t "delayed" slot) */
        createObjectT();
        this->createConnections();
        QThread::exec();
    }

protected:
    void createObjectT(){
        //qDebug() << "ObjectTArg1 creation";
        *(this->t) = new T(arg1);
    }

};


template <class T, class Arg1, class Arg2>
class ThreadObjectTArg2: public ThreadObjectTArg1<T,Arg1>
{

public:
    ThreadObjectTArg2(T **_t, Arg1 _arg1, Arg2 _arg2, SemaphoreObject *_semaphoreObject) :
      ThreadObjectTArg1<T,Arg1>(_t,_arg1,_semaphoreObject){
        arg2 = _arg2;
    }

protected:
    Arg2 arg2;

protected:
    void run(){
        this->createSemaphoreObject();          /* the semaphoreObject creation is always before the t creation, because the first
                                               thing in the event loop needs to be the releaseResourceForSemaphoreCreation (and
                                               not a possible t "delayed" slot) */
        createObjectT();
        this->createConnections();
        QThread::exec();
    }

protected:
    void createObjectT(){
        //qDebug() << "ObjectTArg2 creation";
        *(this->t) = new T(this->arg1,arg2);
    }

};


template <class T, class Arg1, class Arg2, class Arg3>
class ThreadObjectTArg3: public ThreadObjectTArg2<T,Arg1,Arg2>
{

public:
    ThreadObjectTArg3(T **_t, Arg1 _arg1, Arg2 _arg2, Arg3 _arg3, SemaphoreObject *_semaphoreObject) :
      ThreadObjectTArg2<T,Arg1,Arg2>(_t,_arg1,_arg2,_semaphoreObject){
        arg3 = _arg3;
    }

protected:
    Arg3 arg3;

protected:
    void run(){
        this->createSemaphoreObject();          /* the semaphoreObject creation is always before the t creation, because the first
                                               thing in the event loop needs to be the releaseResourceForSemaphoreCreation (and
                                               not a possible t "delayed" slot) */
        createObjectT();
        this->createConnections();
        QThread::exec();
    }

protected:
    void createObjectT(){
        //qDebug() << "ObjectTArg3 creation";
        *(this->t) = new T(this->arg1,this->arg2,arg3);
    }

};


template <class T, class Arg1, class Arg2, class Arg3, class Arg4>
class ThreadObjectTArg4: public ThreadObjectTArg3<T,Arg1,Arg2,Arg3>
{

public:
    ThreadObjectTArg4(T **_t, Arg1 _arg1, Arg2 _arg2, Arg3 _arg3, Arg4 _arg4, SemaphoreObject *_semaphoreObject) :
      ThreadObjectTArg3<T,Arg1,Arg2,Arg3>(_t,_arg1,_arg2,_arg3,_semaphoreObject){
        arg4 = _arg4;
    }

protected:
    Arg4 arg4;

protected:
    void run(){
        this->createSemaphoreObject();          /* the semaphoreObject creation is always before the t creation, because the first
                                               thing in the event loop needs to be the releaseResourceForSemaphoreCreation (and
                                               not a possible t "delayed" slot) */
        createObjectT();
        this->createConnections();
        QThread::exec();
    }

protected:
    void createObjectT(){
        //qDebug() << "ObjectTArg4 creation";
        *(this->t) = new T(this->arg1,this->arg2,this->arg3,arg4);
    }

};


template <class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
class ThreadObjectTArg5: public ThreadObjectTArg4<T,Arg1,Arg2,Arg3,Arg4>
{

public:
    ThreadObjectTArg5(T **_t, Arg1 _arg1, Arg2 _arg2, Arg3 _arg3, Arg4 _arg4, Arg5 _arg5, SemaphoreObject *_semaphoreObject) :
      ThreadObjectTArg4<T,Arg1,Arg2,Arg3,Arg4>(_t,_arg1,_arg2,_arg3,_arg4,_semaphoreObject){
        arg5 = _arg5;
    }

protected:
    Arg5 arg5;

protected:
    void run(){
        this->createSemaphoreObject();          /* the semaphoreObject creation is always before the t creation, because the first
                                               thing in the event loop needs to be the releaseResourceForSemaphoreCreation (and
                                               not a possible t "delayed" slot) */
        createObjectT();
        this->createConnections();
        QThread::exec();
    }

protected:
    void createObjectT(){
        //qDebug() << "ObjectTArg5 creation";
        *(this->t) = new T(this->arg1,this->arg2,this->arg3,this->arg4,arg5);
    }

};


template <class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
class ThreadObjectTArg6: public ThreadObjectTArg5<T,Arg1,Arg2,Arg3,Arg4,Arg5>
{

public:
    ThreadObjectTArg6(T **_t, Arg1 _arg1, Arg2 _arg2, Arg3 _arg3, Arg4 _arg4, Arg5 _arg5, Arg6 _arg6, SemaphoreObject *_semaphoreObject) :
      ThreadObjectTArg5<T,Arg1,Arg2,Arg3,Arg4,Arg5>(_t,_arg1,_arg2,_arg3,_arg4,_arg5,_semaphoreObject){
        arg6 = _arg6;
    }

protected:
    Arg6 arg6;

protected:
    void run(){
        this->createSemaphoreObject();          /* the semaphoreObject creation is always before the t creation, because the first
                                               thing in the event loop needs to be the releaseResourceForSemaphoreCreation (and
                                               not a possible t "delayed" slot) */
        createObjectT();
        this->createConnections();
        QThread::exec();
    }

protected:
    void createObjectT(){
        //qDebug() << "ObjectTArg6 creation";
        *(this->t) = new T(this->arg1,this->arg2,this->arg3,this->arg4,this->arg5,arg6);
    }

};


template <class T, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
class ThreadObjectTArg7: public ThreadObjectTArg6<T,Arg1,Arg2,Arg3,Arg4,Arg5,Arg6>
{

public:
    ThreadObjectTArg7(T **_t, Arg1 _arg1, Arg2 _arg2, Arg3 _arg3, Arg4 _arg4, Arg5 _arg5, Arg6 _arg6, Arg7 _arg7, SemaphoreObject *_semaphoreObject) :
      ThreadObjectTArg6<T,Arg1,Arg2,Arg3,Arg4,Arg5,Arg6>(_t,_arg1,_arg2,_arg3,_arg4,_arg5,_arg6,_semaphoreObject){
        arg7 = _arg7;
    }

protected:
    Arg7 arg7;

protected:
    void run(){
        this->createSemaphoreObject();          /* the semaphoreObject creation is always before the t creation, because the first
                                               thing in the event loop needs to be the releaseResourceForSemaphoreCreation (and
                                               not a possible t "delayed" slot) */
        createObjectT();
        this->createConnections();
        QThread::exec();
    }

protected:
    void createObjectT(){
        //qDebug() << "ObjectTArg7 creation";
        *(this->t) = new T(this->arg1,this->arg2,this->arg3,this->arg4,this->arg5,this->arg6,arg7);
    }

};




#endif // THREADOBJECTT_H
