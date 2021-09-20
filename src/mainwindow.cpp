#include "inc/mainwindow.h"
#include "ui_mainwindow.h"
#include "inc/Config.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::initView()
{
    this->setWindowTitle(QString::fromUtf8("启动面板"));
    ui->start_lab->setText(QString::fromUtf8("服务控制:"));
    ui->path_lab->setText(QString::fromUtf8("文件夹路径:"));
    ui->change_btn->setText(QString::fromUtf8("选择文件夹路径"));
    ui->clear_btn->setText(QString::fromUtf8("清除"));

    ui->path_text->setText(Config().Get("path","shell_path").toString());

    ui->cmd_lab->setText(QString::fromUtf8("终端运行情况:"));

    this->runUtils = new RunUtils();

    fetchShList();
    initTerminal();
}

void MainWindow::fetchShList()
{
    QStringList list = FileUtils().getCount();
    ui->select_lsit->clear();
    foreach (QString str, list) {
        getItem(str, QString::fromUtf8("查看内容"));
    }
}

void MainWindow::initTerminal()
{
    connect(this->runUtils->getProcess() , SIGNAL(readyReadStandardOutput()) , this , SLOT(change_cmd_output()));
    connect(this->runUtils->getProcess() , SIGNAL(readyReadStandardError()) , this , SLOT(change_cmd_error()));
}

void MainWindow::getItem(QString service_name, QString status)
{
    QWidget *w = new QWidget();

    QLabel *label = new QLabel();
    label->setText(service_name);
    label->setObjectName("service_name");

    QHBoxLayout *layout = new QHBoxLayout();

    layout->addWidget(label);

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
    ui->cmd_text->setText(str.append(this->runUtils->getProcess()->readAllStandardOutput().data()));
}

void MainWindow::change_cmd_error()
{
    QString str = ui->cmd_text->toPlainText().append("\n");
    ui->cmd_text->setText(str.append(this->runUtils->getProcess()->readAllStandardError().data()));
}

void MainWindow::on_select_lsit_itemClicked(QListWidgetItem *item)
{
    //ui->cmd_text->clear();

    QWidget *w = ui->select_lsit->itemWidget(item);
    QList<QLabel*> labelList = w->findChildren<QLabel*>();

    foreach (QLabel *lab, labelList) {
        ui->cmd_text->setText(this->runUtils->run(lab->text(), ui->cmd_text->toPlainText()));
    }
}

void MainWindow::on_change_btn_clicked()
{
    QString srcDirPath = FileUtils().selectPath(this);
    ui->path_text->setText(srcDirPath);
    Config().Set("path", "shell_path", srcDirPath);

    fetchShList();
}

MainWindow::~MainWindow()
{
    delete ui;
}
