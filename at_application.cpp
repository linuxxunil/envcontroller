#include "at_application.h"

AtApplication::AtApplication(int argc, char *argv[])
{
    _app = new QGuiApplication(argc, argv);
    _engine = new QQmlApplicationEngine();
    root = this;

    //if ( AtLicense::checkDeviceLicense() ) {
        // Initial Work Thread
        workThread = AtWorkThread::getInstance();
        //workThread->setGuiSignal(guiSignal);
        workThread->start();
        //_engine->rootContext()->setContextProperty("qmlSettings", qmlSettings);
        _engine->load(QUrl(QStringLiteral("qrc:/view/index.qml")));

        // Initial Web Thread
        webThread = AtWebThread::getInstance();
        webThread->start();
    //} else {
    //}
}

QGuiApplication* AtApplication::getQGuiApplication()
{
    return _app;
}

bool AtApplication::isGuiRunning()
{
    return (_app->applicationState() == Qt::ApplicationActive)?true:false;
}

int AtApplication::exec()
{
    return _app->exec();
}
