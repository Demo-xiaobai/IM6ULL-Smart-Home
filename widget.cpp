#include "widget.h"
#include "ui_widget.h"
#include <QNetworkInterface>
#include <QHostInfo>
#include <QThread>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

//    ui->pushButton = new QPushButton();
//    ui->pushButton_2 = new QPushButton();
//    ui->textBrowser = new QTextBrowser();


//    ui->pushButton->setText("===");
//    ui->pushButton_2->setText("---");

    timer = new QTimer();

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(timerStart()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(clearHostInfo()));

    connect(timer,SIGNAL(timeout()),this,SLOT(timerTimerout()));

}

Widget::~Widget()
{
    delete ui;
}

QString Widget::getHostInfo()
{
    QString str = "主机名称:" + QHostInfo::localHostName()+"\n";
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();

    foreach(QNetworkInterface interface,list){
        str += "网卡设备:" + interface.name()+"\n";
        str +="MAC地址:" + interface.hardwareAddress()+"\n";
            QList<QNetworkAddressEntry> entryList = interface.addressEntries();
            foreach(QNetworkAddressEntry entry,entryList){
                if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol){
                    str += "IP 地址:" + entry.ip().toString()+"\n";
                    str += "子网掩码:" + entry.netmask().toString()+"\n";
                    str += "广播地址:" + entry.broadcast().toString()+"\n";
                }
            }
    }
    qDebug() << str << endl;

    return str;
}

void Widget::timerTimerout()
{
    qDebug()<<"=====";
    showHostInfo();
    timer->stop();
}

void Widget::showHostInfo()
{
    ui->textBrowser->insertPlainText(getHostInfo());        /* 获取本机信息后显示到 textBrowser */

}

void Widget::timerStart()
{
    ui->textBrowser->clear();
    ui->textBrowser->setText("开启定时器");
    timer->start(1000);
}

void Widget::clearHostInfo()
{
    if(!ui->textBrowser->toPlainText().isEmpty()){
        ui->textBrowser->clear();
    }
}



