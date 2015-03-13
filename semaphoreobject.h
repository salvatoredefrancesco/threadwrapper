/*

    This class is a wrapper for the semaphores used to create and delete the object of the QObject
    derived class T inside the QThread.
    To better understand the meaning, refer to the code of the "ThreadWrapper" and "ThreadObject" classes.

*/


#ifndef SEMAPHOREOBJECT_H
#define SEMAPHOREOBJECT_H

#include <QObject>
#include <QSemaphore>
#include <QThread>
#include <QDebug>

class SemaphoreObject : public QObject
{
    Q_OBJECT
public:
    explicit SemaphoreObject(QObject *parent = 0);
    explicit SemaphoreObject(QSemaphore *_semaphoreCreation, QSemaphore *_semaphoreDeletion, QObject *parent = 0);
    ~SemaphoreObject(){
        if(mainConstructor){
            delete semaphoreCreation;
            delete semaphoreDeletion;
        }
    }

public:
    bool mainConstructor;
    QSemaphore *semaphoreCreation;
    QSemaphore *semaphoreDeletion;

signals:

public slots:
    void acquireResourceForSemaphoreCreation();
    void acquireResourceForSemaphoreDeletion();
    void releaseResourceForSemaphoreCreation();
    void releaseResourceForSemaphoreDeletion();

};

#endif // SEMAPHOREOBJECT_H
