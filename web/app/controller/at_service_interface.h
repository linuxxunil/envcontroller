#ifndef AT_SERVICE_INTERFACE_H
#define AT_SERVICE_INTERFACE_H


#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"
#include "../at_web_thread.h"


using namespace stefanfrings;

class AtServiceInterface : public  HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(AtServiceInterface)
public:
    AtWebThread *app = AtWebThread::getInstance();

    /** Constructor */
    AtServiceInterface(){}
    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};


#endif // AT_SERVICE_INTERFACE_H
