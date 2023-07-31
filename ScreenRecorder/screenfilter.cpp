#include "screenfilter.h"
#include "ui_screenfilter.h"

ScreenFilter::ScreenFilter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScreenFilter)
{
    ui->setupUi(this);

    mscreen = QGuiApplication::primaryScreen();

    mtimer = new QTimer(this);
    mtimer->start(1000);
    connect(mtimer, SIGNAL(timeout()), this, SLOT(updateScreen()));

    if (mtess.Init("./tessdata", "eng"))
    {
        std::cout << "OCRTesseract: Could not initialize tesseract." << std::endl;
    }

    mtess.SetPageSegMode(tesseract::PageSegMode::PSM_AUTO);
    mtess.SetVariable("save_best_choices", "T");
}
void ScreenFilter::getFieldEntries(std::vector<std::string>& entries)
{
    for (auto& entry : entries)
    {
        mEntries.push_back(entry);
        qDebug() << entry << "\n";
    }
}

QPixmap ScreenFilter::convertPix(QPixmap& pixmap)
{
    QImage image = pixmap.toImage();
    cv::Mat mat(image.height(), image.width(), CV_8UC3, (cv::Scalar*)image.scanLine(0));

    mtess.SetImage(mat.data, mat.cols, mat.rows, 4, 4 * mat.cols);
    mtess.Recognize(0);

    tesseract::ResultIterator* ri = mtess.GetIterator();
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

            for (const std::string& stext : mEntries)
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

void ScreenFilter::updateScreen()
{
    if (!mscreen) return;

    QPixmap pixmap = mscreen->grabWindow(0);
    ui->label->setPixmap(convertPix(pixmap));
    //outputLabel->setPixmap(convertPix(pixmap).scaled(outputLabel->size(), Qt::KeepAspectRatio));
}

ScreenFilter::~ScreenFilter()
{
    delete ui;
}

void ScreenFilter::on_pushButton_clicked()
{
    emit backButtonClicked();
    hide();
}

