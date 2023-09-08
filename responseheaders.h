#ifndef RESPONSEHEADERS_H
#define RESPONSEHEADERS_H

#include <QWidget>

namespace Ui {
class ResponseHeaders;
}

class ResponseHeaders : public QWidget
{
    Q_OBJECT

public:
    explicit ResponseHeaders(QWidget *parent = nullptr);
    ~ResponseHeaders();

    void setHeaders(const QList<QPair<QByteArray,QByteArray>>& responseHeaders);
    void clear();
private:
    Ui::ResponseHeaders *ui;
};

#endif // RESPONSEHEADERS_H
