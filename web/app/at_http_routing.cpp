/**
  @file
  @author Stefan Frings
*/

#include "at_http_routing.h"
#include "at_response_code.h"
#include "controller/at_dumpcontroller.h"
#include "controller/at_service_users.h"
#include "controller/at_service_interface.h"
#include "controller/at_service_system.h"
#include "at_web_thread.h"


AtHttpRouting::AtHttpRouting(QObject* parent)
    :HttpRequestHandler(parent)
{
    qDebug("AtRequestRouting: created");
}


AtHttpRouting::~AtHttpRouting()
{
    qDebug("AtRequestRouting: deleted");
}



void AtHttpRouting::service(HttpRequest& request, HttpResponse& response)
{
    QByteArray path=request.getPath();
    qDebug("RequestRouting: path=%s",path.data());
    QString msg = AtResponseCode::MSG_UNKOWN_ERR;
    QByteArray sessionId = request.getCookie("sessionid");

    if (path.startsWith("/users")){
        AtServiceUsers().service(request, response);
    } else if (path.startsWith("/assets")) {
        redirect(request,response);
    } else if (isLogin(request, response)){
        qDebug() << "DDDDD";
        if ( path == "/" ) {
           redirect("/dashboard.html",response);
        } else if ( path.startsWith("/system") ) {
            AtServiceSystem().service(request, response);
        } else if ( path.startsWith("/interface") ) {
            AtServiceInterface().service(request, response);
        } else if ( path.endsWith(".html")) {
            redirect(request,response);
        } else {
            msg = AtResponseCode::MSG_UNSUPPORT_RESOURCE;
            response.write(msg.toLatin1(),true);
        }
    } else {
        redirectRootIndex(response); //redirect index.html
    }


//    else if (path.startsWith("/template"))
//    {
//        TemplateController().service(request, response);
//    }

//    else if (path.startsWith("/form"))
//    {
//        FormController().service(request, response);
//    }

//    else if (path.startsWith("/file"))
//    {
//        FileUploadController().service(request, response);
//    }

//    else if (path.startsWith("/session"))
//    {
//        SessionController().service(request, response);
//    }

//    // All other pathes are mapped to the static file controller.
//    // In this case, a single instance is used for multiple requests.
//    else
//    {
//      //  staticFileController->service(request, response);
//    }

//    qDebug("RequestMapper: finished request");

    // Clear the log buffer
//    if (logger)
//    {
//       logger->clear();
//    }
}

bool AtHttpRouting::isLogin(HttpRequest& request, HttpResponse& response)
{
    qDebug() << request.getCookie("sessionid");
    AtWebThread *app = AtWebThread::getInstance();
    HttpSession session =
            app->httpSessionStore->getSession(request, response, false);
    return !session.isNull();
}


void AtHttpRouting::redirect(HttpRequest &request, HttpResponse &response)
{
    AtWebThread *app = AtWebThread::getInstance();
    app->staticFileController->service(request, response);
}

void AtHttpRouting::redirect(QString path, HttpResponse &response)
{
    AtWebThread *app = AtWebThread::getInstance();
    app->staticFileController->service(path.toLatin1(), response);
}

void AtHttpRouting::redirectRootIndex(HttpResponse &response)
{
    AtWebThread *app = AtWebThread::getInstance();
    QByteArray index = app->settings.webDocRoot.indexHtml.toLatin1();
    app->staticFileController->service(index, response);
}

