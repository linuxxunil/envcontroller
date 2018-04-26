#ifndef AT_SYSTEM_H
#define AT_SYSTEM_H

#include "at_controller.h"
#include <QProcess>
#include <QHash>

class AtSystem : public AtController
{
    Q_OBJECT

private :
    AtSystem(){}
    ~AtSystem(){}
    static QProcess *_process;
    static QString _key;//"http://www.ateam.com.cn";

public:
    static QStringList getUpgradeImages();
    static QString getCpuTemperature();
    static QString getGpuTemperature();
    static QString getOperatingVoltage();
    static void execUpgrade(QString val);
    static bool execReboot();
    static bool execShutdown();
    static bool execAppRestart();
    static bool execSetTcpRecycle();
    static bool execSetTcpReuse();
    static bool writeLog(QString text);
    static bool execConfigsExport();
    static bool execConfigsImport();
    static bool existsConfigsImportConfigs();
    static bool existsConfigsExportDisk();
    static bool execResetDefault();
    static bool setSystemDate(QString val);
    static bool setSystemTime(QString val);
    static bool setSystemDateTime(QString val);
    static bool execStartNtp();
    static bool execStopNtp();
    static bool setNtpServer(QString val);

};

#endif // AT_SYSTEM_H
