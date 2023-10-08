#include "ScreenFilter.h"
#include "ui_screenfilter.h"
#include <chrono>

ScreenFilter::ScreenFilter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScreenFilter)
{
    ui->setupUi(this);

    mscreen = QGuiApplication::primaryScreen();

    mFrameCount = 0;
    mSecondary = false;
    mInputsReceived = false;

    if (mtess.Init("./tessdata", "eng"))
    {
        std::cout << "OCRTesseract: Could not initialize tesseract." << std::endl;
    }

    mtess.SetPageSegMode(tesseract::PageSegMode::PSM_AUTO);
    mtess.SetVariable("save_best_choices", "T");

    mOcrTimer = new QTimer(this);
    mOcrTimer->start(1000);
    connect(mOcrTimer, SIGNAL(timeout()), this, SLOT(ocrUpdateScreen()));
    prevOcr = std::make_shared<ocrData>(mSecondary);

}
void ScreenFilter::getFieldEntries(std::vector<std::string>& entries, bool& secondary)
{
    for (auto& entry : entries)
    {
        mEntries.push_back(entry);
    }
    mFrameCount = 0;
    mSecondary = secondary;
    mInputsReceived = true;
    if (secondary)
    {
        QList<QScreen*> screens = QGuiApplication::screens();
        mscreen = screens.at(1);
    }
    else
    {
        mscreen = QGuiApplication::primaryScreen();
    }
    prevOcr->secondary = mSecondary;
    cascadeOCR();
}
void ScreenFilter::cascadeOCR()
{
    //mutex.lock();
    if (!mscreen) return;
    if (!prevOcr->contains && mInputsReceived)
    {
        using namespace std::chrono_literals;
        qDebug() << "Inside Cascade";
        QPixmap pixmap = mscreen->grabWindow(0);
        if (pixmap.isNull()) {
            qDebug() << "Error capturing screenshot";
        }
        else {
            qDebug() << "Screenshot captured successfully";
        }
        QImage image = pixmap.toImage();
        cv::Mat mat(image.height(), image.width(), CV_8UC3, (cv::Scalar*)image.scanLine(0));
        mtess.SetImage(mat.data, mat.cols, mat.rows, 4, 4 * mat.cols);
        mtess.Recognize(0);
        tesseract::ResultIterator* ri = mtess.GetIterator();
        bool flag = false;
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
                    qDebug() << "Cascade Text: " << text;
                }
                for (const std::string& stext : mEntries)
                {
                    if (isSimilar(stext, text))
                    {
                        prevOcr->uBoxes.emplace_back(x1, y1, x2 - x1, y2 - y1);
                        flag = true;
                        
                    }
                }
            } while (ri->Next(tesseract::RIL_TEXTLINE));
        }
        prevOcr->confidence = 0;
        prevOcr->cycleCount++;
        prevOcr->contains = flag;
        if (flag)
        {
            prevOcr->clearAssociation();
            std::vector<winData> tempWinList = SensitivityModule::Get().getWinList(true, mSecondary);
            for (auto& winTemp : tempWinList)
            {
                if (!prevOcr->present(winTemp.hwnd))
                {
                    prevOcr->association.push_back(std::make_shared<winAssociation>(winTemp));
                }
            }
            prevOcr->classify(); // should fill it in uBoxes as well
            paintBoxes(pixmap, prevOcr->uBoxes);
            std::this_thread::sleep_for(500ms);
            ui->label->setPixmap(pixmap);
            qDebug() << "Cascade Drawn\n";
        }
    }
    //mutex.unlock();
}

void ScreenFilter::ocrUpdateScreen()
{
    if (!mscreen) return;
    using namespace std::chrono_literals;
    if (prevOcr->contains)
    {
        //SensitivityModule::Get().update(mSecondary);
        currOcr.reset();
        //ocrData::getCurr().reset();
        currOcr = std::make_shared<ocrData>(mSecondary);
        currOcr->clearAssociation();
        auto future = std::async(std::launch::async, [&, this] 
            {
                mutex.lock();
                QPixmap pixmap = mscreen->grabWindow(0);
                mutex.unlock();
                QImage image = pixmap.toImage();
                cv::Mat mat(image.height(), image.width(), CV_8UC3, (cv::Scalar*)image.scanLine(0));
                mtess.SetImage(mat.data, mat.cols, mat.rows, 4, 4 * mat.cols);
                mtess.Recognize(0);
                tesseract::ResultIterator* ri = mtess.GetIterator();
                bool flag = false;
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

                            for (const std::string& stext : mEntries)
                            {
                                if (isSimilar(stext, text))
                                {
                                    currOcr->uBoxes.emplace_back(x1, y1, x2 - x1, y2 - y1);
                                    qDebug() << "Async Text : " << text;
                                    flag = true;
                                }
                            }
                        }
                    } while (ri->Next(tesseract::RIL_TEXTLINE));
                }
                currOcr->contains = flag;
                if(flag) paintBoxes(pixmap, currOcr->uBoxes);
                //qDebug() << "Async : painted boxes : " << currOcr.boxes.size() << "\n";
                //ui->label->setPixmap(pixmap);
                //currOcr.confidence = 0; 
                currOcr->cycleCount++;
                //currOcr.contains = flag;

                return flag;
            });

        auto status = future.wait_for(0ms);
        while (status != std::future_status::ready)
        {
            mutex.lock();
            QPixmap pixmap = mscreen->grabWindow(0);
            mutex.unlock();
            prevOcr->updatePosition();
            //SensitivityModule::Get().getList(mSecondary, boxes);
            qDebug() << "Relative Drawing\n";
            paintBoxes(pixmap, prevOcr->uBoxes);
            std::this_thread::sleep_for(500ms);
            ui->label->setPixmap(pixmap);
            status = future.wait_for(0ms);
        }

        if (status == std::future_status::ready)
        {
            if (future.get())
            {
                std::vector<winData> tempWinList = SensitivityModule::Get().getWinList(false, mSecondary);
                for (auto& winTemp : tempWinList)
                {
                    if (!currOcr->present(winTemp.hwnd))
                    {
                        currOcr->association.push_back(std::make_shared<winAssociation>(winTemp));
                    }
                }
                currOcr->classify();
                prevOcr.reset();
                prevOcr = std::make_shared<ocrData>(*currOcr);
            }
        }
    }
    else
    {
        std::this_thread::sleep_for(500ms);
        cascadeOCR();
    }
}

bool ScreenFilter::isSimilar(std::string x, std::string  y)
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

void ScreenFilter::paintBoxes(QPixmap& pixmap, std::vector<QRect>& boxes)
{
    QPainter painter(&pixmap);
    QPen pen(Qt::red);
    QBrush brush(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(brush);

    for (auto& box : boxes)
    {
        painter.drawRect(box);
        qDebug() << box << "\n";
    }

    painter.end();
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