#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QTcpSocket>
#include <QObject>
#include <QStringList>
class TcpClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    TcpClientSocket(QObject *parent=0);
    QString nameclient;
signals:
    void updateClients(QString,int);
    //群发信号
    void SendBatch(QString name,QString str,QString toname);
    void disconnected(int);
    void saveclient(QString ccQString);

protected slots:
    void dataReceived();
    void slotDisconnected();
};

#endif // TCPCLIENTSOCKET_H
