#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Logger logger("Main");
    logger.log("APPLICATION START", Logger::INFO, false);
    w.show();
    return a.exec();
}
