#ifndef CLIENT_H
#define CLIENT_H

#include "widget.h"
#include <QWidget>
#include <QTcpSocket>
#include <QFile>

struct ImgInfoR
{
    unsigned long Size;
    char Setting[16];
    char Tran[16];
};
static unsigned char *gImgBufR=nullptr;

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void on_pushButton_connect_clicked();

private:
    Ui::Client *ui;
    QTcpSocket *mTcpSocket;
    ImgInfoR *mRecv;
    QFile file;
};

#endif // CLIENT_H
