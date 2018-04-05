#include "spingserver.h"
#include "ui_spingserver.h"

spingserver::spingserver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::spingserver)
{
    ui->setupUi(this);
    ui->image_label->setScaledContents(true);
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen(QHostAddress::Any,8888))
    {
        QMessageBox::critical(this,tr("Fortune Server"),tr("listen失败！！！").arg(tcpServer->errorString()));
        close();
        return;
    }
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(sendFortune()));
}

spingserver::~spingserver()
{
    delete ui;
}



void spingserver::sendFortune()
{
    basize=0;

    tcpServerConnection = tcpServer->nextPendingConnection();
    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_4_6);
    out<<(quint16) 0;
    out<<tr("OK");//当有连接时则发送一个OK信号给客户端，通知其发送数据

    out.device()->seek(0); //定位到第一个16位， 是写入的数据的大小
    out<<(quint16)(message.size()-sizeof(quint16));


    //connect(tcpServerConnection,SIGNAL(disconnected()),
    //        tcpServerConnection,SLOT(deleteLater()));
    tcpServerConnection->write(message); //写入发送的数据

    connect(tcpServerConnection,SIGNAL(readyRead()),
            this,SLOT(ReadMyData()));//当有数据到来时，读取图像数据
    connect(tcpServerConnection,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(DisplayError(QAbstractSocket::SocketError)));

}
//如果断开就 close()
void spingserver::DisplayError(QAbstractSocket::SocketError socketError)
{
    tcpServerConnection->close();
}
void spingserver::ReadMyData()
{
    QByteArray message;//存放从服务器接收到的字符串
    QDataStream in(tcpServerConnection);
    in.setVersion(QDataStream::Qt_4_6);
    if (basize==0)
    {
        //判断接收的数据是否有两字节（文件大小信息）
        //如果有则保存到basize变量中，没有则返回，继续接收数据
        if (tcpServerConnection->bytesAvailable()<(int)sizeof(quint64))
        {
            return;
        }
        in>>basize;
    }
    //如果没有得到全部数据，则返回继续接收数据
    if (tcpServerConnection->bytesAvailable()<basize)
    {
        return;
    }
    in>>message;//将接收到的数据存放到变量中
    ShowImage(message);
}

void spingserver::ShowImage(QByteArray ba)
{
    QString ss=QString::fromLatin1(ba.data(),ba.size());
    QByteArray rc;
    rc=QByteArray::fromBase64(ss.toLatin1());
    QByteArray rdc=qUncompress(rc);
    QImage img;
    img.loadFromData(rdc);
    ui->image_label->setPixmap(QPixmap::fromImage(img));
    ui->image_label->resize(img.size());
    update();
}
