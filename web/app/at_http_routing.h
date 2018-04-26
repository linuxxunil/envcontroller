/**
  @file
  @author Stefan Frings
*/

#ifndef AT_HTTP_ROUTING_H
#define AT_HTTP_ROUTING_H

#include "httprequesthandler.h"
#include "at_web_thread.h"
using namespace stefanfrings;


class AtHttpRouting : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(AtHttpRouting)
public:
    /**
      Constructor.
      @param parent Parent object
    */
    AtHttpRouting(QObject* parent=0);

    /**
      Destructor.
    */
    ~AtHttpRouting();

    /**
      Dispatch incoming HTTP requests to different controllers depending on the URL.
      @param request The received HTTP request
      @param response Must be used to return the response
    */
    void service(HttpRequest& request, HttpResponse& response);
    bool isLogin(HttpRequest& request, HttpResponse& response);
    void redirect(HttpRequest& request, HttpResponse& response);
    void redirectRootIndex(HttpResponse& response);

};

#endif // AT_HTTP_ROUTING_H
