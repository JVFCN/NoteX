#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QApplication>
#include <QtQml>
#include "texteditorfunc.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<TextEditorFunc>("MyCppFunc", 1 , 0 , "TextEditor");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
