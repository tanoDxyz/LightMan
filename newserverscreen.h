#ifndef NEWSERVERSCREEN_H
#define NEWSERVERSCREEN_H

#include <QWidget>

namespace Ui {
class NewServerScreen;
}

class NewServerScreen : public QWidget
{
    Q_OBJECT

public:
    explicit NewServerScreen(QWidget *parent = nullptr);
    ~NewServerScreen();

private:
    Ui::NewServerScreen *ui;
};

#endif // NEWSERVERSCREEN_H
