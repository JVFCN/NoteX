
#include "widget.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationDomain("https://jvfcn.github.io/NoteX.io/");
    a.setApplicationName("NoteX");
    a.setWindowIcon(QIcon("://res/icon.ico"));
    Widget w;
    w.setStyleSheet("background-color:#FAFAFA;");
    w.show();
    return a.exec();
}
