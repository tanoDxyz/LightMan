#include "responsecookies.h"
#include "ui_responsecookies.h"
#include <QNetworkCookie>
#include <qdebug.h>
#include <QDateTime>
ResponseCookies::ResponseCookies(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResponseCookies)
{
    ui->setupUi(this);
}

ResponseCookies::~ResponseCookies()
{
    delete ui;
    qDebug()<<" RESPONSE COOKIES DELETED";
}

void ResponseCookies::clear() {
    ui->tableWidget->clear();
}

void ResponseCookies::setCookies(const QList<QNetworkCookie>& responseCookies) {
    // Create a QTableWidget
    QTableWidget* tableWidget = ui->tableWidget;
    tableWidget->setRowCount(responseCookies.size());
    tableWidget->setColumnCount(4);
    tableWidget->setHorizontalHeaderLabels({"Name", "Domain","Path","Expiration Date"});
    auto tableWidgetLayout = static_cast<QWidget*>(ui->tableWidget->parent());
    auto availableWidth = tableWidgetLayout->width();
    auto perColumnWidth = availableWidth / ui->tableWidget->columnCount();
    tableWidget->setColumnWidth(0,perColumnWidth);
    tableWidget->setColumnWidth(1,perColumnWidth);
    tableWidget->setColumnWidth(2,perColumnWidth);
    tableWidget->setColumnWidth(3,perColumnWidth);
    int row = 0;
    for (const auto& cookie : responseCookies)
    {
        QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromUtf8(cookie.name()));
        QTableWidgetItem* domainItem = new QTableWidgetItem(cookie.domain());

        tableWidget->setItem(row, 0, nameItem);
        tableWidget->setItem(row, 1, domainItem);

        QTableWidgetItem* pathItem = new QTableWidgetItem(cookie.path());
        QTableWidgetItem* expirationDateItem = new QTableWidgetItem(cookie.expirationDate().toLocalTime().toString());

        tableWidget->setItem(row, 2, pathItem);
        tableWidget->setItem(row, 3, expirationDateItem);

        ++row;
    }
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
