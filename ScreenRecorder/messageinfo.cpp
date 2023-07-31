#include "messageinfo.h"
#include "ui_messageinfo.h"

messageInfo::messageInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::messageInfo)
{
    ui->setupUi(this);
}

messageInfo::~messageInfo()
{
    delete ui;
}

void messageInfo::on_pushButton_2_clicked()
{
    emit backButtonClicked();
    hide();
}


void messageInfo::on_pushButton_clicked()
{
    // Start button
}

