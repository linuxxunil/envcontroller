#include <QGuiApplication>
#include <QSettings>
#include "at_web_thread.h"
#include "at_application.h"

using namespace stefanfrings;


AtWebThread *AtWebThread::_instance = 0;
QThread *AtWebThread::_thread = 0;

void AtWebThread::init()
{
    QGuiApplication *app
            = ((AtApplication*)root)->getQGuiApplication();

    // Initial SesstionStore
    QSettings* sessionSettings=new QSettings(settings.path,QSettings::IniFormat,app);
    sessionSettings->beginGroup(settings.webSessions.getGroupName());
    httpSessionStore = new HttpSessionStore(sessionSettings,app);

    // Initial StaticFile
    QSettings* staticFileSettings=new QSettings(settings.path,QSettings::IniFormat,app);
    staticFileSettings->beginGroup(settings.webDocRoot.getGroupName());
    staticFileController = new StaticFileController(staticFileSettings,app);

    // Initial Web Server
    QSettings* webServerSettings=new QSettings(settings.path,QSettings::IniFormat,app);
    webServerSettings->beginGroup(settings.webServer.getGroupName());
    httpListener = new HttpListener(webServerSettings,
                                    new AtHttpRouting(app),app);
}


void AtWebThread::start()
{
    _instance->moveToThread(_thread);
    QObject::connect(_thread, &QThread::finished, _instance, &QObject::deleteLater);
    _thread->start();
 }

void AtWebThread::stop()
{
    _thread->quit();
    _thread->wait();
}
