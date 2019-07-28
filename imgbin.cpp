#define _C_

#include "imgbin.h"
#include <cassert>
#include <fstream>
#include <QDebug>

ImgBin::ImgBin(QObject *parent) : QObject(parent)
{

}

ImgBin::~ImgBin()
{

}

unsigned long ImgBin::getImgSize(char *src_path)
{
    assert(src_path!=nullptr);
    FILE *rf=fopen(src_path,"rb");
    assert(rf!=nullptr);
    fseek(rf,0,SEEK_END);
    unsigned long src_size=ftell(rf);
    fclose(rf);
    return src_size;
}

bool ImgBin::setImg2Bin(char *src_path,unsigned long src_size,unsigned char *des_buf)
{
    if(src_path==nullptr||src_size<=0) {return false;}
    FILE *fp = fopen(src_path,"rb");
    if(!fp) return false;

    fread(des_buf, sizeof(unsigned char), src_size, fp);
    fclose(fp);

//    qDebug()<<"read:"<<mImgSize;
//    qDebug()<<"read:"<<sizeof(*mImgBuf);
    return true;
}

bool ImgBin::saveToImg(char *des_path,unsigned char *src_buf,unsigned long src_size)
{
    if(des_path==nullptr) {return false;}
    if(src_buf==nullptr) {return false;}
    FILE *fout = fopen(des_path, "wb");
    if(!fout) return false;
    fwrite(src_buf, sizeof(unsigned char), src_size, fout);
    fclose(fout);
}



