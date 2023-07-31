#include "QtWidgetsClass.h"

QtWidgetsClass::QtWidgetsClass(QWidget *parent)
	: QWidget(parent)
{
	setWindowTitle("Configuration window");

	outputLabel = new QLabel("Configure Sensitive Information here");
	outputLabel->setAlignment(Qt::AlignCenter);

	addButton = new QPushButton("Add", this);
	connect(addButton, SIGNAL(clicked()), this, SLOT(addHorizontalform()));

	submitButton = new QPushButton("Submit", this);
	connect(submitButton, SIGNAL(clicked()), this , SLOT(submitConfig()));

	text = new QLineEdit;

	QHBoxLayout* hlayout = new QHBoxLayout(this);
	hlayout->addWidget(addButton);
	hlayout->addWidget(submitButton);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(text);
	layout->addLayout(hlayout);

	resize(1280, 960);
}


void QtWidgetsClass::addHorizontalform()
{
	QHBoxLayout* hlayout = new QHBoxLayout(this);
	hlayout->addWidget(text);
	hlayout->addWidget(addButton);
	hlayout->addWidget(submitButton);
}

void QtWidgetsClass::submitConfig()
{}

QtWidgetsClass::~QtWidgetsClass()
{}
