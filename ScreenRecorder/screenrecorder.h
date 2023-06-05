#ifndef SCREENRECORDER_H
#define SCREENRECORDER_H

#include <QtWidgets>
#include <QScreen>
#include <QFrame>
#include <QPushButton>
#include <QTimer>

class ScreenRecorder : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenRecorder(QWidget *parent = nullptr);
private slots:
    void startRecording();
    void stopRecording();
    void updateScreen();
private:
    QScreen *screen;
    QLabel *outputLabel;
    QPushButton *startButton;
    QPushButton *stopButton;
    QTimer *timer;
};


#endif // SCREENRECORDER_H
