#include "semaphoreobject.h"

SemaphoreObject::SemaphoreObject(QObject *parent) :
    QObject(parent)
{

    mainConstructor = true;
    semaphoreCreation = new QSemaphore();
    semaphoreDeletion = new QSemaphore();

}



SemaphoreObject::SemaphoreObject(QSemaphore *_semaphoreCreation, QSemaphore *_semaphoreDeletion, QObject *parent) :
    QObject(parent)
{

    mainConstructor = false;
    semaphoreCreation = _semaphoreCreation;
    semaphoreDeletion = _semaphoreDeletion;

}


void SemaphoreObject::acquireResourceForSemaphoreCreation(){

    semaphoreCreation->acquire(1);
    //qDebug() << QThread::currentThreadId() << "Resource for semaphoreCreation acquired";

}


void SemaphoreObject::acquireResourceForSemaphoreDeletion(){

    semaphoreDeletion->acquire(1);
    //qDebug() << QThread::currentThreadId() << "Resource for semaphoreDeletion acquired";

}


void SemaphoreObject::releaseResourceForSemaphoreCreation(){

    semaphoreCreation->release(1);
    //qDebug() << QThread::currentThreadId() << "Resource for semaphoreCreation released";

}


void SemaphoreObject::releaseResourceForSemaphoreDeletion(){

    semaphoreDeletion->release(1);
    //qDebug() << QThread::currentThreadId() << "Resource for semaphoreDeletion released";

}
