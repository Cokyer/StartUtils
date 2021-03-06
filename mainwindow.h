#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidgetItem>
#include <QProcess>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        QProcess *process;

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        void initView();
        void getData(QStringList list);

        void setProcess(QProcess *process);

    private:
        void getItem(QString service_name, QString status);
        Ui::MainWindow *ui;

    private slots:
        void change_cmd_output();
        void change_cmd_error();
        void on_select_lsit_itemClicked(QListWidgetItem *item);
        void on_change_btn_clicked();
};
#endif // MAINWINDOW_H
