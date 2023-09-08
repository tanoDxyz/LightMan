#include "httprequest.h"
#include <QDebug>
#include <Constants.h>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkSession>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkCookie>
HttpRequest::HttpRequest(QObject *parent) : QThread(parent)
{
}

void HttpRequest::cancelRequest() {
    qDebug() <<" HttpRequest cancelRequest";
    if(reply && reply->isRunning()) {
        qDebug() <<" HttpRequest request running -> canceling";
        reply->abort();
        qDebug() <<" HttpRequest request cancel called off";
    }
}

void HttpRequest::run() {
    auto networkAccessManager {QNetworkAccessManager{}};
    auto responseHeaders {QList<QPair<QByteArray, QByteArray>>()};
    auto cookies {QList<QNetworkCookie>()};
    int responseCode = 0;
    try {
        qDebug() <<"Running Thread "<<QThread::currentThread()<<endl<<" url "<<url <<" Request method "<<requestMethod;

        if(urlQueryParams) {
            url->setQuery(*urlQueryParams);
        }


        QNetworkRequest request(*url);

        if(headers) {
            for (QMap<QString, QString>::iterator it = headers->begin(); it != headers->end(); ++it) {
                QString key = it.key();
                QString value = it.value();
                request.setRawHeader(key.toUtf8(),value.toUtf8());
            }
        }

        if(!body) {
            body = new QByteArray();
        }

        if(!requestMethod) {
            requestMethod = new QString(Constants::HttpMethods::GET);
        }

        auto reqMethod = *requestMethod;
        if(reqMethod == Constants::HttpMethods::GET) {
            reply = networkAccessManager.get(request);
        }
        else if(reqMethod == Constants::HttpMethods::POST) {
            reply = networkAccessManager.post(request,*body);
        } else if(reqMethod == Constants::HttpMethods::DELETE) {
            reply = networkAccessManager.deleteResource(request);
        } else if(reqMethod == Constants::HttpMethods::PUT) {
            reply = networkAccessManager.put(request,*body);
        } else if(reqMethod == Constants::HttpMethods::HEAD) {
            reply = networkAccessManager.head(request);
        } else {
            reply = networkAccessManager.sendCustomRequest(request,reqMethod.toUtf8(),*body);
        }

        // Wait for the HTTP request to finish
        QEventLoop loop;
        QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        auto response = QByteArray();
        QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug() <<" STATUS CODE IS "<<statusCode.toInt();
        if (statusCode.isValid())
        {
             responseCode = statusCode.toInt();
        }
        response = reply->readAll();
        if (reply->error() == QNetworkReply::NoError)
        {
            responseHeaders = reply->rawHeaderPairs();
            cookies = QNetworkCookie::parseCookies(reply->rawHeader("Set-Cookie"));
            emit requestFinished(false,responseCode,QString(),response,responseHeaders,cookies);
        }else{
            emit requestFinished(true,responseCode,reply->errorString(),response,responseHeaders,cookies);
        }

        reply->deleteLater();
    }  catch (std::exception &ex) {
        auto response = QByteArray();
        emit requestFinished(true,responseCode,ex.what(),response,responseHeaders,cookies);
    }
}


void HttpRequest::newRequest( QUrl *url,
                              QString *requestMethod,
                              QMap<QString, QString> *headers,
                              QByteArray *body, QUrlQuery *urlQuery) {
    this->url = url;
    this->requestMethod = requestMethod;
    this->headers = headers;
    this->body = body;
    this->urlQueryParams = urlQuery;

}

void HttpRequest::start() {
    QThread::start(QThread::Priority::TimeCriticalPriority);
}

void HttpRequest::newRequest(QUrl *url, QString *requestMethod,
                             QMap<QString, QString> *headers, QByteArray *body){
    newRequest(url,requestMethod,headers,body,nullptr);
}


void HttpRequest::newRequest(QUrl *url, QString *requestMethod,
                             QMap<QString, QString> *headers, QUrlQuery *urlQuery) {
    newRequest(url,requestMethod,headers,nullptr,urlQuery);

}

void HttpRequest::terminateBlocking() {
    if(this->isRunning()) {
        cancelRequest();
        this->terminate();
        this->wait();
    }
}

HttpRequest::~HttpRequest() {
    //also add code for termination as well.
    delete this->url;
    delete this->requestMethod;
    delete this->headers;
    delete  this->body;
    delete this->urlQueryParams;
    terminateBlocking();
    qDebug() <<"HTTP REQUEST SCREEN DELETED FOR "<<url;
}
