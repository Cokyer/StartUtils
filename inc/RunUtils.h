#ifndef RUNUTILS_H
#define RUNUTILS_H

#include <QString>
#include <QProcess>

class RunUtils
{
    public:
        RunUtils();
        virtual ~RunUtils(void);

        QString run(QString, QString);
        QProcess* getProcess();

    private:
        QProcess *process;
};

#endif // RUNUTILS_H
