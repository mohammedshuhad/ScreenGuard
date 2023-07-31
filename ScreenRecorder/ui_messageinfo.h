/********************************************************************************
** Form generated from reading UI file 'messageinfo.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEINFO_H
#define UI_MESSAGEINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_messageInfo
{
public:
    QLabel *label;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;

    void setupUi(QDialog *messageInfo)
    {
        if (messageInfo->objectName().isEmpty())
            messageInfo->setObjectName("messageInfo");
        messageInfo->resize(540, 400);
        label = new QLabel(messageInfo);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 30, 231, 21));
        widget = new QWidget(messageInfo);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(360, 360, 168, 26));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        pushButton->setEnabled(true);

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout->addWidget(pushButton_2);

        widget1 = new QWidget(messageInfo);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(40, 80, 90, 52));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        checkBox = new QCheckBox(widget1);
        checkBox->setObjectName("checkBox");

        verticalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(widget1);
        checkBox_2->setObjectName("checkBox_2");

        verticalLayout->addWidget(checkBox_2);


        retranslateUi(messageInfo);

        QMetaObject::connectSlotsByName(messageInfo);
    } // setupUi

    void retranslateUi(QDialog *messageInfo)
    {
        messageInfo->setWindowTitle(QCoreApplication::translate("messageInfo", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("messageInfo", "Select the type of messages to be hidden : ", nullptr));
        pushButton->setText(QCoreApplication::translate("messageInfo", "Start", nullptr));
        pushButton_2->setText(QCoreApplication::translate("messageInfo", "Back", nullptr));
        checkBox->setText(QCoreApplication::translate("messageInfo", "Emails", nullptr));
        checkBox_2->setText(QCoreApplication::translate("messageInfo", "Notification", nullptr));
    } // retranslateUi

};

namespace Ui {
    class messageInfo: public Ui_messageInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEINFO_H
