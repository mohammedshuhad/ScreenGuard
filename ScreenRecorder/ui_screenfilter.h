/********************************************************************************
** Form generated from reading UI file 'screenfilter.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENFILTER_H
#define UI_SCREENFILTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_ScreenFilter
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QStatusBar *statusbar;
    QLabel* label;

    void setupUi(QMainWindow *ScreenFilter)
    {
        if (ScreenFilter->objectName().isEmpty())
            ScreenFilter->setObjectName("ScreenFilter");
        ScreenFilter->resize(800, 600);
        centralwidget = new QWidget(ScreenFilter);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 0, 80, 24));
        ScreenFilter->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(ScreenFilter);
        statusbar->setObjectName("statusbar");
        ScreenFilter->setStatusBar(statusbar);

        retranslateUi(ScreenFilter);

        QMetaObject::connectSlotsByName(ScreenFilter);
    } // setupUi

    void retranslateUi(QMainWindow *ScreenFilter)
    {
        ScreenFilter->setWindowTitle(QCoreApplication::translate("ScreenFilter", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("ScreenFilter", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScreenFilter: public Ui_ScreenFilter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENFILTER_H
