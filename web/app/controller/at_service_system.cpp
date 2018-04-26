#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include "httpsession.h"
#include "at_service_system.h"
#include "../at_response_code.h"
#include "at_system.h"


void AtServiceSystem::service(HttpRequest& request, HttpResponse& response)
{
    QString path = request.getPath();
    QString method = request.getMethod().toUpper();
    QString parameter = request.getParameter("params");
    QString msg = AtResponseCode::MSG_UNSUPPORT_RESOURCE;

    if ( path == "/system/reboot" ) {
        if ( method == "POST" ) {
            //AtSystem::execReboot();
        }
    } else if ( path == "/system/shutdown" ) {

        if ( method == "POST" ) {
            //AtSystem::execShutdown();
        }
    } else if ( path == "" ) {

    }

    response.write(msg.toLatin1(),true);
}


