#ifndef REQUESTSHANDLER_H
#define REQUESTSHANDLER_H
/**
 * This class is designed for single thread access without blocking.
 * it is thread un safe. (no parralel or concurrent modification will be handled.)
 *
 *
 *
 * */
#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QMap>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QNetworkSession>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QNetworkAccessManager>


class HttpRequest : public QThread
{
    Q_OBJECT
public:
    explicit HttpRequest(QObject *parent = nullptr);
    ~HttpRequest();
    void newRequest(QUrl *url,QString *requestMethod,
                    QMap<QString,QString> *headers, QUrlQuery *urlQuery);

    void newRequest( QUrl *url, QString *requestMethod,
                     QMap<QString,QString> *headers, QByteArray* body);

    void newRequest( QUrl *url, QString *requestMethod,
                     QMap<QString,QString> *headers, QByteArray* body, QUrlQuery *urlQuery);
    void start();

    void cancelRequest();

    void terminateBlocking();

    bool openConnection(const std::function<void(bool)> callback) {

        auto networkManager{ QNetworkConfigurationManager{this}};

        const bool canStartIAP = (networkManager.capabilities() &
                                  QNetworkConfigurationManager::CanStartAndStopInterfaces);
        // default access point, use it
        QNetworkConfiguration cfg = networkManager.defaultConfiguration();
        if (!cfg.isValid() || (!canStartIAP && cfg.state() !=
                               QNetworkConfiguration::Active))
        {
            callback(false);
            return false;
        }
        QNetworkSession* session = new QNetworkSession(cfg, this);
        session->open();
        return session->waitForOpened(-1);
    }

private:
    QUrl *url = nullptr;
    QString *requestMethod = nullptr;
    QMap<QString , QString> *headers = nullptr;
    QByteArray *body = nullptr;
    QUrlQuery *urlQueryParams = nullptr;
    QNetworkReply* reply = nullptr;

signals:
    void requestFinished(bool error,
                         int statusCode,
                         const QString& errorString,
                         const QByteArray& response,
                         const QList<QPair<QByteArray,QByteArray>>& responseHeaders,
                         const QList<QNetworkCookie>& cookies);
protected:
    void run() override;
};

#endif // REQUESTSHANDLER_H
