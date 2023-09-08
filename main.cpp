#include "lightman.h"
#include "nameatabdialog.h"
#include <QApplication>
#include "QDebug"
#include <QNetworkCookie>
#include <iostream>

void registerCustomMetaTypes() {
    // Register custom types
    qRegisterMetaType<QByteArray>("QByteArray");
    qRegisterMetaType<QList<QPair<QByteArray, QByteArray>>>("QList<QPair<QByteArray,QByteArray>>");
    qRegisterMetaType<QList<QNetworkCookie>>("QList<QNetworkCookie>");
}
int main(int argc, char *argv[])
{

    registerCustomMetaTypes();
    QApplication a(argc, argv);
    LightMan w;
    w.show();

    return a.exec();
}



