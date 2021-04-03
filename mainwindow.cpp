#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Config.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::initView()
{
    QString path = Config().Get("path","shell_path").toString();

    this->setWindowTitle(QString::fromUtf8("启动面板"));
    ui->start_lab->setText(QString::fromUtf8("服务控制:"));
    ui->path_lab->setText(QString::fromUtf8("文件夹路径:"));
    ui->change_btn->setText(QString::fromUtf8("选择文件夹路径"));
    ui->clear_btn->setText(QString::fromUtf8("清除"));

    ui->path_text->setText(path);

    ui->cmd_lab->setText(QString::fromUtf8("终端运行情况:"));
}

void MainWindow::getData(QStringList list)
{
    foreach (QString str, list) {
        getItem(str, QString::fromUtf8("查看内容"));
    }
}

void MainWindow::setProcess(QProcess *process)
{
    this->process = process;
    connect(this->process , SIGNAL(readyReadStandardOutput()) , this , SLOT(change_cmd_output()));
    connect(this->process , SIGNAL(readyReadStandardError()) , this , SLOT(change_cmd_error()));
}

void MainWindow::getItem(QString service_name, QString status)
{
    QWidget *w = new QWidget();

    QLabel *label = new QLabel();
    label->setText(service_name);
    label->setObjectName("service_name");

    QHBoxLayout *layout = new QHBoxLayout();

    QPushButton *status_btn = new QPushButton(this);
    status_btn->setText(status);
    status_btn->setObjectName("status_btn");

    layout->addWidget(label);
    layout->addWidget(status_btn);

    w->setLayout(layout);

    QListWidgetItem *listItem = new QListWidgetItem();
    listItem->setSizeHint(QSize(200, 50));
    ui->select_lsit->addItem(listItem);
    ui->select_lsit->setItemWidget(listItem, w);

    //connect(this->ui->select_lsit, SIGNAL(itemClicked()) , this , SLOT(change_cmd()));
}

void MainWindow::change_cmd_output()
{
    QString str = ui->cmd_text->toPlainText().append("\n");
    ui->cmd_text->setText(str.append(process->readAllStandardOutput().data()));
}

void MainWindow::change_cmd_error()
{
    QString str = ui->cmd_text->toPlainText().append("\n");
    ui->cmd_text->setText(str.append(process->readAllStandardError().data()));
}

void MainWindow::on_select_lsit_itemClicked(QListWidgetItem *item)
{
    //ui->cmd_text->clear();

    QWidget *w = ui->select_lsit->itemWidget(item);
    QList<QLabel*> labelList = w->findChildren<QLabel*>();

    foreach (QLabel *lab, labelList) {
        QString cmd = QString("/home/coky/ServiceShell/").append(lab->text());
        QString str;
        if(cmd.contains(".sh")){
            str = QString("/bin/bash ").append(cmd);
        } else {
            str = QString("cat ").append(cmd);
        }
        QString old_str = ui->cmd_text->toPlainText();
        ui->cmd_text->setText(old_str.append("cmd:").append(str));
        process->start(str);
    }
}

void MainWindow::on_change_btn_clicked()
{
    QString srcDirPath = QFileDialog::getExistingDirectory(
               this, "choose src Directory","/home");

    if (srcDirPath.isEmpty())
    {
        return;
    }
    else
    {
        srcDirPath += "/";
    }
    ui->path_text->setText(srcDirPath);
    Config().Set("path", "shell_path", srcDirPath);
}

MainWindow::~MainWindow()
{
    delete ui;
}
