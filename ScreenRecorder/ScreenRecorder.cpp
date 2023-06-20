#include "screenrecorder.h"
#include <QGuiApplication>
#include <opencv2/opencv.hpp>

ScreenRecorder::ScreenRecorder(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Screen Recorder");

    outputLabel = new QLabel(this);
    outputLabel->setAlignment(Qt::AlignCenter);

    startButton = new QPushButton("Start Recording", this);
    connect(startButton, SIGNAL(clicked()), this, SLOT(startRecording()));

    stopButton = new QPushButton("Stop Recording", this);
    stopButton->setEnabled(false);
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopRecording()));

    textlabel1 = new QLabel("Name");
    text1 = new QLineEdit;

    textlabel2 = new QLabel("email id");
    text2 = new QLineEdit;

    submitButton = new QPushButton("Submit", this);

    connect(submitButton, SIGNAL(clicked()), this, SLOT(getSensitiveInfo()));

    QFormLayout* formlayout = new QFormLayout;
    formlayout->addRow(textlabel1, text1);
    formlayout->addRow(textlabel2, text2);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addLayout(formlayout);
    layout->addWidget(outputLabel);
    layout->addWidget(submitButton);
    layout->addWidget(startButton);
    layout->addWidget(stopButton);

    resize(1280, 960);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateScreen()));

    if (tess.Init("./tessdata", "eng"))
    {
        std::cout << "OCRTesseract: Could not initialize tesseract." << std::endl;
    }

    tess.SetPageSegMode(tesseract::PageSegMode::PSM_AUTO);
    tess.SetVariable("save_best_choices", "T");
}

void ScreenRecorder::getSensitiveInfo()
{
    sensitiveInfo.push_back(text1->text().toStdString());
    sensitiveInfo.push_back(text2->text().toStdString());
    submitButton->setEnabled(false);
}

void ScreenRecorder::startRecording()
{
    screen = QGuiApplication::primaryScreen();
    startButton->setEnabled(false);
    stopButton->setEnabled(true);

    updateScreen();  

    timer->start(1000);  
}

void ScreenRecorder::stopRecording()
{
    timer->stop();
    startButton->setEnabled(true);
    stopButton->setEnabled(false);
}

QPixmap ScreenRecorder::convertPix(QPixmap& pixmap)
{
    QImage image = pixmap.toImage();
    cv::Mat mat(image.height(), image.width(), CV_8UC3, (cv::Scalar*)image.scanLine(0));

    tess.SetImage(mat.data, mat.cols, mat.rows, 4, 4 * mat.cols);
    tess.Recognize(0);

    tesseract::ResultIterator* ri = tess.GetIterator();
    tesseract::PageIteratorLevel level = tesseract::RIL_TEXTLINE;

    QPainter painter(&pixmap);
    QPen pen(Qt::red);
    QBrush brush(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(brush);

    if (ri != nullptr) 
    {
        do 
        {
            bool flag = false;
            int x1, y1, x2, y2;
            ri->BoundingBox(level, &x1, &y1, &x2, &y2);
            std::string text(ri->GetUTF8Text(level));

            for (const std::string& stext : sensitiveInfo)
            {
                if (text.find(stext) != std::string::npos)
                {
                    painter.drawRect(x1, y1, x2 - x1, y2 - y1);
                    qDebug() << stext << text;
                    flag = true;
                    break;
                }
            }
        } while (ri->Next(level));
    }

    painter.end();

    return pixmap;
}

void ScreenRecorder::updateScreen()
{
    if (!screen) return;

    QPixmap pixmap = screen->grabWindow(0);

    outputLabel->setPixmap(convertPix(pixmap).scaled(outputLabel->size(), Qt::KeepAspectRatio));
}

