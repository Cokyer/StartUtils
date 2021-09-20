#include "inc/mainwindow.h"
#include "inc/FileUtils.h"
#include "inc/Config.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString path = Config().Get("path","shell_path").toString();
    if(path.size() == 0){
        Config().Set("path","shell_path","/home/coky/ServiceShell/");
    }

    MainWindow w;

    w.initView();

    w.show();
    return a.exec();
}
