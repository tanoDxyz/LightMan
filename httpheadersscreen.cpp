#include "httpheadersscreen.h"
#include "ui_httpheadersscreen.h"
#include "Constants.h"
#include <QDebug>
#include "ItemDelegate.h"
HttpHeadersScreen::HttpHeadersScreen(int type , QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HttpHeadersScreen),type{type},counter{new Counter{0}}
{
    ui->setupUi(this);
    init();
}

HttpHeadersScreen::~HttpHeadersScreen()
{
    delete ui;
    qDebug() <<" HTTP HEADER SCREEN DELETED WITH TYPE "<<type;
}

void HttpHeadersScreen::init() {
    setTypeLabelText();
    setupTableWidget();
}

void HttpHeadersScreen::setTypeLabelText() {
    // set label (extra indicator for type
    auto typeLabelText {new QString("Headers")};
    if(type == Constants::PARAMS) {
        delete typeLabelText;
        typeLabelText = {new QString("Query Params")};
    }
    ui->label->setText(*typeLabelText);
}

QMap<QString, QString>* HttpHeadersScreen::getKeyValuePairs() {
    QMap<QString, QString> *headers = new QMap<QString, QString>;

    int rowCount = ui->tableWidget->rowCount();

    for (int row = 0; row < rowCount; ++row) {
        QTableWidgetItem *item0 = ui->tableWidget->item(row, 0); // Assuming column 0 is for keys
        QTableWidgetItem *item1 = ui->tableWidget->item(row, 1); // Assuming column 1 is for values
        if (item0 && item1) {
            QString key = item0->text();
            QString value = item1->text();
            if(key.isEmpty() || value.isEmpty()) {
                continue;
            }
            // Add the key-value pair to the map
            headers->insert(key, value);
        }
    }
    return headers;
}

void HttpHeadersScreen::insertRowData(int index, const QString &key, const QString &value, const QString &description) {
    if(index < 0) {
        index = 0;
    }
    qDebug()<<"Insertion index is "<<index;
    ui->tableWidget->insertRow(index);

    QTableWidgetItem *column0Item {new QTableWidgetItem(key)};

    ui->tableWidget->setItem(index,0,column0Item);

    QTableWidgetItem *column1Item {new QTableWidgetItem(value)};
    ui->tableWidget->setItem(index,1,column1Item);

    QTableWidgetItem *column2Item {new QTableWidgetItem(description)};
    ui->tableWidget->setItem(index,2,column2Item);
    column2Item->setToolTip(QString("hey there"));


    auto tableWidgetLayout = static_cast<QWidget*>(ui->tableWidget->parent());
    auto availableWidth = tableWidgetLayout->width();
    auto perColumnWidth = availableWidth / ui->tableWidget->columnCount();
    ui->tableWidget->setColumnWidth(0,perColumnWidth);
    ui->tableWidget->setColumnWidth(1,perColumnWidth);
    ui->tableWidget->setColumnWidth(2,perColumnWidth);
    column0Item->setTextColor(Qt::darkMagenta);
    column1Item->setTextColor(Qt::darkMagenta);
    column2Item->setTextColor(Qt::darkMagenta);

}

void HttpHeadersScreen::setupTableWidget() {
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::ContiguousSelection);

    auto headers = QStringList();
    headers.append(trUtf8("Key"));
    headers.append(trUtf8("Value"));
    headers.append(trUtf8("Description"));
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    // set headers alignment to left
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        QTableWidgetItem *headerItem = ui->tableWidget->horizontalHeaderItem(col);
        if (headerItem) {
            headerItem->setTextAlignment(Qt::AlignLeft);
        }
    }

    insertRowData(QString(trUtf8("")),QString(trUtf8("")),QString(trUtf8("Description")));
    connect(ui->tableWidget,&QTableWidget::itemChanged,this,&HttpHeadersScreen::onTableWidgetItemChanged);
    connect(ui->tableWidget,&QTableWidget::cellChanged,this,&HttpHeadersScreen::onCellChanged);

}

void HttpHeadersScreen::insertRowData(const QString &key, const QString &value, const QString &description) {
    insertRowData(counter->getAndIncrement(),key,value,description);
}

QTableWidgetItem* HttpHeadersScreen::firstColumn(QTableWidgetItem *item) {
    auto currentRowChangedItem = item->row();
    if(item->column() == 0) {
        return item;
    }
    auto firstColumn = ui->tableWidget->item(currentRowChangedItem,0);
    return firstColumn;
}

QTableWidgetItem* HttpHeadersScreen::secondColumn(QTableWidgetItem *item) {
    auto currentRowChangedItem = item->row();
    if(item->column() == 1) {
        return item;
    }
    auto secondColumn = ui->tableWidget->item(currentRowChangedItem,1);
    return secondColumn;
}



bool HttpHeadersScreen::tableItemIsEmpty(QTableWidgetItem *item){
    QString localText = item->text();
    return (localText.isEmpty());
}

void HttpHeadersScreen::onTableWidgetItemChanged(QTableWidgetItem *item) {
    auto currentRowChangedItem = item->row();
    auto firstColumn = ui->tableWidget->item(currentRowChangedItem,0);
    auto secondColumn = ui->tableWidget->item(currentRowChangedItem,1);

    auto firstColumnIsEmpty = tableItemIsEmpty(firstColumn);
    if(!firstColumnIsEmpty) {
        auto seconColumnIsEmpty = tableItemIsEmpty(secondColumn);
        if(seconColumnIsEmpty) {
            secondColumn->setText("");
        }
    }

}

void HttpHeadersScreen::onCellChanged(int row, int column) {
    if(column == 0) { // add it based on
        auto lastElement = ui->tableWidget->item(ui->tableWidget->rowCount()-1,0);
        auto currentChangedCellIsInLastRow = ui->tableWidget->rowCount()-1 == row;
        if(!tableItemIsEmpty(lastElement) && currentChangedCellIsInLastRow) {
            insertRowData(QString(trUtf8("")),QString(trUtf8("")),QString(trUtf8("Description")));
        }

    }
}


