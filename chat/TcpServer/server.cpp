#include "server.h"

Server::Server(QObject *parent,int port)
    :QTcpServer(parent)
{
    serverIP =new QHostAddress();
    serverIP->setAddress("192.168.2.186");
    //1
    ///////////////////////////////////////////////////////////////////////

//     serverIP->setAddress(QHostAddress::Any);

    ////////////////////////////////////////////////////////////////////////
    listen(*serverIP,port);
}


//群主单独函数
void Server::senClients(QString str, int length)
{
//     QStringList strlist=msg.split("%");
    QString msg="管理员"+tr("%")+tr("qunfa")+tr("%")+str+tr("%")+tr("null");
    QStringList strlist=msg.split("%");
    qDebug()<<"管理员:"<<strlist;
    emit updateServer(msg,length);
    for(int i=0;i<tcpClientSocketList.count();i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
         qDebug()<<"群主单独函数item:"<<item;
         if( item->write(msg.toUtf8().data(),strlen(msg.toUtf8().data()))  ==strlen(msg.toUtf8().data())
          ){
             continue;
           }
    }
}
int i =0;
void Server::incomingConnection(qintptr socketDescriptor)
{
    //第链接一个会新创建一个
    TcpClientSocket *tcpClientSocket=new TcpClientSocket(this);
    connect(tcpClientSocket,SIGNAL(updateClients(QString,int)),this,SLOT(updateClients(QString,int)));
    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected(int)));
    //保存信号
    connect(tcpClientSocket,SIGNAL(saveclient(QString)),this,SLOT(saveclientslots(QString)));

    //每个客服端的群发信号
    connect(tcpClientSocket,SIGNAL(SendBatch(QString,QString,QString)),this,SLOT(SendBatchslot(QString,QString,QString)));
    //设置套节字
    tcpClientSocket->setSocketDescriptor(socketDescriptor);

    tcpClientSocketList.append(tcpClientSocket);
    qDebug()<<i;
    i++;
}



//一上线群发
void Server::updateClients(QString msg,int length)
{
    emit updateServer(msg,length);
    for(int i=0;i<tcpClientSocketList.count();i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);

         if( item->write(msg.toUtf8().data(),strlen(msg.toUtf8().data()))  ==strlen(msg.toUtf8().data())
          ){
             continue;
           }
    }
}


//保存
void Server::saveclientslots(QString ccQString)
{
    qDebug()<<"参数"<<ccQString;
    for(int i=0;i<tcpClientSocketList.count();i++)
    {
        TcpClientSocket *item = tcpClientSocketList.at(i);

         if(item->nameclient==ccQString){
                qDebug()<<"插入"<<item->nameclient;
//              map.insert(4, 400);
             //保存起来

             tcpClientSocketmap.insert(ccQString,item);
              qDebug()<<"插入"<<item;
         }
    }
}


//发送槽
void Server::SendBatchslot(QString wherename,QString ccQString,QString toname)
{
    //QString msg=username+tr("%")+tr("first")+tr("%")+tr("null")+tr("%")+tr("null");
    //拼接成信息
    QString msg=toname+tr("%")+tr("xinxi")+tr("%")+ccQString+tr("%")+wherename;
    emit updateServer(msg,msg.length());
    qDebug()<<"//发送槽"<<msg<<wherename;
    QMap<QString, TcpClientSocket*>::iterator it;
    //找接收者
    for(it=tcpClientSocketmap.begin();it!=tcpClientSocketmap.end();it++)
        {
            qDebug()<<"t.value()"<<it.value()<<"it.key()"<<it.key()<<"name"<<toname;
            //如果他在线
            if( it.key()==toname) {
//                tcpClientSocketmap.erase(it);
                qDebug()<<it.key()<<"接收者socket"<<msg;

                //往接收者那写
                if( it.value()->write(msg.toUtf8().data(),strlen(msg.toUtf8().data()))  ==strlen(msg.toUtf8().data())
                  ){
                     continue;
                   }
                break;
            }
        }
//    for(int i=0;i<tcpClientSocketList.count();i++)
//    {
//        QTcpSocket *item = tcpClientSocketList.at(i);

//         if( item->write(ccQString.toUtf8().data(),strlen(ccQString.toUtf8().data()))  ==strlen(ccQString.toUtf8().data())
//          ){
//             continue;
//           }
//    }
}

void Server::slotDisconnected(int descriptor)
{
    for(int i=0;i<tcpClientSocketList.count();i++)
    {

        qDebug()<<tcpClientSocketList.at(i);
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->socketDescriptor()==descriptor)
        {

            QMap<QString, TcpClientSocket*>::iterator it;
            for(it=tcpClientSocketmap.begin();it!=tcpClientSocketmap.end();it++)
                {
                    qDebug()<<it.value();

                    if( it.value()==item) {
                        tcpClientSocketmap.erase(it);
                        break;
                    }
                }
            tcpClientSocketList.removeAt(i);
            return;
        }
    }
    return;
}
