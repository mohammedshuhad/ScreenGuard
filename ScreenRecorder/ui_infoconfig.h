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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InfoConfig
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioButton;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButton_2;
    QLabel *label_4;

    void setupUi(QDialog *InfoConfig)
    {
        if (InfoConfig->objectName().isEmpty())
            InfoConfig->setObjectName("InfoConfig");
        InfoConfig->resize(675, 669);
        label = new QLabel(InfoConfig);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 290, 241, 31));
        layoutWidget = new QWidget(InfoConfig);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(400, 630, 255, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName("pushButton_3");

        horizontalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        layoutWidget1 = new QWidget(InfoConfig);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(30, 330, 241, 31));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(layoutWidget1);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);

        label_2 = new QLabel(InfoConfig);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 30, 211, 16));
        widget = new QWidget(InfoConfig);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(70, 80, 451, 161));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        radioButton = new QRadioButton(widget);
        radioButton->setObjectName("radioButton");

        verticalLayout_2->addWidget(radioButton);

        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        radioButton_2 = new QRadioButton(widget);
        radioButton_2->setObjectName("radioButton_2");

        verticalLayout_3->addWidget(radioButton_2);

        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");

        verticalLayout_3->addWidget(label_4);


        horizontalLayout_2->addLayout(verticalLayout_3);


        retranslateUi(InfoConfig);

        QMetaObject::connectSlotsByName(InfoConfig);
    } // setupUi

    void retranslateUi(QDialog *InfoConfig)
    {
        InfoConfig->setWindowTitle(QCoreApplication::translate("InfoConfig", "Configuration Window", nullptr));
        InfoConfig->setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_DesktopIcon));
        InfoConfig->setStyleSheet("background-color: #333333; color: white;");
        label->setText(QCoreApplication::translate("InfoConfig", "Add the Specific Information to be hidden :", nullptr));
        pushButton_3->setText(QCoreApplication::translate("InfoConfig", "Add new field", nullptr));
        pushButton_2->setText(QCoreApplication::translate("InfoConfig", "Clear field", nullptr));
        pushButton->setText(QCoreApplication::translate("InfoConfig", "Start", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("InfoConfig", "Enter the text to be hidden here...", nullptr));
        label_2->setText(QCoreApplication::translate("InfoConfig", "Select the screen to be monitored : ", nullptr));
        radioButton->setText(QCoreApplication::translate("InfoConfig", "Primary Screen", nullptr));
        label_3->setText(QString());
        radioButton_2->setText(QCoreApplication::translate("InfoConfig", "Secondary Screen", nullptr));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InfoConfig: public Ui_InfoConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFOCONFIG_H
