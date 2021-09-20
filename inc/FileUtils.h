#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QString>
#include <QList>
#include <QDir>
#include <QFileDialog>

class FileUtils{

    public:
        FileUtils();
        virtual ~FileUtils(void);

    public:
        QStringList getCount();
        QString selectPath(QWidget *parent);

};

#endif // FILEUTILS_H
