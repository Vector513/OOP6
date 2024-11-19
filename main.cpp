#include "mainwindow.h"
#include "tcpClient.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    TcpClient tcpClient;
    QApplication a(argc, argv);
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "OOP4_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w(&tcpClient);

    w.show();
    return a.exec();
}
