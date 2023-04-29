
#ifndef WIDGET_H
#define WIDGET_H

#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QDialog>
#include <QTextEdit>
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMenuBar>
#include <QMenu>
#include <QPlainTextEdit>
#include <QAction>
#include <QShortcut>
#include <QUrl>
#include <QDragEnterEvent>
#include <QSystemTrayIcon>
#include <QMimeData>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QLabel *label_openFile;
    QLabel *label_Welcome;
    QPlainTextEdit *textEdit_plain_main;

    QSystemTrayIcon *QSTI;
    QMenu* trayMenu = new QMenu;
    QAction* quitAction = new QAction("退出", trayMenu);

    QShortcut *shortcut_save;
    QShortcut *shortcut_open;

    QString readFileData(QString FilePath);
    bool saveFile(QString FilePath, QString FileData);
    bool openFile();

public slots:
    void saveFile_slot();

private:
    Ui::Widget *ui;
    QString fileName;
protected:
    //将matlab窗口设置为随着窗口变化而变化
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual bool eventFilter(QObject* obj, QEvent* event) override;

    // 拖动进入事件
    void dragEnterEvent(QDragEnterEvent *event);
    // 放下事件
    void dropEvent(QDropEvent *event);
};

#endif // WIDGET_H
