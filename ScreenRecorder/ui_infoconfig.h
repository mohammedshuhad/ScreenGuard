/********************************************************************************
** Form generated from reading UI file 'infoconfig.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFOCONFIG_H
#define UI_INFOCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InfoConfig
{
public:
    QLabel *label;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;

    void setupUi(QDialog *InfoConfig)
    {
        if (InfoConfig->objectName().isEmpty())
            InfoConfig->setObjectName("InfoConfig");
        InfoConfig->resize(540, 400);
        label = new QLabel(InfoConfig);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 241, 31));
        widget = new QWidget(InfoConfig);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(270, 350, 255, 26));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName("pushButton_3");

        horizontalLayout->addWidget(pushButton_3);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout->addWidget(pushButton_2);

        widget1 = new QWidget(InfoConfig);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(20, 60, 241, 31));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(widget1);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);


        retranslateUi(InfoConfig);

        QMetaObject::connectSlotsByName(InfoConfig);
    } // setupUi

    void retranslateUi(QDialog *InfoConfig)
    {
        InfoConfig->setWindowTitle(QCoreApplication::translate("InfoConfig", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("InfoConfig", "Add the Specific Information to be hidden :", nullptr));
        pushButton_3->setText(QCoreApplication::translate("InfoConfig", "Add new field", nullptr));
        pushButton->setText(QCoreApplication::translate("InfoConfig", "Start", nullptr));
        pushButton_2->setText(QCoreApplication::translate("InfoConfig", "Close", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("InfoConfig", "Enter the text to be hidden here...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InfoConfig: public Ui_InfoConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFOCONFIG_H
