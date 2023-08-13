#include "ScreenFilter.h"
#include "ui_screenfilter.h"

ScreenFilter::ScreenFilter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScreenFilter)
{
    ui->setupUi(this);

    mscreen = QGuiApplication::primaryScreen();

    mFrameCount = 0;

    if (mtess.Init("./tessdata", "eng"))
    {
        std::cout << "OCRTesseract: Could not initialize tesseract." << std::endl;
    }

    mtess.SetPageSegMode(tesseract::PageSegMode::PSM_AUTO);
    mtess.SetVariable("save_best_choices", "T");

    mOcrTimer = new QTimer(this);
    mOcrTimer->start(1000);
    connect(mOcrTimer, SIGNAL(timeout()), this, SLOT(ocrUpdateScreen()));

    //mWinTimer = new QTimer(this);
    //mWinTimer->start(1000);
    //connect(mWinTimer, SIGNAL(timeout()), this, SLOT(winUpdateScreen()));
}

void ScreenFilter::getFieldEntries(std::vector<std::string>& entries)
{
    for (auto& entry : entries)
    {
        mEntries.push_back(entry);
        //qDebug() << entry << "\n";
    }
    mFrameCount = 0;
}

bool isSimilar(std::string x, std::string  y)
{
    bool flag = false;
    int i, j, pxy = 1, pgap = 1;

    int m = x.length();
    int n = y.length();

    int** dp = new int* [n + m + 1];
    for (int i = 0; i < n + m + 1; ++i)
        dp[i] = new int[n + m + 1];

    for (i = 0; i <= (n + m); i++)
    {
        dp[i][0] = i * pgap;
        dp[0][i] = i * pgap;
    }

    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (x[i - 1] == y[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = std::min({ dp[i - 1][j - 1] + pxy ,
                                dp[i - 1][j] + pgap    ,
                                dp[i][j - 1] + pgap });
            }
        }
    }

    if (dp[m][n] < 5) flag = true;

    for (int i = 0; i < n + m + 1; ++i) {
        delete[] dp[i];
    }
    delete[] dp;

    return flag;
}

void ScreenFilter::runOcr(cv::Mat& mat)
{
    mtess.SetImage(mat.data, mat.cols, mat.rows, 4, 4 * mat.cols);
    mSensitivityModule.mAllBoxes.clear();
    mtess.Recognize(0);

    tesseract::ResultIterator* ri = mtess.GetIterator();

    if (ri != nullptr && ri->GetUTF8Text(tesseract::RIL_TEXTLINE) != nullptr && !mEntries.empty())
    {
        do
        {
            int x1, y1, x2, y2;
            ri->BoundingBox(tesseract::RIL_TEXTLINE, &x1, &y1, &x2, &y2);
            std::string text(ri->GetUTF8Text(tesseract::RIL_TEXTLINE));
            if (!text.empty())
            {
                text.erase(std::remove_if(text.begin(), text.end(), std::bind(std::isspace < char >,
                    std::placeholders::_1,
                    std::locale::classic())),
                    text.end());
            }
            for (const std::string& stext : mEntries)
            {
                if (isSimilar(stext, text))
                {
                    mSensitivityModule.mAllBoxes.emplace_back(x1, y1, x2 - x1, y2 - y1);
                }
            }
        } while (ri->Next(tesseract::RIL_TEXTLINE));
    }
    delete ri; 
}
void ScreenFilter::paintBoxes(QPixmap& pixmap)
{
    QPainter painter(&pixmap);
    QPen pen(Qt::red);
    QBrush brush(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(brush);

    for (auto& box : mSensitivityModule.mAllBoxes)
    {
        painter.drawRect(box);
    }

    painter.end();
}

void ScreenFilter::ocrUpdateScreen()
{
    if (!mscreen) return;
    QPixmap pixmap = mscreen->grabWindow(0);
    QImage image = pixmap.toImage();
    cv::Mat mat(image.height(), image.width(), CV_8UC3, (cv::Scalar*)image.scanLine(0));
    runOcr(mat);
    paintBoxes(pixmap);
    ui->label->setPixmap(pixmap);
    mSensitivityModule.update();
    //if (mFrameCount % 4 == 0)
    //{
    //    cv::Mat mat(image.height(), image.width(), CV_8UC3, (cv::Scalar*)image.scanLine(0));
    //    runOcr(mat);
    //    paintBoxes(pixmap);
    //    ui->label->setPixmap(pixmap);
    //    mSensitivityModule.update();
    //}
    //else
    //{
    //    QPainter painter(&pixmap);
    //    QPen pen(Qt::red);
    //    QBrush brush(Qt::black);
    //    pen.setWidth(2);
    //    painter.setPen(pen);
    //    painter.setBrush(brush);
    //    painter.drawRect(20, 20, 20, 20);
    //    painter.end();

    //    mSensitivityModule.updateRelative();
    //    paintBoxes(pixmap);
    //    ui->label->setPixmap(pixmap);
    //}
    //mFrameCount++;
}

void ScreenFilter::winUpdateScreen()
{
    mutex.lock();
    if (!mscreen) return;
    QPixmap pixmap = mscreen->grabWindow(0);
    QImage image = pixmap.toImage();
    //cv::Mat mat(image.height(), image.width(), CV_8UC3, (cv::Scalar*)image.scanLine(0));
    //runOcr(mat);

    QPainter painter(&pixmap);
    QPen pen(Qt::red);
    QBrush brush(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(20, 20, 20, 20);
    painter.end();

    mSensitivityModule.updateRelative();
    paintBoxes(pixmap);
    ui->label->setPixmap(pixmap);
    mutex.unlock();
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

//QPixmap ScreenFilter::convertPix(QPixmap& pixmap)
//{
//    QImage image = pixmap.toImage();
//    cv::Mat mat(image.height(), image.width(), CV_8UC3, (cv::Scalar*)image.scanLine(0));
//
//    mtess.SetImage(mat.data, mat.cols, mat.rows, 4, 4 * mat.cols);
//    mtess.Recognize(0);
//
//    tesseract::ResultIterator* ri = mtess.GetIterator();
//    tesseract::PageIteratorLevel level = tesseract::RIL_TEXTLINE;
//
//    QPainter painter(&pixmap);
//    QPen pen(Qt::red);
//    QBrush brush(Qt::black);
//    pen.setWidth(2);
//    painter.setPen(pen);
//    painter.setBrush(brush);
//
//    if (ri != nullptr && !mEntries.empty())
//    {
//        do
//        {
//            int x1, y1, x2, y2;
//            ri->BoundingBox(level, &x1, &y1, &x2, &y2);
//            std::string text(ri->GetUTF8Text(level));
//            if (!text.empty())
//            {
//                text.erase(std::remove_if(text.begin(), text.end(), std::bind(std::isspace < char >,
//                    std::placeholders::_1,
//                    std::locale::classic())),
//                    text.end());
//            }
//            for (const std::string& stext : mEntries)
//            {
//                if(isSimilar(stext, text))
//                {
//                    painter.drawRect(x1, y1, x2 - x1, y2 - y1);
//                    //break;
//                }
//            }
//        } while (ri->Next(level));
//    }
//
//    painter.end();
//
//    return pixmap;
//}

    //ui->label->setPixmap(convertPix(pixmap));
    //outputLabel->setPixmap(convertPix(pixmap).scaled(outputLabel->size(), Qt::KeepAspectRatio));