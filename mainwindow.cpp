#include "mainwindow.h"
#include "txpackets.h"
#include "configthread.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<"MainWindow destrust";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_runTestOnce_clicked() //单次测试
{
    int packetSize = ui->spinBox_packetSize->value();
    int txSpeed = ui->spinBox_txSpeed->value();
    qDebug()<<"on runtest";
    //TxPackets* tp = new TxPackets();
    //char *data = "woaiminmin";
    //tp->run(data, 100, 10);
    QSettings setting("418","AFDXTester");//保存到注册表中
    setting.beginGroup("Tx Config");
    setting.setValue("PacketSize", packetSize);
    setting.setValue("TxSpeed", txSpeed);
    setting.endGroup();
    ConfigThread *configtd = new ConfigThread();
    connect(configtd, &configtd->finished, configtd, &configtd->deleteLater);
    configtd->start();
}

void MainWindow::on_pushButton_runTestLC_clicked()  //线性加压测试
{
    qDebug()<<"on runTestLC";
    //包长：0->64->128->256->512->1024
    //速率：1->2->4->8->16->32->64->128->256->512
    //6*10 = 60

}
