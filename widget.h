#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>

struct ImgData
{
    int Size;
    char Setting[160];
    char Tran[16];
    char ImgID[64];
};

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

    ImgData *m_imgData;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
};

#endif // WIDGET_H
