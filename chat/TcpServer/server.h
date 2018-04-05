#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include "tcpclientsocket.h"
#include<QHostAddress>
#include <QMap>
class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent=0,int port=0);
    QList<TcpClientSocket*> tcpClientSocketList;
    QMap<QString, TcpClientSocket*> tcpClientSocketmap;
    void senClients(QString,int);
signals:
    void updateServer(QString,int);
public slots:
    void updateClients(QString,int);

    //保存
    void saveclientslots(QString);

    //群发槽
    void SendBatchslot(QString name,QString ccQString,QString toname);
    void slotDisconnected(int);
protected:
    int port;
    QHostAddress *serverIP;
//    void incomingConnection(int socketDescriptor);
    void incomingConnection(qintptr socketDescriptor);
};

#endif // SERVER_H
