#ifndef IMGBIN_H
#define IMGBIN_H

#include <QObject>
#include <iostream>

class ImgBin : public QObject
{
    Q_OBJECT
public:
    explicit ImgBin(QObject *parent = nullptr);
    ~ImgBin();

    unsigned long getImgSize(char *src_path);
    bool setImg2Bin(char *src_path,unsigned long src_size,unsigned char *des_buf);
    bool saveToImg(char *des_path,unsigned char *src_buf,unsigned long src_size);
signals:

public slots:

private:
};

#endif // IMGBIN_H
