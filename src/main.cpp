
#include <QApplication>
#include <QTranslator>
#include <QSettings>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ipcalculator.h"
#include "utilities.h"
#include "iptablemodel.h"


int main(int argc, char *argv[])
{
    QApplication app {argc, argv};
    QCoreApplication::setApplicationName("cm.danofred.Ip-Tools");
    QCoreApplication::setOrganizationName("HarpTutos");
    QCoreApplication::setOrganizationDomain("cm.danofred.HarpTutos");

    QQmlApplicationEngine engine;
    QTranslator translator;
    QQmlContext * context = nullptr;
    QSettings setting = QSettings(QSettings::UserScope);
    Utils utils = Utils(&setting);

    auto language = setting.value("LANG", QVariant("ENGLISH")).toString();
    if(language.compare("ENGLISH") != 0) {

        if(translator.load("fr_FR", ":/i18n"))
            qDebug() << "[+] Translation Loaded";
        else
            qDebug() << "[-] Translation not Loaded";
        if(QCoreApplication::installTranslator(&translator))
            qDebug() << "[+] Launched in French";
        else
            qDebug() << "[-] Couldn't install the translator";

    } else {
        qDebug() << "[+] Running App without Translator";
    }

    qmlRegisterType<IpCalculator>("IpCalculator", 1, 0, "IpCalculator");
    qmlRegisterType<IpTableModel>("IpTableModel", 1, 0, "IpTableModel");

    const QUrl url(u"qrc:/ui/Main.qml"_qs);
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
