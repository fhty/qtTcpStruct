#ifndef CLIENT_H
#define CLIENT_H

#include "widget.h"
#include <QWidget>
#include <QTcpSocket>

struct ImgDataA
{
    int Size;
    char Setting[160];
    char Tran[16];
    char ImgID[64];
};

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
    ImgDataA *mRecv;
};

#endif // CLIENT_H
