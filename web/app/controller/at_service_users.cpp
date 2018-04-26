
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include "httpsession.h"
#include "at_service_users.h"
#include "../at_response_code.h"

void AtServiceUsers::service(HttpRequest& request, HttpResponse& response)
{
    QString path = request.getPath();
    QString method = request.getMethod().toUpper();
    QString parameter = request.getParameter("params");
    qDebug() << request.getBody();
    QString msg = AtResponseCode::MSG_UNSUPPORT_RESOURCE;


    if ( path == "/users/login" ) {
        if ( method == "POST" ) {
            response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");
            QJsonObject params = QJsonDocument::fromJson(parameter.toUtf8()).object();
            QString username = params["username"].toString();
            QString password = params["password"].toString();
            if ( login(username, password) ) {

                HttpSession session =
                        app->httpSessionStore->getSession(request,response);

                if (!session.contains("startTime")) {
                    session.set("startTime",QDateTime::currentDateTime());
                    session.set("username",username);
                }

                msg = AtResponseCode::MSG_OK;
            } else {
                msg = AtResponseCode::MSG_USER_LOGIN_ERR;
            }
        }
    } else if ( path == "/users/logout" ) {

        if ( method == "POST" ) {
            HttpSession session =
                    app->httpSessionStore->getSession(request,response, false);
            app->httpSessionStore->removeSession(session);
            msg = AtResponseCode::MSG_OK;
        }
    }

    response.write(msg.toLatin1());
}

bool AtServiceUsers::login(QString username, QString password)
{
    int size = app->settings.webUsers.size;

    for (int i=0; i<size; i++) {
        if ( app->settings.webUsers.username[i] == username &&
             app->settings.webUsers.password[i] == password ) {
            return true;
        }
    }
    return false;
}

