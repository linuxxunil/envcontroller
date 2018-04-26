#ifndef AT_APPLICATION_H
#define AT_APPLICATION_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "at_work_thread.h"
#include "at_controller.h"
#include "web/app/at_web_thread.h"

class AtApplication : public AtController
{
private :
    QGuiApplication *_app;
    QQmlApplicationEngine *_engine;

public:
    AtApplication(int argc, char *argv[]);
    AtWorkThread *workThread;
    AtWebThread *webThread;

    bool isGuiRunning();
    QGuiApplication *getQGuiApplication();
    int exec() ;
};

#endif // AT_APPLICATION_H
