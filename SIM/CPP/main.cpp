// main.cpp
#include <QApplication>
#include "wavecontrolwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    WaveControlWindow window;
    window.show();
    return app.exec();
}
