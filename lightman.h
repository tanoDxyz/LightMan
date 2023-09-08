#ifndef LIGHTMAN_H
#define LIGHTMAN_H

#include <QWidget>
#include <nameatabdialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class LightMan; }
QT_END_NAMESPACE

class LightMan : public QWidget
{
    Q_OBJECT

public:
    LightMan(QWidget *parent = nullptr);
    ~LightMan();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:

    void on_tabWidget_tabCloseRequested(int index);
    void on_tabWidget_tabBarClicked(int index);
    void onNewRequestButtonClicked();
    void onNewServerButtonClicked();
    void onNameATabDialogDismiss(QString& , bool tabTypeIsServer);

private:
    Ui::LightMan *ui;
    NameATabDialog *nameATabDialog;
    void init();
};
#endif // LIGHTMAN_H
