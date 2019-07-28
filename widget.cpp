#include "widget.h"
#include "ui_widget.h"
#include "imgbin.h"
#include <QDebug>
#include <QString>
#include <QFile>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("server:8888");
    tcpSocket=new QTcpSocket(this);
    tcpServer=new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,8888);

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
    ImgBin img(this);
    unsigned long size=img.getImgSize("C:\\Users\\FHTY\\Desktop\\Pictures\\Jike\\2.jpeg");
    unsigned char *img_buf=new unsigned char[size]();
    bool isok=img.setImg2Bin("C:\\Users\\FHTY\\Desktop\\Pictures\\Jike\\2.jpeg",size,img_buf);
    if(!isok){return;}

    mImgInfo=new ImgInfo;
    memset(mImgInfo->Tran,0,16);
    memset(mImgInfo->Setting,0,16);
    mImgInfo->Size=size;
    memcpy(mImgInfo->Tran,ui->lineEdit_id->text().toLatin1().data(),16);
    memcpy(mImgInfo->Setting,ui->lineEdit_setting->text().toLatin1().data(),16);

    file=new QFile("C:\\Users\\FHTY\\Desktop\\Pictures\\Jike\\2.jpeg");
    bool isOk=file->open(QIODevice::ReadOnly);
    if(isok){
        qDebug()<<"open success";
        qDebug()<<file->size();
    }

    gImgBuf=new unsigned char[size]();
    memcpy(gImgBuf,img_buf,size);
    qDebug()<<"img size:"<<size;
    qDebug()<<sizeof (*gImgBuf);

    connect(&timer,&QTimer::timeout,this,[&](){
        timer.stop();
        static qint64 recv_size=0;
        //        qint64 len=tcpSocket->write((char *)gImgBuf,4096);
        //        qDebug()<<"send:"<<len;
        //        recv_size+=len;
        //        if(len==size) {
        //            qDebug()<<"send over";
        //            return;
        //        }
        qint64 len=0;
        do{
            char buf[4096]={0};
            len=file->read(buf,sizeof (buf));
            len=tcpSocket->write(buf,len);
            recv_size+=len;
            qDebug()<<"send:"<<len;
        }while(len>0);

        if(recv_size==file->size()){
            file->close();
        }
    });

    qint64 len=tcpSocket->write((char *)mImgInfo,sizeof(*mImgInfo));
    if(len>0){
        timer.start(128);
    }
}
