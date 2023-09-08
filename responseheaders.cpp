#include "responseheaders.h"
#include "ui_responseheaders.h"
#include <QTextEdit>
#include <QtDebug>
ResponseHeaders::ResponseHeaders(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResponseHeaders)
{
    ui->setupUi(this);
}

ResponseHeaders::~ResponseHeaders()
{
    delete ui;
    qDebug() <<"Response Headeres deleted";
}

void ResponseHeaders::clear() {
    ui->tableWidget->clear();
}

void ResponseHeaders::setHeaders(const QList<QPair<QByteArray,QByteArray>>& responseHeaders) {


    // Create a QTableWidget
    QTableWidget* tableWidget = ui->tableWidget;
    tableWidget->setRowCount(responseHeaders.size());
    tableWidget->setColumnCount(2);
    tableWidget->setHorizontalHeaderLabels({"Header", "Value"});
    auto tableWidgetLayout = static_cast<QWidget*>(ui->tableWidget->parent());
    auto availableWidth = tableWidgetLayout->width();
    auto perColumnWidth = availableWidth / ui->tableWidget->columnCount();
    tableWidget->setColumnWidth(0,perColumnWidth);
    tableWidget->setColumnWidth(1,perColumnWidth);
    int row = 0;
    for (const auto& header : responseHeaders)
    {
        QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromUtf8(header.first));
        QTableWidgetItem* valueItem = new QTableWidgetItem(QString::fromUtf8(header.second));

        tableWidget->setItem(row, 0, nameItem);
        tableWidget->setItem(row, 1, valueItem);

        ++row;
    }
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

