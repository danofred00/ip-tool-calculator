
#include <QApplication>
#include <QDebug>

#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app {argc, argv};

    //QApplication::setStyle(&style);

    //qDebug() << QStyleFactory::keys();

    MainWindow window;
    window.setWindowTitle(QCoreApplication::tr("Ip-Tools"));
    window.show();

    return app.exec();
}
