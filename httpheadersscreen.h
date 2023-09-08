#ifndef HTTPHEADERSSCREEN_H
#define HTTPHEADERSSCREEN_H
#include "Utils.h"

#include <QTableWidgetItem>
#include <QWidget>
#include <httprequest.h>
namespace Ui {
class HttpHeadersScreen;
}

class HttpHeadersScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HttpHeadersScreen(int type,QWidget *parent = nullptr);
    ~HttpHeadersScreen();

    QTableWidgetItem* firstColumn(QTableWidgetItem *item);
    QTableWidgetItem *secondColumn(QTableWidgetItem *item);
    bool tableItemIsEmpty(QTableWidgetItem *item);
    void insertRowData(const QString &key, const QString &value, const QString &description);
    void insertRowData(int index, const QString &key, const QString &value, const QString &description);
    QMap<QString, QString>* getKeyValuePairs();
public slots:
    void onTableWidgetItemChanged(QTableWidgetItem *item);
    void onCellChanged(int row, int column);
private:
    Ui::HttpHeadersScreen *ui;
    const int type;
    void init();
    void setTypeLabelText();
    void setupTableWidget();
    Counter *counter = nullptr;
};

#endif // HTTPHEADERSSCREEN_H
