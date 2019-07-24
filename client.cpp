#include "client.h"
#include "ui_client.h"
#include <QDebug>

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    setWindowTitle("client");
    mTcpSocket=new QTcpSocket(this);

    connect(mTcpSocket,&QTcpSocket::connected,this,[](){
        qDebug()<<"connected!";
    });
    connect(mTcpSocket,&QTcpSocket::readyRead,this,[&](){
        QByteArray arr=mTcpSocket->readAll();
        qDebug()<<"receive:"<<arr.size();
        char *p=new char[244]();
        memcpy(p,arr.data(),244);
        mRecv=(ImgData *)arr.data();
        //char *t=new char[16]();


        //img=(ImgData*)t;
        qDebug()<< mRecv->Tran<<","<<mRecv->Setting<<","<<mRecv->ImgID;
    });
}

Client::~Client()
{
    delete ui;
}

void Client::on_pushButton_connect_clicked()
{
    mTcpSocket->connectToHost("127.0.0.1",8888);
}
