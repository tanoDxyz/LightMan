#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H
#include <QEvent>
#include <QStyledItemDelegate>
#include <QKeyEvent>
#include <QTableWidget>
#include <QToolTip>
#include <QDebug>
// itemdelegate.h
class ItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ItemDelegate(QTableWidget *tableWidget,QObject *parent = nullptr) : QStyledItemDelegate(parent),qTableWidget{tableWidget}
    {

    }

    bool eventFilter(QObject *object, QEvent *event) override
    {
        if (event->KeyPress == QEvent::KeyPress) {
//            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
//            QTableWidgetItem* currentItem = qTableWidget->currentItem();
//                if (currentItem) {
//                    QString typedText = currentItem->text();
//                    currentItem->setToolTip("Typed Text: " + typedText);
//                    QToolTip::showText(QCursor::pos(), currentItem->toolTip());
//                }
        }
        return false;
    }
private:
    QTableWidget *qTableWidget;
};
#endif // ITEMDELEGATE_H
