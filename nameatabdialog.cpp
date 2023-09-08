#include "nameatabdialog.h"
#include "ui_nameatabdialog.h"
#include "QtDebug"

NameATabDialog::NameATabDialog(const std::function<void(QString&,bool)> callback,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NameATabDialog),clickCallback{callback},requestTabCounter{new Counter{1}},serverTabCounter {new Counter{1}}
{
    ui->setupUi(this);

}

NameATabDialog::~NameATabDialog()
{
    delete ui;
    delete requestTabCounter;
    delete serverTabCounter;
    qDebug() <<"NAME A TAB DIALOG DELETED";
}

void NameATabDialog::on_buttonBox_accepted()
{
   QString text = ui->textEdit->toPlainText().replace("\n", " ");;
   if(text.isEmpty() || text.isNull()) {
    int tabCounter = tabTypeIsServer ? serverTabCounter->getAndIncrement() : requestTabCounter->getAndIncrement();
    QString tabTitle = tabTypeIsServer ? QString("Server") : QString("Request");
    text = tabTitle.append(tr(" - %1")).arg(tabCounter);
   }
    (clickCallback)(text,tabTypeIsServer);
}



void NameATabDialog::on_buttonBox_rejected()
{
   //todo implement something.
}

void NameATabDialog::showEvent(QShowEvent *event) {
    ui->textEdit->clear();
}

void NameATabDialog::showDialog(bool server) {
    tabTypeIsServer = server;
    this->show();
}
