#ifndef AT_SERVICE_USERS_H
#define AT_SERVICE_USERS_H


#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"
#include "../at_web_thread.h"


using namespace stefanfrings;

class AtServiceUsers : public  HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(AtServiceUsers)
public:
    AtWebThread *app = AtWebThread::getInstance();

    /** Constructor */
    AtServiceUsers(){}
    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
    bool login(QString username, QString password);
};


#endif // AT_SERVICE_USERS_H
