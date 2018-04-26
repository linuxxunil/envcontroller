
#include <QDebug>
#include <QException>
#include "at_application.h"

int main(int argc, char *argv[])
{
    int status ;
    try {
        AtApplication app(argc, argv);

        status = app.exec();
    } catch ( QException e ) {
        qDebug() << "Status : " << QString::number(status,10) ;//<< ", ErrorMsg : " << e.err;
    }
    return status;
}
