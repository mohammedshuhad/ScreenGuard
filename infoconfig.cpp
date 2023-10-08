#include "InfoConfig.h"
#include "ui_infoconfig.h"

InfoConfig::InfoConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoConfig)
{
    ui->setupUi(this);
    mFieldCount = 0;
    mScreenFilter = new ScreenFilter();
    setScreenImages();
    //screen = QGuiApplication::primaryScreen();

}

void InfoConfig::setScreenImages()
{
    QList<QScreen*> screens = QGuiApplication::screens();

    if (screens.size() == 2)
    {
        QPixmap pixmap = screens.at(0)->grabWindow(0);
        int newWidth = pixmap.width() / 10;
        int newHeight = pixmap.height() / 10;
        QPixmap scaledPixmap = pixmap.scaled(newWidth, newHeight);
        ui->label_3->setPixmap(scaledPixmap);
        pixmap = screens.at(1)->grabWindow(0);
        newWidth = pixmap.width() / 10;
        newHeight = pixmap.height() / 10;
        scaledPixmap = pixmap.scaled(newWidth, newHeight);
        ui->label_4->setPixmap(scaledPixmap);
    }
    else
    {
        QPixmap pixmap = screens.at(0)->grabWindow(0);
        int newWidth = pixmap.width() / 10;
        int newHeight = pixmap.height() / 10;
        QPixmap scaledPixmap = pixmap.scaled(newWidth, newHeight);
        ui->label_3->setPixmap(scaledPixmap);
        ui->label_4->setText("\tNot Available");
        ui->label_4->setStyleSheet("border: 1px solid black; margin: 10px 10px;");
    }

}

InfoConfig::~InfoConfig()
{
    delete ui;
}

void InfoConfig::on_pushButton_2_clicked()
{
    //clear field button
    if (!mLineEdits.empty())
    {
        ui->verticalLayout->removeWidget(mLineEdits.back());
        mLineEdits.pop_back();
        mFieldCount--;
    }
}


void InfoConfig::on_pushButton_clicked()
{
    //start button
    if (!ui->lineEdit->text().toStdString().empty())
    {
        mEntries.push_back(ui->lineEdit->text().toStdString());
    }
    for (auto entry : mLineEdits)
    {
        QString text = entry->text();
        mEntries.push_back(text.toStdString());
    }

    QList<QScreen*> screens = QGuiApplication::screens();
    bool secondary = false;
    if (screens.size() == 2)
    {
        if (ui->radioButton->isChecked())
        {
            //primary
            screen = screens.at(0);
        }
        else if (ui->radioButton_2->isChecked())
        {
            // secondary
            screen = screens.at(1);
            secondary = true;
        }
    }
    else
    {
        screen = QGuiApplication::primaryScreen();
    }

    connect(mScreenFilter, SIGNAL (backButtonClicked()), this, SLOT (showWindow()));
    mScreenFilter->getFieldEntries(mEntries, secondary);
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

