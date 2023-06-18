#include <QApplication>
#include "screenrecorder.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ScreenRecorder screenRecorder;
    screenRecorder.show();

    return app.exec();
}

