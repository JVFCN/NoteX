
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

    //main MenuBar
//    QMenuBar *menuBar_main;
    //file Menu
    QMenu *fileMenu;
    //Action at File Menu
    QAction *openFile;



    QString readFileData(QString FilePath);

private:
    Ui::Widget *ui;

protected:
    //将matlab窗口设置为随着窗口变化而变化
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual bool eventFilter(QObject* obj, QEvent* event) override;
};

#endif // WIDGET_H
