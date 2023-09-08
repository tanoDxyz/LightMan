#include "lightman.h"
#include "ui_lightman.h"
#include "QResizeEvent"
#include <QDebug>
#include "iostream"
#include "newrequestscreen.h"
#include "newserverscreen.h"
#include "nameatabdialog.h"
LightMan::LightMan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LightMan)
{
    ui->setupUi(this);
    init();

}


LightMan::~LightMan()
{
    delete ui;
    qDebug() <<" LIGMAN DELETED";
}


void LightMan::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
}


void LightMan::init() {
    const std::function<void(QString&,bool)> clickCallback = [&](QString &tabName,bool tabTypeIsServer) {
           onNameATabDialogDismiss(tabName,tabTypeIsServer);
       };
    nameATabDialog = new NameATabDialog(clickCallback,this);
    ui->tabWidget->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(ui->newRequestButton,&QPushButton::clicked,this,&LightMan::onNewRequestButtonClicked);
    connect(ui->newServerButton,&QPushButton::clicked,this,&LightMan::onNewServerButtonClicked);

    //todo will be working on it later..
    ui->newServerButton->setVisible(false);
}




void LightMan::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}


void LightMan::on_tabWidget_tabBarClicked(int index)
{

}


void LightMan::onNewServerButtonClicked()
{
    nameATabDialog->showDialog(true);
}


void LightMan::onNewRequestButtonClicked()
{
    nameATabDialog->showDialog(false);
}

void LightMan::onNameATabDialogDismiss(QString& tabName,bool tabTypeIsServer) {
    int tabIndex = -1;
    if(tabTypeIsServer) {
        tabIndex = ui->tabWidget->addTab(new NewServerScreen(),tabName);
    } else {
        tabIndex = ui->tabWidget->addTab(new NewRequestScreen(), tabName);
    }
    ui->tabWidget->setCurrentIndex(tabIndex);
    ui->tabWidget->update();
}



