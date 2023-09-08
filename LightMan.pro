QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Utils.cpp \
    edittext.cpp \
    highlighter.cpp \
    httpheadersscreen.cpp \
    httprequest.cpp \
    httpresponse.cpp \
    main.cpp \
    lightman.cpp \
    nameatabdialog.cpp \
    newrequestscreen.cpp \
    newserverscreen.cpp \
    requestscreencontroller.cpp \
    responsecookies.cpp \
    responseheaders.cpp

HEADERS += \
    Constants.h \
    ItemDelegate.h \
    Utils.h \
    edittext.h \
    highlighter.h \
    httpheadersscreen.h \
    httprequest.h \
    httpresponse.h \
    lightman.h \
    nameatabdialog.h \
    newrequestscreen.h \
    newserverscreen.h \
    requestscreencontroller.h \
    responsecookies.h \
    responseheaders.h

FORMS += \
    form.ui \
    httpheadersscreen.ui \
    lightman.ui \
    nameatabdialog.ui \
    newrequestscreen.ui \
    newserverscreen.ui \
    responsecookies.ui \
    responseheaders.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

OPENSSL_LIBS='-L/opt/ssl/lib -lssl -lcrypto' ./configure -openssl-linked
