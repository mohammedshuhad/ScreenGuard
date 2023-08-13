#ifndef INFOCONFIG_H
#define INFOCONFIG_H

#include <QDialog>
#include <QLineEdit>
#include <QScreen>
#include <QMessageBox>
#include "ScreenFilter.h"
#include <string>
const int maxFields = 10;

namespace Ui {
class InfoConfig;
}

class InfoConfig : public QDialog
{
    Q_OBJECT

public:
    explicit InfoConfig(QWidget *parent = nullptr);
    ~InfoConfig();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void showWindow();
private:
    Ui::InfoConfig *ui;
    ScreenFilter *mScreenFilter;
    std::vector<QLineEdit*> mLineEdits;
    std::vector<std::string> mEntries;
    int mFieldCount;
    QScreen *screen;
};

#endif // INFOCONFIG_H
