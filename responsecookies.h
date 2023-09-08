#ifndef RESPONSECOOKIES_H
#define RESPONSECOOKIES_H

#include <QNetworkCookie>
#include <QWidget>

namespace Ui {
class ResponseCookies;
}

class ResponseCookies : public QWidget
{
    Q_OBJECT

public:
    explicit ResponseCookies(QWidget *parent = nullptr);
    ~ResponseCookies();

    void clear();
    void setCookies(const QList<QNetworkCookie>& responseCookies);
private:
    Ui::ResponseCookies *ui;
};

#endif // RESPONSECOOKIES_H
