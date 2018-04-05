#ifndef SPINGSERVER_H
#define SPINGSERVER_H

#include <QWidget>
#include<QTcpSocket>
#include<QTcpServer>
#include<QString>
#include<QtNetwork>
#include <QMessageBox>
#include<QImage>
namespace Ui {
class spingserver;
}

class spingserver : public QWidget
{
    Q_OBJECT

public:
    explicit spingserver(QWidget *parent = 0);
    ~spingserver();
    QTcpServer *tcpServer;
    QTcpSocket *tcpServerConnection;
    QStringList *fortunes;
    QImage *img;
    quint64 basize;

private:
    Ui::spingserver *ui;

public slots:
    //发送
    void sendFortune();
    //
    void DisplayError(QAbstractSocket::SocketError socketError);
    void ReadMyData();

    void ShowImage(QByteArray ba);
};

#endif // SPINGSERVER_H
