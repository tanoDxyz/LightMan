#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QByteArray>
#include <QNetworkCookie>
#include <QPair>



class HttpResponse
{
public:
    HttpResponse(bool error,
                 int responseCode,
                 const QString& errorString,
                 const QByteArray& response,
                 const QList<QPair<QByteArray,QByteArray>>& responseHeaders,
                 const QList<QNetworkCookie>& cookies);
    bool error;
    const QString& errorString;
    const QByteArray& response;
    const QList<QPair<QByteArray,QByteArray>>& responseHeaders;
    const QList<QNetworkCookie>& cookies;
    int responseCode = 0;


};

#endif // HTTPRESPONSE_H
