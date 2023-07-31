/********************************************************************************
** Form generated from reading UI file 'modeselection.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODESELECTION_H
#define UI_MODESELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModeSelection
{
public:
    QFrame *frame;
    QLabel *label_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;

    void setupUi(QDialog *ModeSelection)
    {
        if (ModeSelection->objectName().isEmpty())
            ModeSelection->setObjectName("ModeSelection");
        ModeSelection->resize(540, 400);
        frame = new QFrame(ModeSelection);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(20, 10, 511, 261));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(190, 70, 131, 121));
        layoutWidget = new QWidget(ModeSelection);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(290, 350, 241, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout->addWidget(pushButton_2);

        layoutWidget1 = new QWidget(ModeSelection);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(20, 290, 511, 51));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        radioButton = new QRadioButton(layoutWidget1);
        radioButton->setObjectName("radioButton");

        horizontalLayout_2->addWidget(radioButton);

        radioButton_2 = new QRadioButton(layoutWidget1);
        radioButton_2->setObjectName("radioButton_2");

        horizontalLayout_2->addWidget(radioButton_2);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(ModeSelection);
        QObject::connect(pushButton_2, &QPushButton::clicked, ModeSelection, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(ModeSelection);
    } // setupUi

    void retranslateUi(QDialog *ModeSelection)
    {
        ModeSelection->setWindowTitle(QCoreApplication::translate("ModeSelection", "ModeSelection", nullptr));
        label_2->setText(QCoreApplication::translate("ModeSelection", "ScreenGuard Application", nullptr));
        pushButton->setText(QCoreApplication::translate("ModeSelection", "Next", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ModeSelection", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("ModeSelection", "Select Mode :", nullptr));
        radioButton->setText(QCoreApplication::translate("ModeSelection", "Specific Information Hiding", nullptr));
        radioButton_2->setText(QCoreApplication::translate("ModeSelection", "Message Hiding", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModeSelection: public Ui_ModeSelection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODESELECTION_H
