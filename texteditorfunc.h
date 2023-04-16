#ifndef TEXTEDITORFUNC_H
#define TEXTEDITORFUNC_H

#include <QObject>

class TextEditorFunc : public QObject
{
    Q_OBJECT

    public:
    TextEditorFunc();
    Q_INVOKABLE QString readFile(const QString& FilePath);
    Q_INVOKABLE void sayHello_02();
    Q_INVOKABLE QString getFileName(const QString& FilePath);
    Q_INVOKABLE void saveFile(const QString& FilePath, const QString& FileData);
};

#endif
