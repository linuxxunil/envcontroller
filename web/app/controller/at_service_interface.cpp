#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include "httpsession.h"
#include "at_service_interface.h"
#include "../at_response_code.h"

void AtServiceInterface::service(HttpRequest& request, HttpResponse& response)
{
    QString path = request.getPath();
    QString method = request.getMethod().toUpper();
    QString parameter = request.getParameter("params");
    QString msg = AtResponseCode::MSG_UNSUPPORT_RESOURCE;

    if ( path == "/interface/di" ) {
        if ( method == "POST" ) {

        }
    } else if ( path == "/interface/shutdown" ) {

        if ( method == "POST" ) {

        }
    }

    response.write(msg.toLatin1(),true);
}


