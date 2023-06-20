#ifndef SCREENRECORDER_H
#define SCREENRECORDER_H

#include <QtWidgets>
#include <QScreen>
#include <QFrame>
#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <leptonica/allheaders.h> 
#include <tesseract/baseapi.h> 
#include <opencv2/opencv.hpp>

class ScreenRecorder : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenRecorder(QWidget* parent = nullptr);
private slots:
    void startRecording();
    void stopRecording();
    void updateScreen();
    void getSensitiveInfo();
private:
    QScreen* screen;

    QLabel* outputLabel;

    QLabel* textlabel1;
    QLineEdit* text1;

    QLabel* textlabel2;
    QLineEdit* text2;

    QPushButton* submitButton;
    QPushButton* startButton;
    QPushButton* stopButton;

    QTimer* timer;

    tesseract::TessBaseAPI tess;

    QPixmap convertPix(QPixmap& pixmap);

    std::vector<std::string> sensitiveInfo;
};


#endif // SCREENRECORDER_H
