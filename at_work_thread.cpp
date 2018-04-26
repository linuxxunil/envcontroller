#include "at_work_thread.h"

AtWorkThread *AtWorkThread::_instance = 0;
QThread *AtWorkThread::_thread = 0;

void AtWorkThread::init()
{

}

void AtWorkThread::start()
{
    _instance->moveToThread(_thread);
    QObject::connect(_thread, &QThread::finished, _instance, &QObject::deleteLater);
    _thread->start();
 }

void AtWorkThread::stop()
{
    _thread->quit();
    _thread->wait();
}
