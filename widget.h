
#ifndef WIDGET_H
#define WIDGET_H

#include "json.hpp"

#include <vector>
#include <fstream>

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
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCloseEvent>
#include <QTextCursor>

using json = nlohmann::json;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT
public: // Setting QWidgets
    QLabel *settingLabel;
    QVBoxLayout *qVBlayout_setting;
    QPushButton *btn_checkUpdates;

public: // Main QWidgets
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QLabel *label_openFile;
    QLabel *label_Welcome;
    QPlainTextEdit *textEdit_plain_main;
    QLabel *label_FileSize;
    QPushButton *setting_btn;
//    QLabel *label_line_number;
//    QLabel *label_column_number;

    QWidget *setting_widget;

    QHBoxLayout *layout;

    QSystemTrayIcon *QSTI;
    QMenu* trayMenu = new QMenu;
    QAction* quitAction = new QAction("退出", trayMenu);

    QShortcut *shortcut_save;
    QShortcut *shortcut_open;

    QString readFileData(QString FilePath);
    QString getFileSize(QString FilePath);
    QString readJsonFile(const QString FilePath, const QString key);
    bool saveFile(QString FilePath, QString FileData);
    bool openFile();

    bool onlineDetectionUpdate();
    int compareVersion(QString VersionCode_1, QString VersionCode_2);

public slots:
    void saveFile_slot();
    void setting_buttton_clicked();
    void setting_closed();
//    void line_number_show();

private:
    Ui::Widget *ui;
    QString fileName;
    bool settingOpened = false;
    std::string const jsonURL = "https://raw.githubusercontent.com/JVFCN/NoteX.io/main/OnlineUpdata/UpdataInfo.json";
    std::string configPath = __argv[0];
    std::string curlPath = __argv[0];
//    QTextCursor plainTextCursor;

protected:
    //将matlab窗口设置为随着窗口变化而变化
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual bool eventFilter(QObject* obj, QEvent* event) override;
    void closeEvent(QCloseEvent *event) override;

    // 拖动进入事件
    void dragEnterEvent(QDragEnterEvent *event);
    // 放下事件
    void dropEvent(QDropEvent *event);
};
class setting : public QWidget
{
public:

};
#endif // WIDGET_H
