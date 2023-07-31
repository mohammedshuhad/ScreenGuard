#include "modeselection.h"
#include "./ui_modeselection.h"

ModeSelection::ModeSelection(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModeSelection)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
    mRadioToggled = false;
    mInfoConfig = new InfoConfig(this);
    mMessageConfig = new messageInfo(this);
}

ModeSelection::~ModeSelection()
{
    delete ui;
}


void ModeSelection::on_pushButton_clicked()
{
    if(ui->radioButton->isChecked())
    {
        // specific information hiding
        connect(mInfoConfig, SIGNAL (backButtonClicked()), this, SLOT (showWindow()));
        hide();
        mInfoConfig->show();
    }
    else if (ui->radioButton_2->isChecked())
    {
        // Message hiding
        connect(mMessageConfig, SIGNAL (backButtonClicked()), this, SLOT (showWindow()));
        hide();
        mMessageConfig->show();
    }
}


void ModeSelection::on_radioButton_toggled(bool checked)
{
    if(!mRadioToggled)
    {
    ui->pushButton->setEnabled(true);
    mRadioToggled = true;
    }
}

void ModeSelection::on_radioButton_2_toggled(bool checked)
{
    if(!mRadioToggled)
    {
    ui->pushButton->setEnabled(true);
    mRadioToggled = true;
    }
}

void ModeSelection::showWindow()
{
    show();
}




