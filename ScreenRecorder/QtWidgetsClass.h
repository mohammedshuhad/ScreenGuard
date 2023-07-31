#ifndef QTWIDGETCLASS_H
#define QTWIDGETCLASS_H

#include <QtWidgets>
#include <QScreen>
#include <QFrame>
#include <QPushButton>

//#include "ui_QtWidgetsClass.h"

class QtWidgetsClass : public QWidget
{
	Q_OBJECT

public:
	QtWidgetsClass(QWidget *parent = nullptr);
	~QtWidgetsClass();
private slots:
	void addHorizontalform();
	void submitConfig();

private:
	QLabel* outputLabel;

	QPushButton* addButton;
	QPushButton* submitButton;

	QLineEdit* text;

	//Ui::QtWidgetsClassClass ui;
};

#endif