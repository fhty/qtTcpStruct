#include "client.h"
#include "ui_client.h"
#include <QDebug>
#include <QImage>
#include <QString>
#include "imgbin.h"

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    setWindowTitle("client");
    mTcpSocket=new QTcpSocket(this);
    mRecv=new ImgInfoR;
    bool is_head=true;

    connect(mTcpSocket,&QTcpSocket::connected,this,[](){
        qDebug()<<"connected!";
    });

    connect(mTcpSocket,&QTcpSocket::readyRead,this,[&](){
        QByteArray arr=mTcpSocket->readAll();
        //qDebug()<<"receive:"<<arr->size();
        if(is_head){
            is_head=false;

            mRecv->Size=((ImgInfoR *)arr.data())->Size;
            strcpy(mRecv->Tran,((ImgInfoR *)arr.data())->Tran);
            strcpy(mRecv->Setting,((ImgInfoR *)arr.data())->Setting);

            QString name=QString("C:\\Users\\FHTY\\Desktop\\%1.jpeg").arg(mRecv->Tran);
            qDebug()<<"tran:"<<mRecv->Tran;
            qDebug()<<"set:"<<mRecv->Setting;
            qDebug()<<"file name:"<<name;
            file.setFileName(name);
            bool isOk=file.open(QIODevice::WriteOnly);
        }
        else {
//            memset(gImgBufR,0,mRecv->Size);
//            memcpy(gImgBufR,arr.data(),mRecv->Size);
//            ImgBin img;
//            img.saveToImg("C:\\Users\\FHTY\\Desktop\\2.jpeg",gImgBufR,mRecv->Size);

            //img.loadFromData(arr);
            qint64 len=file.write(arr);
            static qint64 recv_size=0;
            if(len>0) {
                recv_size+=len;
                qDebug()<<"receive size"<<recv_size;
            }
            if(recv_size==mRecv->Size){
                file.close();
            }
        }
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
