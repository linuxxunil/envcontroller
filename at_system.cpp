#include "at_system.h"
#include <QFile>
//# tar -zcvf - pma|openssl des3 -salt -k password | dd of=pma.des3
//# dd if=pma.des3 |openssl des3 -d -k password|tar zxf -

QString AtSystem::_key = "http://www.ateam.com.cn";
QProcess *AtSystem::_process = new QProcess();

bool AtSystem::execReboot()
{
    return _process->startDetached("reboot");
}

bool AtSystem::execShutdown()
{
    return _process->startDetached("poweroff");
}

bool AtSystem::execAppRestart()
{
    return _process->startDetached("/opt/service restart&");
}

QStringList AtSystem::getUpgradeImages()
{
    QString cmd = "/opt/upgrade.sh";
    QStringList arg;
    arg << "list";
    _process->start(cmd, arg, QIODevice::ReadOnly );
    _process->waitForFinished();
    QString data = _process->readAllStandardOutput();
    QStringList list = data.split("\n");
    list.removeLast();
    return list;
}

QString AtSystem::getCpuTemperature()
{
    QString cmd = "cat /sys/class/thermal/thermal_zone0/temp";
    _process->start(cmd);
    _process->waitForFinished();
    QString data = _process->readAllStandardOutput();
    double temp = data.toDouble() / 1000;
    return QString::number(temp) + "'C";
}


QString AtSystem::getGpuTemperature()
{
    QString cmd = "/opt/vc/bin/vcgencmd measure_temp";
    _process->start(cmd);
    _process->waitForFinished();
    QString data = _process->readAllStandardOutput();
    data.remove("temp=").remove("\n");
    return data;
}


QString AtSystem::getOperatingVoltage()
{
    QString cmd = " /opt/vc/bin/vcgencmd measure_volts";
    _process->start(cmd);
    _process->waitForFinished();
    QString data = _process->readAllStandardOutput();
    data.remove("volt=").remove("\n");
    return data;
}


void AtSystem::execUpgrade(QString val)
{
    qDebug() << val;
    QString cmd = "/opt/upgrade.sh";
    QStringList arg;
    arg << "upgrade" << _key << val;
    _process->startDetached(cmd, arg );
}

bool AtSystem::execSetTcpRecycle()
{
    return QProcess::execute("/bin/bash", QStringList() << "-c" <<  "echo 1 > /proc/sys/net/ipv4/tcp_tw_recycle");
}

bool AtSystem::execSetTcpReuse()
{
    return QProcess::execute("/bin/bash", QStringList() << "-c" <<  "echo 1 > /proc/sys/net/ipv4/tcp_tw_reuse");
}

bool AtSystem::writeLog(QString text)
{
    QFile f("/var/log/ateam.log");
    if(!f.open(QIODevice::ReadWrite | QIODevice::Append)){
        qDebug()<<"Error opening the file";
        return false;
    }
    QTextStream outStream(&f);

    outStream << text + "\n";
    f.close();
    return true;
}

bool AtSystem::execConfigsExport()
{
//    QString cmd = "rm -rf " + setting.comConfigs.execConfigsPath + " && "
//                  "mkdir -p " + setting.comConfigs.execConfigsPath + " && "
//                  "mkdir -p /tmp/" + setting.comConfigs.execCopyDisk + " && "
//                  "umount /dev/" + setting.comConfigs.execCopyDisk + " ; "
//                  "mount /dev/" +  setting.comConfigs.execCopyDisk + " /tmp/" + setting.comConfigs.execCopyDisk + " && "
//                  "cp -a /etc/proscan*.conf " + setting.comConfigs.execConfigsPath + " && "
//                  "cd " + setting.comConfigs.execConfigsPath + " && "
//                  "tar -zcvf proscan.cfg proscan*.conf && "
//                  "cp -a " + setting.comConfigs.execConfigsPath + "/" + setting.comConfigs.appConfigName + " /tmp/" + setting.comConfigs.execCopyDisk + " && "
//                  "umount /dev/"+setting.comConfigs.execCopyDisk ;
//    qDebug() << "export : " << cmd;
//    return (QProcess::execute("/bin/bash", QStringList() << "-c" << cmd)==0)?true:false;
}

bool AtSystem::execConfigsImport()
{
//    QString cmd = "mkdir -p /tmp/" + setting.comConfigs.execCopyDisk + " && "
//                  "umount /dev/" + setting.comConfigs.execCopyDisk + " ; "
//                  "mount /dev/" + setting.comConfigs.execCopyDisk + " /tmp/" + setting.comConfigs.execCopyDisk + " && "
//                  "tar -zxvf /tmp/" + setting.comConfigs.execCopyDisk + "/" + setting.comConfigs.appConfigName + " -C /etc &&"
//                  "umount /dev/" + setting.comConfigs.execCopyDisk ;
//    qDebug() << "import : " << cmd;
//    return (QProcess::execute("/bin/bash", QStringList() << "-c" <<  cmd)==0)?true:false;
}

