
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ipcalculator.h"
#include "utilities.h"
#include "iptablemodel.h"

int main(int argc, char *argv[])
{
    QApplication app {argc, argv};

    //QApplication::setStyle(&style);

    //qDebug() << QStyleFactory::keys();

    Utils utils = Utils();

    QQmlApplicationEngine engine;
    QQmlContext * context = nullptr;

    qmlRegisterType<IpCalculator>("IpCalculator", 1, 0, "IpCalculator");
    qmlRegisterType<IpTableModel>("IpTableModel", 1, 0, "IpTableModel");

    const QUrl url(u"qrc:/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    context = engine.rootContext();
    context->setContextProperty("Utils", &utils);

//    MainWindow window;
//    window.setWindowTitle(QCoreApplication::tr("Ip-Tools"));
//    window.show();

    return app.exec();
}
