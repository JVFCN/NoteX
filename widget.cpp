
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    textEdit_plain_main = new QPlainTextEdit(this);
    textEdit_plain_main->setVisible(false);

    label_Welcome = new QLabel(tr("NoteX: 文本编辑解决方案"), this);
    label_Welcome->setStyleSheet("color:rgb(152, 152, 152);");
    label_Welcome->setFont(QFont("",30));
    label_Welcome->setGeometry(50, 50, 600, 80);

    label_openFile = new QLabel(tr("打开文件"), this);
    label_openFile->setStyleSheet("color:#94A7B0;");
    label_openFile->setFont(QFont("", 20));
    label_openFile->installEventFilter(this);

    shortcut_save = new QShortcut(QKeySequence::Save, this);
//    shortcut_save->setContext(Qt::);
    connect(shortcut_save, &QShortcut::activated, this, saveFile_slot);
}

Widget::~Widget()
{
    delete ui;
}

QString Widget::readFileData(QString FilePath)
{
    QFile file(FilePath);
    QString content;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "失败" << FilePath;
    }

    QTextStream in(&file);
    in.setCodec("UTF8");
    while (!in.atEnd()) {
        QString line = in.readLine(); // 读取一行文本
        content.append(line + "\n"); // 将文本追加到内容字符串中，加上换行符
    }
    file.close();
    return content;
}

bool Widget::saveFile(QString FilePath, QString FileData)
{
    if (FilePath == NULL) {
        qDebug() << "NO";
        return false;
    }
    QFile file(FilePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(FileData.toUtf8());
    file.close();
    qDebug() << "Save OK";
    return true;
}

void Widget::saveFile_slot()
{
    qDebug() << "slot";
    saveFile(fileName, textEdit_plain_main->toPlainText());
}

void Widget::resizeEvent(QResizeEvent *event)
{
    qDebug() << "宽:" << this->width() << "    高:" << this->height();
    if (label_openFile->parent() != NULL) {
        label_openFile->setGeometry(this->width() / 2 - 130, this->height() / 2, 150, 100);
    }
    textEdit_plain_main->setGeometry(0,0, this->width(), this->height());
}

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (qobject_cast<QLabel*>(obj)) {
            qDebug() << "点击";

            fileName = QFileDialog::getOpenFileName(this, "打开文件", "C:" , "* (*)");
            if (fileName == NULL) {
                return false;
            }
            qDebug() << fileName;
            label_openFile->setVisible(false);
            delete label_Welcome;

            textEdit_plain_main->setVisible(true);
            textEdit_plain_main->setGeometry(0,0, this->width(), this->height());
            textEdit_plain_main->setPlainText(readFileData(fileName));
            textEdit_plain_main->setFont(QFont("", 12));

//            qDebug() << textEdit_main->size() << "\n" << textEdit_main->isVisible();
//            label_openFile->setVisible(false);
//            label_Welcome->setVisible(false);
            textEdit_plain_main->setStyleSheet("QScrollBar:vertical { width: 8px; background: rgba(0,0,0,0%); margin: 0px,0px,0px,0px; padding-top: 9px; padding-bottom: 9px; } QScrollBar::handle:vertical { width: 8px; background: rgba(0,0,0,25%); border-radius: 4px; min-height: 20; } QScrollBar::handle:vertical:hover { width: 8px; background: rgba(0,0,0,50%); border-radius: 4px; min-height: 20; }");
            return true;
        }
    }

    return false;
}
