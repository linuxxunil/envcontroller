#ifndef AT_SERVICE_SYSTEM_H
#define AT_SERVICE_SYSTEM_H


#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"
#include "../at_web_thread.h"


using namespace stefanfrings;

class AtServiceSystem : public  HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(AtServiceSystem)
public:
    AtWebThread *app = AtWebThread::getInstance();

    /** Constructor */
    AtServiceSystem(){}
    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};


#endif // AT_SERVICE_SYSTEM_H
