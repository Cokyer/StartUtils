#include "inc/RunUtils.h"
#include "inc/Config.h"

RunUtils::RunUtils(){
    process = new QProcess();
    process->setReadChannel(QProcess::StandardOutput);
    //process->setReadChannel(QProcess::StandardError);
}

RunUtils::~RunUtils(){
    //delete process;
}

QString RunUtils::run(QString cmd, QString oldTerminalInfo){
    QString str;
    QString path = Config().Get("path","shell_path").toString();
    if(cmd.contains(".sh")){
        str = QString("/bin/bash ").append(path).append(cmd);
    } else {
        str = QString("cat ").append(path).append(cmd);
    }
    this->process->start(str);
    return oldTerminalInfo.append("cmd:").append(str);
}

QProcess* RunUtils::getProcess()
{
    return process;
}

