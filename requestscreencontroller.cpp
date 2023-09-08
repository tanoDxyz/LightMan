#include "requestscreencontroller.h"
#include "Constants.h"
RequestScreenController::RequestScreenController(QObject *parent) :
    QObject(parent)
{
}
void RequestScreenController::setResponseCallback(const std::function<void(HttpResponse)> callback) {
    this->callback = callback;
}
RequestScreenController::~RequestScreenController() {
    delete req;
    qDebug() <<" REQUEST SCREEN CONTROLLER DELETED";

}

void RequestScreenController::cancelRequest() {
    req->cancelRequest();
}
void RequestScreenController::start() {
    connect(req,&HttpRequest::requestFinished,this,[&](bool error,int responseCode,
            const QString& errorString,
            const QByteArray& response, const QList<QPair<QByteArray,QByteArray>>& responseHeaders, const QList<QNetworkCookie>& cookies)->void{
        HttpResponse httpResponse{error,responseCode,errorString,response,responseHeaders,cookies};
        callback(httpResponse);
    });
    req->start();
}

void RequestScreenController::newRequest(QUrl *url, QString *requestMethod,
                                         QMap<QString, QString> *headers, QByteArray *body){
    newRequest(url,requestMethod,headers,body,nullptr);
}


void RequestScreenController::newRequest(QUrl *url, QString *requestMethod,
                                         QMap<QString, QString> *headers, QUrlQuery *urlQuery) {
    newRequest(url,requestMethod,headers,nullptr,urlQuery);

}


void RequestScreenController::newRequest( QUrl *url,
                                          QString *requestMethod,
                                          QMap<QString, QString> *headers,
                                          QByteArray *body, QUrlQuery *urlQuery) {

    if(req) {
        delete req;
    }
    req = new HttpRequest(this);
    req->newRequest(url,requestMethod,headers,body,urlQuery);

}

void RequestScreenController::newRequest(QUrl* url) {
    newRequest(url,new QString{Constants::HttpMethods::GET},nullptr,nullptr,nullptr);
}

