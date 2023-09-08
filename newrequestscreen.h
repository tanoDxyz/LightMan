#ifndef NEWREQUESTSCREEN_H
#define NEWREQUESTSCREEN_H

#include "edittext.h"
#include "highlighter.h"
#include <httprequest.h>
#include <QWidget>
#include "httpresponse.h"
#include "requestscreencontroller.h"
#include "responseheaders.h"
#include "responsecookies.h"
#include "httpheadersscreen.h"
namespace Ui {
class NewRequestScreen;
}

class NewRequestScreen : public QWidget
{
    Q_OBJECT

public:
    explicit NewRequestScreen(QWidget *parent = nullptr);
    ~NewRequestScreen();
    void onHttpResponseRecieved(HttpResponse response);
    QMap<QString, QString>* getRequestHeaders();
    QUrlQuery* getQueryParams();

private slots:
    void on_urlTextEdit_textChanged();
    void on_requestTypeComboBox_currentIndexChanged(int index);
    void on_requestTypeComboBox_currentTextChanged(const QString &arg1);
    void setupTabs();
    void on_sendButton_clicked();

private:
    Ui::NewRequestScreen *ui;
    void init();
    void populateComboxBoxForRequestTypeMethods();
    EditText *bodyEditText = nullptr;
    EditText *responseEditText = nullptr;
    Highlighter *responseEditTextHighlighter = nullptr;
    Highlighter *bodyEditTextHighlighter = nullptr;
    RequestScreenController *controller = nullptr;
    ResponseHeaders *responseHeadersScreen = nullptr;
    ResponseCookies *responseCookiesScreen = nullptr;
    HttpHeadersScreen *requestHeaderScreen = nullptr;
    HttpHeadersScreen *requestParamScreen = nullptr;
    QMap<QString, QString>* keyValuePairsFromParamsAndRequestHeadersScreens(int type);
    void prepareDataAndMakeRequest();
};

#endif // NEWREQUESTSCREEN_H
