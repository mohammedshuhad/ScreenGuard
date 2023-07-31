#ifndef MODESELECTION_H
#define MODESELECTION_H

#include <QDialog>
#include "infoconfig.h"
#include "messageinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ModeSelection; }
QT_END_NAMESPACE

class ModeSelection : public QDialog
{
    Q_OBJECT

public:
    ModeSelection(QWidget *parent = nullptr);
    ~ModeSelection();

private slots:
    void on_pushButton_clicked();

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void showWindow();

private:
    Ui::ModeSelection *ui;
    InfoConfig *mInfoConfig;
    messageInfo *mMessageConfig;
    bool mRadioToggled;
};
#endif // MODESELECTION_H
