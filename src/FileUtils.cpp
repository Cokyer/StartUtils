#include "inc/FileUtils.h"
#include "inc/Config.h"

FileUtils::FileUtils()
{

}

QStringList FileUtils::getCount()
{
    QString path = Config().Get("path","shell_path").toString();
    QDir dir(path);
    QStringList nameFilters;
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);

    return files;
}

QString FileUtils::selectPath(QWidget *parent)
{
    QString srcDirPath = QFileDialog::getExistingDirectory(
               parent, "choose src Directory","/");

    if (srcDirPath.isEmpty())
    {
        return "";
    }
    else
    {
        srcDirPath += "/";
    }
    return srcDirPath;
}

FileUtils::~FileUtils()
{
    //delete this;
}

