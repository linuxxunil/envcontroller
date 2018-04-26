#ifndef AT_WORK_THREAD_H
#define AT_WORK_THREAD_H
#include<QThread>
#include "at_controller.h"

class AtWorkThread : public AtController
{
private:
    AtWorkThread(){}
    ~AtWorkThread(){}
    static AtWorkThread *_instance;
    static QThread *_thread;
    const AtWorkThread& operator=(const AtWorkThread&);

public:
    static AtWorkThread *getInstance() {
       if ( !_instance ) {
           _instance = new AtWorkThread();
           _thread = new QThread();
           _instance->init();
       }
       return _instance;
    }

    void init();
    void start();
    void stop();
};

#endif // AT_WORK_THREAD_H
