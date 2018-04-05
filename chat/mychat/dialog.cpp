#include "dialog.h"
#include "ui_dialog.h"
#include<QStyleFactory>
#include <QCryptographicHash>
#include<QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //设置窗口风格
    setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint);
    status = false;
    port = 8989;
    serverIP =new QHostAddress("192.168.1.189");
//     serverIP =new QHostAddress();

     tcpSocket = new QTcpSocket(this);
     //检测链接信号
     connect(tcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
     //检测如果断开
     connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
     //检测如果有新可以读信号
     connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));
     connect(tcpSocket,
             static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
     [=] (QAbstractSocket::SocketError UnconnectedState)
     {
         QMessageBox::information(this,tr("error"),tr("服务器连接失败！！！"));

         //设置登录可以点击
          ui->pushButton->setEnabled(true);
         //设置注册可以点击
         ui->regist_pushButton->setEnabled(true);
         //断开连接
         tcpSocket->close();
     });

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_3_clicked()
{
     exit(0);
}
bool mybool=false;


void Dialog::slotConnected(){
    QMessageBox::information(this,tr("ok"),tr("连接成功！"));
}

void Dialog::slotDisconnected(){
    QMessageBox::information(this,tr("error"),tr("服务器已断开！！！"));
    //断开连接
    tcpSocket->close();
}
//检测如果有新可以读信号
void Dialog::dataReceived(){
     QByteArray datagram;
     datagram.resize(tcpSocket->bytesAvailable());
     tcpSocket->read(datagram.data(),datagram.size());
     QString msg=datagram.data();
     qDebug()<<msg;
     //通过服务端确认
     if(msg=="ok"){

        myCCmyCharDialog = new CCmyCharDialog();
//        //设置
//        myCCmyCharDialog->setQTcpSocket(this->tcpSocket);
//        //ip
//        myCCmyCharDialog->setAddandport(this->port,this->serverIP);
        myCCmyCharDialog->set(this->username,this->userpasswd);
        //绑定关闭信号与槽
        connect(myCCmyCharDialog,SIGNAL(myclose()),this,SLOT(ccmyclose()));
        myCCmyCharDialog->show();
        this->hide();

        QString msg=tr("aaaaaaannnnnnnnnnnnnnnnnaaaaaaaaa")+"%"+tr("aaaaaaccccccccccccccccccccaaaaa")+"%"+login;
        tcpSocket->write(msg.toUtf8().data(),strlen(msg.toUtf8().data()));
       //断开与数据库的连接
        tcpSocket->close();
     }
     if(msg=="no"){
         QMessageBox::information(this,tr("error"),tr("账号或密码错误！！"));
         //设置登录可以点击
          ui->pushButton->setEnabled(true);
         //设置注册可以点击
         ui->regist_pushButton->setEnabled(true);
//         //断开连接
          tcpSocket->close();
     }
     if(msg=="zhuceok"){
         QMessageBox::information(this,tr("ok"),tr("账号注册成功，请重新登录！！！"));
         //设置登录可以点击
          ui->pushButton->setEnabled(true);
          //断开连接
          tcpSocket->close();
     }
     if(msg=="zhuceno"){
         QMessageBox::information(this,tr("error"),tr("账号被占错误！！"));
         //设置登录可以点击
          ui->pushButton->setEnabled(true);
          //设置注册可以点击
          ui->regist_pushButton->setEnabled(true);
          //断开连接
          tcpSocket->close();
     }
}

//接收到窗口关闭
void Dialog::ccmyclose(){
    myCCmyCharDialog->hide();
    this->show();
}

//buttontest
void Dialog::on_test_clicked()
{
    myCCmyCharDialog = new CCmyCharDialog();
    this->username=tr("渣渣辉");
    this->userpasswd=tr("zhazhahui");
    myCCmyCharDialog->set(this->username,this->userpasswd);
    myCCmyCharDialog->setAddandport(this->port,this->serverIP);
    //绑定关闭信号与槽
    connect(myCCmyCharDialog,SIGNAL(myclose()),this,SLOT(ccmyclose()));
    myCCmyCharDialog->show();
    this->hide();

    //断开连接
    tcpSocket->close();

}
//登录账号
void Dialog::on_pushButton_clicked()
{
       //判断用户名是否为空
       if(this->ui->name_lineEdit->text()=="")
       {
           QMessageBox::information(this,tr("error"),tr("User name error!"));
           return;
       }
       //判断用户名密码是否为空
       if(this->ui->passwd_lineEdit->text()=="")
       {
           QMessageBox::information(this,tr("error"),tr("User passwd error!"));
           return;
       }
       //判断 ip是否设置成功
       if(!serverIP->setAddress("192.168.1.189"))
       {
           QMessageBox::information(this,tr("error"),tr("server ip address error!"));
           return;
       }
       //用户名
        username=this->ui->name_lineEdit->text();
        //密码
        userpasswd=this->ui->passwd_lineEdit->text();
         login=tr("denglu");
        //连接
        cclink();

 }
//注册账号
void Dialog::on_regist_pushButton_clicked()
{
    //判断用户名是否为空
    if(this->ui->name_lineEdit->text()=="")
    {
        QMessageBox::information(this,tr("error"),tr("User name error!"));
        return;
    }
    //判断用户名密码是否为空
    if(this->ui->passwd_lineEdit->text()=="")
    {
        QMessageBox::information(this,tr("error"),tr("User passwd error!"));
        return;
    }
    //判断 ip是否设置成功
    if(!serverIP->setAddress("192.168.1.189"))
    {
        QMessageBox::information(this,tr("error"),tr("server ip address error!"));
        return;
    }
    //用户名
     username=this->ui->name_lineEdit->text();
     //密码
     userpasswd=this->ui->passwd_lineEdit->text();
    login=tr("zhuce");
     cclink();
}

//连接
void Dialog::cclink()
{
//    设置登录不可以点击
    ui->pushButton->setEnabled(false);
    //设置注册不可以点击
    ui->regist_pushButton->setEnabled(false);
    //     支持中文加密
    //     QByteArray bytePwd = strPwd5.toUtf8();
        QByteArray bytePwd = userpasswd.toLatin1();
        QByteArray bytePwdMd5 = QCryptographicHash::hash(bytePwd, QCryptographicHash::Md5);
        userpasswd=bytePwdMd5.toHex();
            tcpSocket->connectToHost(*serverIP,port);
        //int length=0;
        QString msg=username+"%"+userpasswd+"%"+login;
        if (tcpSocket->waitForConnected(1000)){
            qDebug("Connected!");
            qDebug("State:%d\n",tcpSocket->state()); // State: 3（ConnectedState）正确
            tcpSocket->write(msg.toUtf8().data(),strlen(msg.toUtf8().data()));
            qDebug("State:%d\n",tcpSocket->state());
        }

}



//ccSerSocket.bind(('192.168.1.189',8989))
