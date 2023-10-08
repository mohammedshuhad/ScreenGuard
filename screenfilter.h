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
#include <future>
#include <thread>
#include <chrono>
#include <memory>

#include <windows.h>
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
    void getFieldEntries(std::vector<std::string> &entries, bool& secondary);
signals:
    void backButtonClicked();
private slots:
    void on_pushButton_clicked();
    void ocrUpdateScreen();
private:
    Ui::ScreenFilter *ui;
    std::vector<std::string> mEntries;
    QScreen* mscreen;
    QTimer* mOcrTimer;
    tesseract::TessBaseAPI mtess;

    void paintBoxes(QPixmap& pixmap, std::vector<QRect>& boxes);

    QMutex mutex;
    int mFrameCount;
    bool mSecondary;
    bool mInputsReceived;

    std::shared_ptr<ocrData> prevOcr;
    std::shared_ptr<ocrData> currOcr;

    void cascadeOCR();
    bool isSimilar(std::string x, std::string  y);
};

#endif // SCREENFILTER_H
