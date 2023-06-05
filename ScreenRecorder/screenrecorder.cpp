#include "screenrecorder.h"
#include <QGuiApplication>

ScreenRecorder::ScreenRecorder(QWidget *parent)
: QWidget(parent)
{
    setWindowTitle("Screen Recorder");

    outputLabel = new QLabel(this);
    outputLabel->setAlignment(Qt::AlignCenter);

    startButton = new QPushButton("Start Recording", this);
    connect(startButton, SIGNAL(clicked()), this, SLOT(startRecording()));

    stopButton = new QPushButton("Stop Recording", this);
    stopButton->setEnabled(false);
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopRecording()));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(outputLabel);
    layout->addWidget(startButton);
    layout->addWidget(stopButton);

    resize(640, 480);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateScreen()));
}

void ScreenRecorder::startRecording()
{
    screen = QGuiApplication::primaryScreen();
    startButton->setEnabled(false);
    stopButton->setEnabled(true);

    updateScreen();  // Initial update

    timer->start(100);  // Update every 100 milliseconds
}

void ScreenRecorder::stopRecording()
{
    timer->stop();
    startButton->setEnabled(true);
    stopButton->setEnabled(false);
}

void ScreenRecorder::updateScreen()
{
    if (!screen) return;

    QPixmap pixmap = screen->grabWindow(0);  // Capture the whole screen
    outputLabel->setPixmap(pixmap.scaled(outputLabel->size(), Qt::KeepAspectRatio));
}
