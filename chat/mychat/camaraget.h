#ifndef CAMARAGET_H
#define CAMARAGET_H
#include <QWidget>
#include <QImage>
#include <QTimer>
#include<QtNetwork>
#include<QTcpServer>
#include<QTcpSocket>
#include<QtGui>

//opencv2
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>
#include<camthread.h>
using namespace cv;
namespace Ui {
class camaraGet;
}

class camaraGet : public QWidget
{
    Q_OBJECT

public:
    explicit camaraGet(QWidget *parent = 0);
    ~camaraGet();

private:
    Ui::camaraGet *ui;

private slots:
    void openCamara();      // 打开摄像头
    void readFarme(QImage );       // 读取当前帧信息
    void closeCamara();     // 关闭摄像头。
    void takingPictures();  // 拍照
    //void warn();
    void openvideo();
    void readFarme();
    void readMessage();

private:
    Camthread *camthread;
    QTimer    *timer;
    VideoCapture cap;
    bool video;
    int op;
    QImage   image;

    QTcpSocket* tcpSocket; //创建tcpsocket
    quint16 blockSize;       //存放文件的大小信息
    QString message;
};

#endif // CAMARAGET_H
