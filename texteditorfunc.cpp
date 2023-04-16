#include "texteditorfunc.h"
#include <iostream>
#include <QString>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <string>
//#include <QDebug>
TextEditorFunc::TextEditorFunc()
{

}

QString TextEditorFunc::readFile(const QString& FilePath)
{
    QString path = FilePath;
    // 去除文件路径的"file:///"前缀
    path.remove(0, 8);
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "无法打开文件: " << FilePath;
            return "";
    }
    QTextStream in(&file);
    QString content;
    content = in.readAll();
    file.close();
    return content;
}

void TextEditorFunc::sayHello_02()
{

}

QString TextEditorFunc::getFileName(const QString &FilePath)
{
    std::string stdString = FilePath.toStdString();
    int pos = stdString.find_last_of('/');
    std::string s = stdString.substr(pos + 1);
    QString qstr = QString::fromStdString(s);
    return qstr;
}

void TextEditorFunc::saveFile(const QString &FilePath, const QString &FileData)
{
    QString path = FilePath;
    // 去除文件路径的"file:///"前缀
    path.remove(0, 8);

    qDebug() << "file:" << path;
    QFile file(path);
    qDebug() << FileData;
    file.open(QIODevice::WriteOnly);
    file.write(FileData.toUtf8());
    file.close();
    qDebug() << "OK_02";
}

