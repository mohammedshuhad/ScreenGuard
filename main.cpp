#include <QApplication>
#include "InfoConfig.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    InfoConfig w;
    w.show();

    return app.exec();
}

