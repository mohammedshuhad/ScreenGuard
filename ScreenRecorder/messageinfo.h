#ifndef MESSAGEINFO_H
#define MESSAGEINFO_H

#include <QDialog>

namespace Ui {
class messageInfo;
}

class messageInfo : public QDialog
{
    Q_OBJECT

public:
    explicit messageInfo(QWidget *parent = nullptr);
    ~messageInfo();


private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

signals:
    void backButtonClicked();

private:
    Ui::messageInfo *ui;
};

#endif // MESSAGEINFO_H
