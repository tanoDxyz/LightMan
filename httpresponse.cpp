#include "httpresponse.h"

HttpResponse::HttpResponse(bool error,
                           int responseCode,
                           const QString& errorString,
                           const QByteArray& response,
                           const QList<QPair<QByteArray,QByteArray>>& responseHeaders,
                           const QList<QNetworkCookie>& cookies):error{error},errorString{errorString},response{response},
    responseHeaders{responseHeaders},cookies{cookies},responseCode{responseCode}
{

}
