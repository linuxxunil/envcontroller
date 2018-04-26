#ifndef AT_WEB_THREAD_H
#define AT_WEB_THREAD_H
#include <QThread>
#include <QObject>
#include "at_controller.h"
#include "at_http_routing.h"
#include "httplistener.h"
#include "httpsessionstore.h"
#include "staticfilecontroller.h"

using namespace stefanfrings;

class AtWebThread : public AtController
{

private :
    AtWebThread(){}
    ~AtWebThread(){}
    static AtWebThread *_instance;
    static QThread *_thread;
    const AtWebThread& operator=(const AtWebThread&);

public:
    HttpListener *httpListener;
    HttpSessionStore *httpSessionStore;
    StaticFileController* staticFileController;

    static AtWebThread *getInstance() {
        if ( !_instance ) {
           _instance = new AtWebThread();
           _thread = new QThread();
           _instance->init();
        }
        return _instance;
    }

    void init();
    void start();
    void stop();
};

#endif // AT_WEB_THREAD_H
