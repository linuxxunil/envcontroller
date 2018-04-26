#ifndef AT_SETTINGS_H
#define AT_SETTINGS_H
#include <QSettings>
#include <QString>
#include <QObject>
#include <QMutex>


class AtSettingsBase : public QObject{

protected:
     QSettings *_settings;
     static QMutex *_mutex;
     QString _group;

public:
     void setSettings(QSettings *settings) {
         _settings = settings;
     }

     void beginGroup() {
         _settings->beginGroup(_group);
     }
     void endGroup() {
         _settings->endGroup();
     }
     QSettings *getSettings() {
         return _settings;
     }
     QString getGroupName() {
         return _group;
     }
};

class AtWebServer : public AtSettingsBase{
public:
    int port;
    int minThread;
    int maxThread;
    int readTimeout;
    QString sslKeyFile;
    QString sslCertFile;
    int maxRequestSize;
    int maxMultiPartSize;


    void init() {
        this->_group = "WebServer";
    }

    void reload() {
        _mutex->lock();
        _settings->beginGroup(_group);
        port = _settings->value("port",QVariant("8080")).toInt();
        minThread = _settings->value("minThread",QVariant("4")).toInt();
        maxThread = _settings->value("maxThread",QVariant("100")).toInt();
        maxThread = _settings->value("readTimeout",QVariant("60000")).toInt();
        maxRequestSize = _settings->value("maxRequestSize",QVariant("16000")).toInt();
        maxMultiPartSize = _settings->value("maxMultiPartSize",QVariant("10000000")).toInt();

        sslKeyFile = _settings->value("sslKeyFile",QVariant("/etc/ssl/my.key")).toString();
        sslCertFile = _settings->value("sslCertFile",QVariant("/etc/ssl/my.cert")).toString();
        _settings->endGroup();
        _mutex->unlock();
    }

    void sync() {
        _mutex->lock();
        _settings->beginGroup(_group);
        _settings->setValue("port", QVariant(port));
        _settings->setValue("minThread", QVariant(minThread));
        _settings->setValue("maxThread", QVariant(maxThread));
        _settings->setValue("maxRequestSize", QVariant(maxRequestSize));
        _settings->setValue("maxMultiPartSize", QVariant(maxMultiPartSize));
        _settings->setValue("sslKeyFile", QVariant(sslKeyFile));
        _settings->setValue("sslCertFile", QVariant(sslCertFile));

        _settings->endGroup();
        _mutex->unlock();
    }
};

class AtWebSessions: public AtSettingsBase{
public:
    int expirationTime;
    QString cookieName;
    QString cookiePath;
    QString cookieComment;
    QString cookieDomain;



    void init() {
        this->_group = "WebSessions";
    }

    void reload() {
        _mutex->lock();
        _settings->beginGroup(_group);
        expirationTime = _settings->value("expirationTime",QVariant("3600000")).toInt();

        cookieName = _settings->value("cookieName",QVariant("sessionid")).toString();
        cookiePath = _settings->value("cookiePath",QVariant("/")).toString();
        cookieComment = _settings->value("cookieComment",QVariant("Identifies the user")).toString();
        cookieDomain = _settings->value("cookieDomain",QVariant("")).toString();

        _settings->endGroup();
        _mutex->unlock();
    }

    void sync() {
        _mutex->lock();
        _settings->beginGroup(_group);
        _settings->setValue("expirationTime", QVariant(expirationTime));
        _settings->setValue("cookieName", QVariant(cookieName));
        _settings->setValue("cookiePath", QVariant(cookiePath));
        _settings->setValue("cookieComment", QVariant(cookieComment));
        _settings->setValue("cookieDomain", QVariant(cookieDomain));

        _settings->endGroup();
        _mutex->unlock();
    }
};

class AtWebUsers: public AtSettingsBase{
public:
    int size = 2;
    QString *username;
    QString *password;


    void init() {
        this->_group = "WebUsers";

        username = new QString[size];
        password = new QString[size];
    }

    void reload() {
        _mutex->lock();
        _settings->beginGroup(_group);
        username[0] = _settings->value("username0",QVariant("admin")).toString();
        password[0] = _settings->value("password0",QVariant("admin")).toString();
        username[1] = _settings->value("username1",QVariant("guest")).toString();
        password[1] = _settings->value("password1",QVariant("guest")).toString();
        _settings->endGroup();
        _mutex->unlock();
    }

    void sync() {
        _mutex->lock();
        _settings->beginGroup(_group);
        _settings->setValue("username0", QVariant(username[0]));
        _settings->setValue("password0", QVariant(password[0]));
        _settings->setValue("username1", QVariant(username[1]));
        _settings->setValue("password1", QVariant(password[1]));

        _settings->endGroup();
        _mutex->unlock();
    }
};

class AtWebDocRoot: public AtSettingsBase{
public:
    QString path;
    QString encoding;
    int maxAge;
    int cacheTime;
    int cacheSize;
    int maxCachedFileSize;
    QString indexHtml;
    void init() {
        this->_group = "WebDocRoot";
    }

    void reload() {
        _mutex->lock();
        _settings->beginGroup(_group);
        path = _settings->value("path",QVariant("/var/www")).toString();
        encoding = _settings->value("encoding",QVariant("UTF-8")).toString();
        maxAge = _settings->value("maxAge",QVariant("60000")).toInt();
        cacheTime = _settings->value("cacheTime",QVariant("60000")).toInt();
        cacheSize = _settings->value("cacheSize",QVariant("1000000")).toInt();
        maxCachedFileSize = _settings->value("maxCachedFileSize",QVariant("65536")).toInt();
        indexHtml = _settings->value("indexHtml",QVariant("/index.html")).toString();
        _settings->endGroup();
        _mutex->unlock();
    }

    void sync() {
        _mutex->lock();
        _settings->beginGroup(_group);
        _settings->setValue("path", QVariant(path));
        _settings->setValue("encoding", QVariant(encoding));
        _settings->setValue("maxAge", QVariant(maxAge));
        _settings->setValue("cacheTime", QVariant(cacheTime));
        _settings->setValue("cacheSize", QVariant(cacheSize));
        _settings->setValue("maxCachedFileSize", QVariant(maxCachedFileSize));
        _settings->setValue("indexHtml", QVariant(indexHtml));

        _settings->endGroup();
        _mutex->unlock();
    }
};

class AtSettings {
private:

    QSettings *_settings;
public :
    const QString path = "/etc/ateam.conf";

    AtSettings(QObject *parent) {
        _settings = new QSettings(path, QSettings::IniFormat);

        webServer.setSettings(_settings);
        webServer.init();
        webServer.reload();
        webServer.sync();

        webSessions.setSettings(_settings);
        webSessions.init();
        webSessions.reload();
        webSessions.sync();

        webUsers.setSettings(_settings);
        webUsers.init();
        webUsers.reload();
        webUsers.sync();

        webDocRoot.setSettings(_settings);
        webDocRoot.init();
        webDocRoot.reload();
        webDocRoot.sync();
    }

    AtWebServer webServer;
    AtWebSessions webSessions;
    AtWebUsers webUsers;
    AtWebDocRoot webDocRoot;
};


#endif // AT_SETTING_H
