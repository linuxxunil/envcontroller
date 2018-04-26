#ifndef AT_LOGGER_H
#define AT_LOGGER_H

#include <QDebug>

class AtLogger : public QDebug
{
public:
    AtLogger();
};

#endif // AT_LOGGER_H
