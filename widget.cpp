
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    textEdit_plain_main = new QPlainTextEdit(this);
    textEdit_plain_main->setFont(QFont("", 12));
    textEdit_plain_main->setStyleSheet("QScrollBar:vertical { width: 8px; background: rgba(0,0,0,0%); margin: 0px,0px,0px,0px; padding-top: 9px; padding-bottom: 9px; } QScrollBar::handle:vertical { width: 8px; background: rgba(0,0,0,25%); border-radius: 4px; min-height: 20; } QScrollBar::handle:vertical:hover { width: 8px; background: rgba(0,0,0,50%); border-radius: 4px; min-height: 20; }");
    textEdit_plain_main->setVisible(false);

    label_FileSize = new QLabel(getFileSize(fileName) ,this);
    label_FileSize->setFont(QFont("", 12));
    label_FileSize->setStyleSheet("background-color: rgba(0,0,0,0)");

    setting_btn = new QPushButton("设置", this);
    setting_btn->setStyleSheet("QPushButton {background-color: #ffffff; border: 1px solid #dcdfe6; padding: 10px; border-radius: 5px;}QPushButton:hover {background-color: #ecf5ff; color: #409eff;}QPushButton:pressed, QPushButton:checked {border: 1px solid #3a8ee6; color: #409eff;}#button3 {border-radius: 20px;}");
    connect(setting_btn, &QPushButton::clicked, this, setting_buttton_clicked);

    layout = new QVBoxLayout;
    layout->addWidget(label_FileSize, 0, Qt::AlignLeft | Qt::AlignBottom);
    layout->addWidget(setting_btn, 0, Qt::AlignRight | Qt::AlignBottom);
    this->setLayout(layout);

    label_Welcome = new QLabel(tr("NoteX: 文本编辑解决方案"), this);
    label_Welcome->setStyleSheet("color:rgb(152, 152, 152);");
    label_Welcome->setFont(QFont("",30));
    label_Welcome->setGeometry(50, 50, 600, 80);

    label_openFile = new QLabel(tr("打开文件"), this);
    label_openFile->setStyleSheet("color:#94A7B0;");
    label_openFile->setFont(QFont("", 20));
    label_openFile->installEventFilter(this);

    QSTI = new QSystemTrayIcon;
    QSTI->setIcon(QIcon("qrc:/res/icon.ico"));
    trayMenu->addAction(quitAction);
    QSTI->setContextMenu(trayMenu);
    QSTI->show();

    shortcut_save = new QShortcut(QKeySequence::Save, this);
    connect(shortcut_save, &QShortcut::activated, this, saveFile_slot);

    shortcut_open = new QShortcut(QKeySequence::Open, this);
    connect(shortcut_open, &QShortcut::activated, this, openFile);
}

Widget::~Widget()
{
    delete ui;
}

QString Widget::readFileData(QString FilePath)
{
    std::string filePath_stdString = FilePath.toStdString();
    std::ifstream fin(filePath_stdString, std::ios::binary);

//    clock_t start = clock();
    std::vector<char> buf(fin.seekg(0, std::ios::end).tellg());
    fin.seekg(0, std::ios::beg).read(&buf[0], static_cast<std::streamsize>(buf.size()));
    fin.close();
//    clock_t end = clock();
//    qDebug() << "time : " << ((double)end - start) / CLOCKS_PER_SEC << "s\n";
    label_FileSize->setText(getFileSize(fileName));

    std::string str(buf.begin(), buf.end());
    return QString::fromStdString(str);
}

QString Widget::getFileSize(QString FilePath)
{
    if (FilePath == NULL) {
        return NULL;
    }
    QFile file(FilePath);
    long fileSize_long;
    if (file.open(QIODevice::ReadOnly)) {
        fileSize_long = file.size();
        file.close();
    }
    if (fileSize_long > 1024 * 1024 * 1024) {
        return QString::number(fileSize_long / 1024 / 1024 / 1024) + "GB";
    }
    if (fileSize_long > 1024 * 1024) {
        return QString::number(fileSize_long / 1024 / 1024) + "MB";
    }
    if (fileSize_long > 1024) {
        return QString::number(fileSize_long / 1024) + "KB";
    } else {
        return QString::number(fileSize_long) + "B";
    }
}

