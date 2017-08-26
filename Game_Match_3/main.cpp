#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <logic.h>


int main(int argc, char *argv[])
{
    QApplication            app(argc, argv);
    QQmlApplicationEngine   engine;
    Logic                   logic;

    engine.rootContext()->setContextProperty("logic", &logic);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();

}
