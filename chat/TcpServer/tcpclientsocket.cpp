#include "tcpclientsocket.h"
#include<QMessageBox>
TcpClientSocket::TcpClientSocket(QObject *parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
}

void TcpClientSocket::dataReceived()
{


    while(bytesAvailable()>0)
    {
       QString msg=QString::fromStdString(readAll().toStdString());

       QStringList strlist=msg.split("%");
//       qDebug()<<msg;

       //先判断要做什么
     //  上线
       if(strlist.at(1)=="first"){
//           QMessageBox::information((QWidget *)this,tr("ok"),tr("第一次连接成功！"));
           //after
//           QString msg=username+tr("%")+tr("first")+tr("%")+tr("null")+tr("%")+tr("null");

             qDebug()<<"当前前谁上线"<<strlist<<strlist.at(0);
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//             //先判当前谁上线了
//             for(it=tcpClientSocketmap.begin();it!=tcpClientSocketmap.end();it++)
//                 {
//                       qDebug()<<"所有上线:"<<"it.value()"<<it.value()<<"it.key()"<<it.key()<<"name"<<name;
////                     //如果他在线
////                     if( it.key()==name) {
////         //                tcpClientSocketmap.erase(it);
////                         qDebug()<<it.key()<<"接收者socket"<<it.value();

////                         //往接收者那写
////                         if( it.value()->write(ccQString.toUtf8().data(),strlen(ccQString.toUtf8().data()))  ==strlen(ccQString.toUtf8().data())
////                           ){
////                              continue;
////                            }
////                         break;
////                     }
//                 }
             //再给刚上线的那个发送所有在线的人
///////////////////////////////////////////////////////////////////////////////////////////////////////////
             this->nameclient=strlist.at(0);
             emit saveclient(strlist.at(0));

             //更新所有客服端
            emit updateClients(msg,msg.length());
       }
//       QString msg=username+tr("%")+str+tr("%")+tr("fangsong")+tr("%")+jeshou;
       //发送
       if(strlist.at(2)=="fangsong"){

          qDebug()<<"fangsong"<<strlist;
          emit SendBatch(strlist.at(0),strlist.at(1),strlist.at(3));

       }
       if(strlist.at(2)=="shiping"){
          qDebug()<<"shiping"<<strlist;
          emit SendBatch(strlist.at(0),strlist.at(1),strlist.at(3));

       }
       if(strlist.at(2)=="winjian"){
          qDebug()<<"winjian"<<strlist;
          emit SendBatch(strlist.at(0),strlist.at(1),strlist.at(3));

       }
        //更新客服端
//       emit updateClients(msg,msg.length());

    }

}

void TcpClientSocket::slotDisconnected()
{
    emit disconnected(this->socketDescriptor());
}
