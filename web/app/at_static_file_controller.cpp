#include "at_static_file_controller.h"
#include <QDateTime>

AtStaticFileController::AtStaticFileController(QSettings* settings, QObject* parent)
    :StaticFileController(settings, parent)
{

}

void AtStaticFileController::service(HttpRequest& request, HttpResponse& response)
{
    this->service(request.getPath(), response);
}

void AtStaticFileController::service(QByteArray path, HttpResponse& response)
{
    // Check if we have the file in cache
    qint64 now=QDateTime::currentMSecsSinceEpoch();
    mutex.lock();
    CacheEntry* entry=cache.object(path);
    if (entry && (cacheTimeout==0 || entry->created>now-cacheTimeout))
    {
        QByteArray document=entry->document; //copy the cached document, because other threads may destroy the cached entry immediately after mutex unlock.
        QByteArray filename=entry->filename;
        mutex.unlock();
        qDebug("StaticFileController: Cache hit for %s",path.data());
        setContentType(filename,response);
        response.setHeader("Cache-Control","max-age="+QByteArray::number(maxAge/1000));
        response.write(document);
    }
    else
    {
        mutex.unlock();
        // The file is not in cache.
        qDebug("StaticFileController: Cache miss for %s",path.data());
        // Forbid access to files outside the docroot directory
        if (path.contains("/.."))
        {
            qWarning("StaticFileController: detected forbidden characters in path %s",path.data());
            response.setStatus(403,"forbidden");
            response.write("403 forbidden",true);
            return;
        }
        // If the filename is a directory, append index.html.
        if (QFileInfo(docroot+path).isDir())
        {
            path+="/index.html";
        }
        // Try to open the file
        QFile file(docroot+path);
        qDebug("StaticFileController: Open file %s",qPrintable(file.fileName()));
        if (file.open(QIODevice::ReadOnly))
        {
            setContentType(path,response);
            response.setHeader("Cache-Control","max-age="+QByteArray::number(maxAge/1000));
            if (file.size()<=maxCachedFileSize)
            {
                // Return the file content and store it also in the cache
                entry=new CacheEntry();
                while (!file.atEnd() && !file.error())
                {
                    QByteArray buffer=file.read(65536);
                    response.write(buffer);
                    entry->document.append(buffer);
                }
                entry->created=now;
                entry->filename=path;
                mutex.lock();
                cache.insert(path, entry,entry->document.size());
                mutex.unlock();
            }
            else
            {
                // Return the file content, do not store in cache
                while (!file.atEnd() && !file.error())
                {
                    response.write(file.read(65536));
                }
            }
            file.close();
        }
        else {
            if (file.exists())
            {
                qWarning("StaticFileController: Cannot open existing file %s for reading",qPrintable(file.fileName()));
                response.setStatus(403,"forbidden");
                response.write("403 forbidden",true);
            }
            else
            {
                response.setStatus(404,"not found");
                response.write("404 not found",true);
            }
        }
    }
}
