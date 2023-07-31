#include <QApplication>
#include "screenrecorder.h"
#include "QtWidgetsClass.h"
#include "modeselection.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //ScreenRecorder screenRecorder;
    //screenRecorder.show();

    //QtWidgetsClass configWindow;
    //configWindow.show();

    ModeSelection w;
    w.show();

    return app.exec();
}

