#ifndef REQUESTSCREENCONTROLLER_H
#define REQUESTSCREENCONTROLLER_H

#include <QObject>
#include <QUrlQuery>
#include "httprequest.h"
#include "httpresponse.h"
class RequestScreenController : public QObject
{
    Q_OBJECT
public:

    explicit RequestScreenController(QObject *parent = nullptr);
    void newRequest(QUrl *url,QString *requestMethod,
                    QMap<QString,QString> *headers, QUrlQuery *urlQuery);

    void newRequest( QUrl *url, QString *requestMethod,
                     QMap<QString,QString> *headers, QByteArray* body);

    void newRequest( QUrl *url, QString *requestMethod,
                     QMap<QString,QString> *headers, QByteArray* body, QUrlQuery *urlQuery);

    void newRequest(QUrl *url);
    void start();
    void cancelRequest();
    void setResponseCallback(const std::function<void(HttpResponse)> callback);
    ~RequestScreenController();

private:
    std::function<void(HttpResponse)> callback;
    HttpRequest *req = nullptr;

};

#endif // REQUESTSCREENCONTROLLER_H
