#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QTimer>
#include <QFile>

struct ImgInfo
{
    unsigned long Size;
    char Setting[16];
    char Tran[16];
};
static unsigned char *gImgBuf=nullptr;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_SendButton_clicked();

private:
    Ui::Widget *ui;

    ImgInfo *mImgInfo;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    QTimer timer;
    QFile *file;
};

#endif // WIDGET_H
