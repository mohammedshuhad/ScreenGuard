#include "infoconfig.h"
#include "ui_infoconfig.h"
#include<QMessageBox>
InfoConfig::InfoConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoConfig)
{
    ui->setupUi(this);
    mFieldCount = 0;
    mScreenFilter = new ScreenFilter();
    screen = QGuiApplication::primaryScreen();
}

InfoConfig::~InfoConfig()
{
    delete ui;
}

void InfoConfig::on_pushButton_2_clicked()
{
    //back button
    emit backButtonClicked();
    hide();

}


void InfoConfig::on_pushButton_clicked()
{
    //start button
    for (auto entry : mLineEdits)
    {
        QString text = entry->text();
        mEntries.push_back(text.toStdString());
    }
    connect(mScreenFilter, SIGNAL (backButtonClicked()), this, SLOT (showWindow()));
    mScreenFilter->getFieldEntries(mEntries);
    mScreenFilter->show();
    mScreenFilter->move(0,0);
    mScreenFilter->resize(screen->availableGeometry().width(),
                          screen->availableGeometry().height());
    mScreenFilter->showMaximized();
    hide();
}


void InfoConfig::on_pushButton_3_clicked()
{
    // add new field button
    if(mFieldCount < maxFields)
    {
        mFieldCount++;
        QLineEdit *lineEdit = new QLineEdit(this);
        lineEdit->setPlaceholderText("Enter the text to be hidden here...");
        mLineEdits.push_back(lineEdit);

        ui->verticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        ui->verticalLayout->addWidget(lineEdit);
    }
    else
    {
        QMessageBox::information(this, "Fields Exceeded", "You have reached the maximum number of fields that can be configured !");
    }
}

void InfoConfig::showWindow()
{
    show();
}

