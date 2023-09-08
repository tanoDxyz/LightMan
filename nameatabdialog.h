#ifndef NAMEATABDIALOG_H
#define NAMEATABDIALOG_H

#include "Utils.h"

#include <QDialog>
#include <functional>
namespace Ui {
class NameATabDialog;
}

class NameATabDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::NameATabDialog *ui;
    const std::function<void(QString&,bool)> clickCallback;
    Counter *requestTabCounter;
    Counter *serverTabCounter;
    bool tabTypeIsServer = false;

public:
    explicit NameATabDialog(const std::function<void(QString&,bool)> clickCallback,QWidget *parent = nullptr);
    void showEvent(QShowEvent *) override;
    void showDialog(bool);
    ~NameATabDialog();


private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

};

#endif // NAMEATABDIALOG_H
