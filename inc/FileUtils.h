#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QString>
#include <QList>
#include <QDir>
#include <QProcess>
#include <QFileDialog>

class FileUtils{

    public:
        QProcess *process;

        FileUtils();
        virtual ~FileUtils(void);

    public:
        QStringList getCount();
        QProcess* getProcess();

        QString selectPath(QWidget *parent);

};

#endif // FILEUTILS_H
