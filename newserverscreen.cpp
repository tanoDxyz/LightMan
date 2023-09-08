#include "newserverscreen.h"
#include "ui_newserverscreen.h"

NewServerScreen::NewServerScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewServerScreen)
{
    ui->setupUi(this);
}

NewServerScreen::~NewServerScreen()
{
    delete ui;
}
