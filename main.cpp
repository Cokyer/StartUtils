#include "mainwindow.h"
#include "FileUtils.h"
#include "Config.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString path = Config().Get("path","shell_path").toString();
    if(path.size() == 0){
        Config().Set("path","shell_path","/home/coky/ServiceShell/");
    }

    MainWindow w;
    FileUtils *file = new FileUtils();

    w.initView();
    w.getData(file->getCount());
    w.setProcess(file->getProcess());

    w.show();
    return a.exec();
}
