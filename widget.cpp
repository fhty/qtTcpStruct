#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QString>
#include<iostream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("server:8888");
    tcpSocket=new QTcpSocket(this);
    tcpServer=new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,8888);
    m_imgData=new ImgData;

    connect(tcpServer,&QTcpServer::newConnection,this,[=](){
        tcpSocket=tcpServer->nextPendingConnection();
        QString ip=tcpSocket->peerAddress().toString();
        qint64 port=tcpSocket->peerPort();
        qDebug()<<ip<<","<<port;
    });

    connect(tcpSocket,&QTcpSocket::readyRead,[=](){
        QByteArray arr=tcpSocket->readAll();
    });

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_SendButton_clicked()
{
    memcpy(m_imgData->Tran,ui->lineEdit_id->text().toLatin1().data(),16);
    memcpy(m_imgData->ImgID,"2019/07/24",64);
    memcpy(m_imgData->Setting,ui->lineEdit_setting->text().toLatin1().data(),16);
    m_imgData->Size=sizeof(*m_imgData);
    qDebug()<<"send:"<<sizeof(*m_imgData)<<","<<m_imgData->Tran<<","<<m_imgData->ImgID<<","<<m_imgData->Setting;
    qint64 len=tcpSocket->write((char *)m_imgData,sizeof(*m_imgData));

}
