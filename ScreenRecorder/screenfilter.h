#ifndef SCREENFILTER_H
#define SCREENFILTER_H
#include <QtWidgets>
#include <QScreen>
#include <QFrame>
#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <leptonica/allheaders.h> 
#include <tesseract/baseapi.h> 
#include <opencv2/opencv.hpp>
#include <QMainWindow>

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
    void updateScreen();
private:
    Ui::ScreenFilter *ui;
    std::vector<std::string> mEntries;
    QScreen* mscreen;
    QTimer* mtimer;
    tesseract::TessBaseAPI mtess;
    QPixmap convertPix(QPixmap& pixmap);
};

#endif // SCREENFILTER_H