bool Widget::saveFile(QString FilePath, QString FileData)
{
    if (FilePath == NULL) {
//        qDebug() << "NO";
        return false;
    }
    QFile file(FilePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(FileData.toUtf8());
    file.close();
//    qDebug() << "Save OK";
    label_FileSize->setText(getFileSize(fileName));
    return true;
}

bool Widget::openFile()
{
    fileName = QFileDialog::getOpenFileName(this, "打开文件", "", "* (*)");
    if (fileName == NULL) {
        return false;
    }
    if (textEdit_plain_main->isVisible() != true) {
        textEdit_plain_main->setVisible(true);
        if (label_openFile->isVisible() == true && label_Welcome->isVisible() == true) {
            label_openFile->setVisible(false);
            delete label_Welcome;
        }
    }
    textEdit_plain_main->setPlainText(readFileData(fileName));
    return true;
}

bool Widget::onlineDetectionUpdate()
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply* reply = manager->get(QNetworkRequest(QUrl("https://github.com/JVFCN/NoteX.io/blob/main/OnlineUpdata/UpdataInfo.json")));

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            return false;
        }

        QByteArray jsonData = reply->readAll();
        qDebug() << jsonData;
    });
}

int Widget::compareVersion(QString VersionCode_1, QString VersionCode_2)
{
    std::string VersionCode_1_stdString = VersionCode_1.toStdString();
    std::string VersionCode_2_stdString = VersionCode_2.toStdString();

    int i = 0, j = 0;
    int n1 = VersionCode_1_stdString.size(), n2 = VersionCode_2_stdString.size();
    int num1 = 0, num2 = 0;
    while (i < n1 || j < n2) {
        while (i < n1 && VersionCode_1_stdString[i] != '.') {
            num1 = num1 * 10 + (VersionCode_1_stdString[i] - '0');
            i++;
        }
        while (j < n2 && VersionCode_2_stdString[j] != '.') {
        num2 = num2 * 10 + (VersionCode_2_stdString[j] - '0');
        j++;
        }
        if (num1 > num2) {
        return 1;
        }
        else if (num1 < num2) {
        return -1;
        }
        num1 = 0;
        num2 = 0;
        i++;
        j++;
    }
    return 0;
}

void Widget::saveFile_slot()
{
//    qDebug() << "slot\n" << "fileName:" << fileName;
    saveFile(fileName, textEdit_plain_main->toPlainText());
}

void Widget::setting_buttton_clicked()
{
    settingOpened = true;
    qDebug() << "Clicked";
    setting_widget = new QWidget();
    setting_widget->setWindowTitle("Setting");
    setting_widget->setGeometry(500,500,1000,700);

    settingLabel = new QLabel("hello", setting_widget);

    setting_widget->show();
}

void Widget::resizeEvent(QResizeEvent *event)
{
//    qDebug() << "宽:" << this->width() << "    高:" << this->height();
    if (label_openFile->parent() != NULL) {
        label_openFile->setGeometry(this->width() / 2 - 70, this->height() / 2, 150, 100);
    }
    textEdit_plain_main->setGeometry(0,0, this->width(), this->height() - 45);
}

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (qobject_cast<QLabel*>(obj)) {
//            qDebug() << "点击";

            fileName = QFileDialog::getOpenFileName(this, "打开文件", "" , "* (*)");
            if (fileName == NULL) {
                return false;
            }
//            qDebug() << fileName;
            label_openFile->setVisible(false);
            delete label_Welcome;

            textEdit_plain_main->setVisible(true);
            textEdit_plain_main->setPlainText(readFileData(fileName));

//            qDebug() << textEdit_main->size() << "\n" << textEdit_main->isVisible();
//            label_openFile->setVisible(false);
//            label_Welcome->setVisible(false);
            return true;
        }
    }
    return false;
}

void Widget::closeEvent(QCloseEvent *event)
{
    qDebug() << "Closed";
    delete setting_widget;
}

// 拖动进入事件
void Widget::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()) {event->acceptProposedAction();}
    else {event->ignore();}
}

// 放下事件
void Widget::dropEvent(QDropEvent *event)
{
    const QMimeData *m = event->mimeData();
    // 如果数据中包含URL
    if(m->hasUrls()){
        // 获取URL列表
        QList<QUrl> urlList = m->urls();
        // 将其中第一个URL表示为本地文件路径
        QString fileName_Drop = urlList.at(0).toLocalFile();
        // 如果文件路径不为空
        if(!fileName_Drop.isEmpty()){
            //  转为char*
            QByteArray qByteArrary = fileName_Drop.toLatin1();
            char* filePath = qByteArrary.data();
//            qDebug() << filePath;
            if (textEdit_plain_main->isVisible() != true) {
                textEdit_plain_main->setVisible(true);
                if (label_openFile->isVisible() == true && label_Welcome->isVisible() == true) {
                    label_openFile->setVisible(false);
                    delete label_Welcome;
                }
            }
            fileName = fileName_Drop;
            textEdit_plain_main->setPlainText(readFileData(fileName_Drop));
        }
    }
}
