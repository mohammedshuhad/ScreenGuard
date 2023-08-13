#ifndef SCREENFILTER_H
#define SCREENFILTER_H
#include <QtWidgets>
#include <QScreen>
#include <QFrame>
#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <QMainWindow>

#include <leptonica/allheaders.h> 
#include <tesseract/baseapi.h> 
#include <opencv2/opencv.hpp>

#include <locale>
#include <algorithm>
#include <map>

#include "WindowTracker.h"
#include "SensitivityModule.h"


namespace Ui {
class ScreenFilter;
}

class ScreenFilter : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScreenFilter(QWidget *parent = nullptr);
    ~ScreenFilter();
    void getFieldEntries(std::vector<std::string> &entries);
signals:
    void backButtonClicked();
private slots:
    void on_pushButton_clicked();
    void ocrUpdateScreen();
    void winUpdateScreen();
private:
    Ui::ScreenFilter *ui;
    std::vector<std::string> mEntries;
    QScreen* mscreen;
    QTimer* mOcrTimer;
    QTimer* mWinTimer;
    tesseract::TessBaseAPI mtess;
    //QPixmap convertPix(QPixmap& pixmap);

    SensitivityModule mSensitivityModule;
    //void ocrInit();
    void runOcr(cv::Mat& mat);
    void paintBoxes(QPixmap& pixmap);

    QMutex mutex;
    int mFrameCount;
};

#endif // SCREENFILTER_H