bool AtSystem::existsConfigsImportConfigs()
{
//    QString cmd = "mkdir -p /tmp/" + setting.comConfigs.execCopyDisk + " && "
//                  "umount /dev/" + setting.comConfigs.execCopyDisk + " ; "
//                  "mount /dev/" + setting.comConfigs.execCopyDisk + " /tmp/" + setting.comConfigs.execCopyDisk + " && "
//                  "ls /tmp/" + setting.comConfigs.execCopyDisk + " | grep ^/tmp/" + setting.comConfigs.execCopyDisk + "/" + setting.comConfigs.appConfigName + "$ && "
//                  "result=$? &&"
//                  "umount /dev/" + setting.comConfigs.execCopyDisk + "&&"
//                  "test $result -eq 0 && exit 0 || exit 1";
//    return (QProcess::execute("/bin/bash", QStringList() << "-c" <<  cmd)==0)?true:false;
}

bool AtSystem::existsConfigsExportDisk()
{
//    QString cmd = "mkdir -p /tmp/" + setting.comConfigs.execCopyDisk + " && "
//                  "umount /dev/" + setting.comConfigs.execCopyDisk + " ; "
//                  "mount /dev/" + setting.comConfigs.execCopyDisk + " /tmp/" + setting.comConfigs.execCopyDisk + " && "
//                  "result=$? &&"
//                  "umount /dev/" + setting.comConfigs.execCopyDisk + "&&"
//                  "test $result -eq 0 && exit 0 || exit 1";
//    return (QProcess::execute("/bin/bash", QStringList() << "-c" <<  cmd)==0)?true:false;
}

bool AtSystem::execResetDefault()
{
//    QString cmd;
//    for (int i=0 ;i<setting.comConfigs.size; i++) {
//        cmd += "cp " + setting.comConfigs.appDefaultConfigPath + " " + setting.comConfigs.appConfigPath[i] + ";";
//    }
//    cmd += "sed -i 's/^appConfigIndex=[0-9]/appConfigIndex=0/g' " + setting.commonPath;
//    return (QProcess::execute("/bin/bash", QStringList() << "-c" <<  cmd)==0)?true:false;
}

bool AtSystem::setSystemDate(QString date) // 20171201
{
    QString cmd; //date -s "20170204 `date +'%T'`"
    cmd += "date -s \"" + date + " `date +'%T'`\"";
    return (QProcess::execute("/bin/bash", QStringList() << "-c" <<  cmd)==0)?true:false;
}

bool AtSystem::setSystemTime(QString time) // 12:00:00
{
    QString cmd;
    cmd += "date -s " + time;
    return (QProcess::execute("/bin/bash", QStringList() << "-c" <<  cmd)==0)?true:false;
}

bool AtSystem::setSystemDateTime(QString val)
{
    QStringList dateTime = val.split(" ");
    if ( dateTime.size() == 2 ) {
        QString cmd; //date -s "20170204 `date +'%T'`"
        cmd += "date -s \"" + dateTime[0] + " `date +'%T'`\" > /dev/null";
        cmd += ";";
        cmd += "date -s " + dateTime[1] + " > /dev/null";
        return (QProcess::execute("/bin/bash", QStringList() << "-c" <<  cmd)==0)?true:false;
    }
    return false;
}

bool AtSystem::execStartNtp()
{
    QString cmd = "systemctl enable ntp > /dev/null; /etc/init.d/ntp start > /dev/null";
    return (QProcess::execute("/bin/bash", QStringList() << "-c" <<  cmd)==0)?true:false;
}

bool AtSystem::execStopNtp()
{
    QString cmd = "systemctl disable ntp > /dev/null ; /etc/init.d/ntp stop > /dev/null";
    return (QProcess::execute("/bin/bash", QStringList() << "-c" <<  cmd)==0)?true:false;
}



bool AtSystem::setNtpServer(QString val) //
{
    QString cmd;
    cmd = "NTPSERVER=`grep \"^server\" /etc/ntp.conf -m 1` && "
          "sed -i \"s/^${NTPSERVER}/server " + val + "/g\" /etc/ntp.conf;"
          "systemctl restart ntp";

    return (QProcess::execute("/bin/bash", QStringList() << "-c" <<  cmd)==0)?true:false;
}

