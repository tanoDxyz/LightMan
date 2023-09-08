#include "newrequestscreen.h"
#include "ui_newrequestscreen.h"
#include <QtDebug>
#include <Constants.h>
#include "httpheadersscreen.h"
#include "edittext.h"
#include "highlighter.h"
#include "responsecookies.h"
#include "responseheaders.h"
#include "httprequest.h"
#include <requestscreencontroller.h>
#include <QTimer>
NewRequestScreen::NewRequestScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewRequestScreen),bodyEditText{new EditText(this)},responseEditText{new EditText(this)}
{
    ui->setupUi(this);
    init();
}

NewRequestScreen::~NewRequestScreen()
{
    qDebug() <<"DELETED NEW REQUEST_SCREEN";
    delete ui;
    delete bodyEditText;
    delete responseEditText;
    delete controller;
    delete responseHeadersScreen;
    delete responseCookiesScreen;
    delete requestHeaderScreen;
    delete requestParamScreen;
    qDebug() <<" NEW REQUEST SCREEN DELETED";
}



void NewRequestScreen::init() {
    bodyEditTextHighlighter = new Highlighter(bodyEditText->document());
    responseEditTextHighlighter = new Highlighter(responseEditText->document());
    controller = new RequestScreenController();
    controller->setResponseCallback([&](HttpResponse response) {
        onHttpResponseRecieved(response);
    });
    populateComboxBoxForRequestTypeMethods();
    setupTabs();
}

QMap<QString, QString>* NewRequestScreen::getRequestHeaders() {
    return keyValuePairsFromParamsAndRequestHeadersScreens(Constants::HEADERS);
}

QUrlQuery* NewRequestScreen::getQueryParams() {
    auto keyValuePairs = keyValuePairsFromParamsAndRequestHeadersScreens(Constants::PARAMS);
    QUrlQuery *urlQuery {new QUrlQuery () };
    for (auto it = keyValuePairs->constBegin(); it != keyValuePairs->constEnd(); ++it) {
        urlQuery->addQueryItem(it.key(), it.value());
    }
    delete keyValuePairs;
    return urlQuery;
}

QMap<QString, QString>* NewRequestScreen::keyValuePairsFromParamsAndRequestHeadersScreens(int type) {
    QMap<QString, QString>* keyValuePairs = nullptr;
    if(requestHeaderScreen && type == Constants::HEADERS) {
        keyValuePairs  = requestHeaderScreen->getKeyValuePairs();
    }

    if(requestParamScreen && type == Constants::PARAMS) {
        keyValuePairs  = requestParamScreen->getKeyValuePairs();
    }
    return keyValuePairs;
}
void NewRequestScreen::setupTabs() {
    //request
    ui->tabWidget->clear();
    requestHeaderScreen = {new HttpHeadersScreen{Constants::HEADERS,this}};
    requestParamScreen ={new HttpHeadersScreen{Constants::PARAMS,this}};
    ui->tabWidget->addTab(requestParamScreen,"Params");
    ui->tabWidget->addTab(requestHeaderScreen,"Headers");
    ui->tabWidget->addTab(bodyEditText,"Body");

    // response
    responseHeadersScreen = {new ResponseHeaders(this)};
    responseCookiesScreen = {new ResponseCookies(this)};
    ui->responseTabWidget->clear();
    ui->responseTabWidget->addTab(responseEditText,"Body");
    ui->responseTabWidget->addTab(responseHeadersScreen,"Headers");
    ui->responseTabWidget->addTab(responseCookiesScreen,"Cookies");

}

void NewRequestScreen::populateComboxBoxForRequestTypeMethods()
{
    auto requestTypeMethods = QStringList();
    requestTypeMethods.append(Constants::HttpMethods::GET);
    requestTypeMethods.append(Constants::HttpMethods::HEAD);
    requestTypeMethods.append(Constants::HttpMethods::POST);
    requestTypeMethods.append(Constants::HttpMethods::PUT);
    requestTypeMethods.append(Constants::HttpMethods::DELETE);
    requestTypeMethods.append(Constants::HttpMethods::NONE);
    ui->requestTypeComboBox->insertItems(0,requestTypeMethods);
}

void NewRequestScreen::on_urlTextEdit_textChanged()
{
    // increate height of the url input view based on height of the screen or window.
    QSize size = ui->urlTextEdit->document()->size().toSize();
    if(size.height() > Constants::NEW_REQUEST_URL_INPUT_TEXT_EDIT_MAX_HEIGHT) {
        return;
    }
    ui->urlTextEdit->setFixedHeight( size.height() + 3 );
}


void NewRequestScreen::on_requestTypeComboBox_currentIndexChanged(int index)
{
    // make the last tab editable
    if (index == ui->requestTypeComboBox->count()-1)
        ui->requestTypeComboBox->setEditable(true);
    else
        ui->requestTypeComboBox->setEditable(false);
}


void NewRequestScreen::on_requestTypeComboBox_currentTextChanged(const QString &arg1)
{
    // once the last tab is edited make sure the text is reflected on the combo box tab.
    ui->requestTypeComboBox->setItemText(ui->requestTypeComboBox->currentIndex(),arg1);
}

//"<span style='color:red;'>This is red text</span> and <span style='font-weight:bold;'>this is bold text</span>";

void NewRequestScreen::on_sendButton_clicked()
{
    ui->sendButton->setEnabled(false);
    ui->responseLabel->setText("Response\t <span style='font-weight:bold;'>---------> 🌐 </span>");
    responseEditText->clear();
    responseHeadersScreen->clear();
    responseCookiesScreen->clear();
    prepareDataAndMakeRequest();

}

void NewRequestScreen::prepareDataAndMakeRequest() {
    auto url {new QUrl{ui->urlTextEdit->toPlainText()}};
    auto requestMethod {new QString{ui->requestTypeComboBox->currentText()}};
    auto requestHeaders = getRequestHeaders();
    auto queryParams = getQueryParams();
    QByteArray *body = new QByteArray{bodyEditText->toPlainText().toUtf8()};
    controller->newRequest(url,requestMethod,requestHeaders,body,queryParams);
    controller->start();
}
void NewRequestScreen::onHttpResponseRecieved(HttpResponse response) {
    QString responseLabelText;
    //response label
    if(response.responseCode == 200) {
        responseLabelText = QString("Response\t<span style='font-weight:bold;color:green'>Status Code = %1 %2</span>");
    } else {
        responseLabelText = QString("Response\t<span style='font-weight:bold;color:red'>Status Code = %1, error ---->  %2</span>");
    }
    ui->responseLabel->setText(responseLabelText.
                               arg(response.responseCode).arg(response.errorString));


    //body
    responseEditText->appendPlainText(response.response);
    responseEditText->beautifyJson();
    // headers
    responseHeadersScreen->setHeaders(response.responseHeaders);

    responseCookiesScreen->setCookies(response.cookies);
    ui->sendButton->setEnabled(true);




}

