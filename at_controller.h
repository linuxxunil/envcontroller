#ifndef AT_CONTROLLER_H
#define AT_CONTROLLER_H

#include <QObject>
#include "at_settings.h"
#include "at_logger.h"

class AtController : public QObject {
private :

protected :

    static QObject *root;
    static AtLogger logger;
    static bool init;

public :
    static AtSettings settings;

    AtController();
    ~AtController();
};

#endif // AT_CONTROLLER_H
