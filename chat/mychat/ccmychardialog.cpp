#include "ccmychardialog.h"
#include "ui_ccmychardialog.h"
#include <QGroupBox>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include <iostream>
#include <fstream>
#include "spingserver.h"
using namespace std;
CCmyCharDialog::CCmyCharDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CCmyCharDialog)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    this->port=4444;


    serverIP =new QHostAddress();
    serverIP->setAddress("192.168.2.186");


    mytcpSocket = new QTcpSocket(this);
    mytcpSocket->connectToHost(*serverIP,port);

    //检测链接信号
    connect(mytcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
    //检测如果断开
    connect(mytcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
    //检测如果有新可以读信号
    connect(mytcpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));

    //toolbox改变
    connect(ui->toolBox,SIGNAL(currentChanged(int)),this,SLOT(currentChangedsolts(int)));
    //开始不能点击必需选择好友
    ui->pushButton->setEnabled(false);

    ccpersonList=new personList();

    ////////////////////////////////////////
    setWindowTitle(tr("My QQ"));
    //***************初始化我的好友*****************
    //      //好友
    //      QMap<QString,  QToolButton*> QToolButtonMap;
    //渣渣辉
    toolBtn1_1=new QToolButton;
    //绑定事件
    connect(toolBtn1_1,SIGNAL(clicked()),this,SLOT(on_QToolButton1_clicked()));
    toolBtn1_1->setText(tr("渣渣辉"));
    //    toolBtn1_1->setEnabled(false);
    //保存
    QToolButtonMap.insert(toolBtn1_1->text(),toolBtn1_1);
    toolBtn1_1->setIcon(QPixmap(":渣渣辉.png"));
    QSize qsize=QSize((QPixmap(":渣渣辉.png").size().width())/5, (QPixmap(":渣渣辉.png").size().height())/5);
    toolBtn1_1->setIconSize(qsize);
    toolBtn1_1->setAutoRaise(true);
    toolBtn1_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);


    //古天乐
    toolBtn1_2=new QToolButton;
    connect(toolBtn1_2,SIGNAL(clicked()),this,SLOT(on_QToolButton2_clicked()));
    toolBtn1_2->setText(tr("古天乐"));
    //    toolBtn1_2->setEnabled(false);
    //保存
    QToolButtonMap.insert(toolBtn1_2->text(),toolBtn1_2);
    toolBtn1_2->setIcon(QPixmap(":古天乐.png"));
    toolBtn1_2->setIconSize(qsize);
    toolBtn1_2->setAutoRaise(true);
    toolBtn1_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);


    //allen
    toolBtn1_3=new QToolButton;
    connect(toolBtn1_3,SIGNAL(clicked()),this,SLOT(on_QToolButton3_clicked()));
    toolBtn1_3->setText(tr("allen"));
    //    toolBtn1_3->setEnabled(false);
    //保存
    QToolButtonMap.insert(toolBtn1_3->text(),toolBtn1_3);
    toolBtn1_3->setIcon(QPixmap(":image"));
    toolBtn1_3->setIconSize(qsize);
    toolBtn1_3->setAutoRaise(true);
    toolBtn1_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);


    //hai
    toolBtn1_4=new QToolButton;
    connect(toolBtn1_4,SIGNAL(clicked()),this,SLOT(on_QToolButton4_clicked()));
    toolBtn1_4->setText(tr("hai"));
    //    toolBtn1_4->setEnabled(false);
    //保存
    QToolButtonMap.insert(toolBtn1_4->text(),toolBtn1_4);
    toolBtn1_4->setIcon(QPixmap(":qq 头像 1.png"));
    toolBtn1_4->setIconSize(qsize);
    toolBtn1_4->setAutoRaise(true);
    toolBtn1_4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);


    //土行孙
    toolBtn1_5=new QToolButton;
    connect(toolBtn1_5,SIGNAL(clicked()),this,SLOT(on_QToolButton5_clicked()));
    toolBtn1_5->setText(tr("土行孙"));
    //    toolBtn1_5->setEnabled(false);
    //保存
    QToolButtonMap.insert(toolBtn1_5->text(),toolBtn1_5);
    toolBtn1_5->setIcon(QPixmap(":qq2.png"));
    toolBtn1_5->setIconSize(qsize);
    toolBtn1_5->setAutoRaise(true);
    toolBtn1_5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //*************逆向基佬*******************
    QGroupBox *groupBox1=new QGroupBox;
    layout1=new QVBoxLayout(groupBox1);
    layout1->setMargin(10);
    layout1->setAlignment(Qt::AlignHCenter);
    layout1->addStretch();
    //***************运维基佬*********************
    toolBtn2_1=new QToolButton;
    //    QMap<bool,  QMap<QString,  QToolButton*>> QToolButtonfriendMap;
    QMap<QString,  QToolButton*> temp0;
    temp0.insert(toolBtn2_1->text(),toolBtn2_1);
    QToolButtonfriendMap.insert(false,temp0);
    //好友 1
    connect(toolBtn2_1,SIGNAL(clicked()),this,SLOT(on_QtoolBtn2_1_clicked()));
    toolBtn2_1->setText(tr("小王"));
    toolBtn2_1->setIcon(QPixmap(":qq2.png"));
    toolBtn2_1->setIconSize(qsize);
    toolBtn2_1->setAutoRaise(true);
    toolBtn2_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolBtn2_1->setEnabled(false);

    toolBtn2_2=new QToolButton;
    QMap<QString,  QToolButton*> temp1;
    temp1.insert(toolBtn2_2->text(),toolBtn2_2);
    QToolButtonfriendMap.insert(false,temp1);
    //好友 2
    connect(toolBtn2_2,SIGNAL(clicked()),this,SLOT(on_QtoolBtn2_2_clicked()));
    toolBtn2_2->setText(tr("小张"));
    toolBtn2_2->setIcon(QPixmap(":image"));
    toolBtn2_2->setIconSize(qsize);
    toolBtn2_2->setAutoRaise(true);
    toolBtn2_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolBtn2_2->setEnabled(false);
    //***************运维基佬*****************
    QGroupBox *groupBox2=new QGroupBox;
    QVBoxLayout *layout2=new QVBoxLayout(groupBox2);
    layout2->setMargin(10);
    layout2->setAlignment(Qt::AlignHCenter);
    layout2->addWidget(toolBtn2_1);
    layout2->addWidget(toolBtn2_2);
    layout2->addStretch();
    //***************黑客名单*********************
    toolBtn3_1=new QToolButton;
    QMap<QString,  QToolButton*> temp2;
    temp2.insert(toolBtn3_1->text(),toolBtn3_1);
    QToolButtonfriendMap.insert(false,temp2);
    //好友 3
    connect(toolBtn3_1,SIGNAL(clicked()),this,SLOT(on_QtoolBtn3_1_clicked()));
    toolBtn3_1->setText(tr("小王"));
    toolBtn3_1->setIcon(QPixmap(":image"));
    toolBtn3_1->setIconSize(qsize);
    toolBtn3_1->setAutoRaise(true);
    toolBtn3_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolBtn3_1->setEnabled(false);
    toolBtn3_2=new QToolButton;
    toolBtn3_2->setText(tr("小张"));
    QMap<QString,  QToolButton*> temp3;
    temp3.insert(toolBtn3_2->text(),toolBtn3_2);
    QToolButtonfriendMap.insert(false,temp3);
    //好友 4
    connect(toolBtn3_2,SIGNAL(clicked()),this,SLOT(on_QtoolBtn3_2_clicked()));
    toolBtn3_2->setIcon(QPixmap(":image"));
    toolBtn3_2->setIconSize(qsize);
    toolBtn3_2->setAutoRaise(true);
    toolBtn3_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolBtn3_2->setEnabled(false);

    //***************添加黑名单*****************
    QGroupBox *groupBox3=new QGroupBox;
    QVBoxLayout *layout3=new QVBoxLayout(groupBox3);
    layout3->setMargin(10);
    layout3->setAlignment(Qt::AlignHCenter);
    layout3->addWidget(toolBtn3_1);
    layout3->addWidget(toolBtn3_2);
    layout3->addStretch();
    //***************添加至主窗口*****************

    ui->toolBox->insertItem(0,(QWidget*)groupBox1,tr("逆向基佬"));
    ui->toolBox->insertItem(1,(QWidget*)groupBox2,tr("运维基佬"));
    ui->toolBox->setItemText(2,tr("信息安全基佬"));
    ui->toolBox->setItemText(3,tr("网络安全基佬"));
    ui->toolBox->addItem((QWidget*)groupBox3,tr("其它黑客名单"));
    ui->toolBox->addItem((QWidget*)ccpersonList,tr("qq"));
}

CCmyCharDialog::~CCmyCharDialog()
{
    delete ui;

}
//设置用户名与密码
void CCmyCharDialog::set(QString use, QString pawssd)
{
    this->username=use;
    this->userpasswd=pawssd;
    QString name="你的昵称:"+use;
    ui->label_2->setText(name);
    //设置好友
    setfriend();
}

void CCmyCharDialog::setQTcpSocket(QTcpSocket * mysocket)
{
    this->mytcpSocket=mysocket;
}

void CCmyCharDialog::setAddandport(int port, QHostAddress *serverIP)
{
    this->serverIP=serverIP;
    this->port=port;
}
//设置好友
bool frit=true;
void CCmyCharDialog::setfriend()
{
    QMap<QString,  QToolButton*>::iterator it;
    while (frit) {
        for(it=QToolButtonMap.begin();it!=QToolButtonMap.end();it++)
        {
            qDebug()<<"t.value()"<<it.value()<<"it.key()"<<it.key()<<"name"<<this->username;
            //判断你当前是谁
            if( it.key()==this->username) {
                continue;
            }else{
                layout1->addWidget(it.value());
            }
        }

        frit=false;
    }
}

//更新好友列表
void CCmyCharDialog::updatefriends(QString usern)
{

    QString str="好友:"+usern+"上线了";
    if(usern!=this->username){
        QMessageBox::information(this,tr("ok"),str);

        QMap<QString,  QToolButton*>::iterator it;
        for(it=QToolButtonMap.begin();it!=QToolButtonMap.end();it++)
        {
            qDebug()<<"t.value()"<<it.value()<<"it.key()"<<it.key()<<"name"<<this->username;
            //判断要更新谁
            if( it.key()==usern) {
                it.value()->setEnabled(true);
            }else{
                continue;
            }
        }


    }
}

//关闭事件
void CCmyCharDialog::closeEvent(QCloseEvent *event)
{
    exit(0);
    //    emit myclose();
}

//数据发送
void CCmyCharDialog::on_pushButton_clicked()
{
    if(ui->textEdit_2->document()->isEmpty()){
        QMessageBox::information(this,tr("error"),tr("不能为空！！！"));
        return;
    }
    //    //获取发送内容
    QString str=ui->textEdit_2->toPlainText();
    //发送内容
    QString msg=username+tr("%")+str+tr("%")+tr("fangsong")+tr("%")+this->jeshou;
    mytcpSocket->write(msg.toStdString().data());
    //把自己的信息保存 str 中
    this->test += this->username+":"+"\n"+str+"\n";
    //先清理
    ui->textEdit_2->clear();
    //输出内容
    ui->textEdit->setPlainText(test);

}

//渣渣辉
void CCmyCharDialog::on_QToolButton1_clicked()
{
    QString str=tr("当前会话:")+toolBtn1_1->text();
    //        QPixmap pTimePix(tr(":brg.jpeg"));
    //        QPainter painter1;
    //        painter1.begin(&pTimePix);
    //        painter1.setPen(Qt::blue);
    //        painter1.drawText(0,5,100,20, Qt::AlignBottom, str);    //这里要确保你的坐标等等参数正确，不然你就不知道画到哪里去了
    //        painter1.end();
    //        ui->label->setPixmap(pTimePix);
    ui->label->setText(str);
    ui->pushButton->setEnabled(true);
    this->jeshou=toolBtn1_1->text();
}
//古天乐
void CCmyCharDialog::on_QToolButton2_clicked()
{
    QString str=tr("当前会话:")+toolBtn1_2->text();
    ui->label->setText(str);
    ui->pushButton->setEnabled(true);
    this->jeshou=toolBtn1_2->text();
}

//allen
void CCmyCharDialog::on_QToolButton3_clicked()
{
    QString str=tr("当前会话:")+toolBtn1_3->text();
    //    str="allen";
    //    QPixmap pTimePix(tr(":brg.jpeg"));
    //    QPainter painter1;
    //    painter1.begin(&pTimePix);
    //    painter1.setPen(Qt::blue);
    //    QPoint pinl=QPoint(0,0);
    //    QPoint pinr=QPoint(pTimePix.height()/2,pTimePix.width()/2);
    //    QRect rect = QRect(pinl,pinr);
    //    painter1.drawText(rect, Qt::AlignCenter, str);    //这里要确保你的坐标等等参数正确，不然你就不知道画到哪里去了
    //    painter1.end();
    ui->label->setText(str);
    ui->pushButton->setEnabled(true);
    this->jeshou=toolBtn1_3->text();
}
//hai
void CCmyCharDialog::on_QToolButton4_clicked()
{
    QString str=tr("当前会话:")+toolBtn1_4->text();
    ui->label->setText(str);
    ui->pushButton->setEnabled(true);
    this->jeshou=toolBtn1_4->text();
}
///土行孙
void CCmyCharDialog::on_QToolButton5_clicked()
{
    QString str=tr("当前会话:")+toolBtn1_5->text();
    ui->label->setText(str);
    ui->pushButton->setEnabled(true);
    this->jeshou=toolBtn1_5->text();
}


void CCmyCharDialog::currentChangedsolts(int index)
{
    //    QMap<QString,  QToolButton*> QToolButtonMap;

    //    layout1->addWidget(toolBtn1_1);
    //    layout1->addWidget(toolBtn1_2);
    //    layout1->addWidget(toolBtn1_3);
    //    layout1->addWidget(toolBtn1_4);
    //    layout1->addWidget(toolBtn1_5);
    QString str=tr("第")+QString(index)+tr("页");
    //    QMessageBox::information(this,"ok",str);
}

/////////////////////////////////////////////////////////////////////////
//第一次链接后
int length=0;
void CCmyCharDialog::slotConnected()
{
    //after
    QString msg=username+tr("%")+tr("first")+tr("%")+tr("null")+tr("%")+tr("null");
    mytcpSocket->write(msg.toStdString().data());
}

//断开连接
void CCmyCharDialog::slotDisconnected()
{

}
//数据接收
void CCmyCharDialog::dataReceived()
{
    while(mytcpSocket->bytesAvailable()>0)
    {
        QString msg=QString::fromStdString(mytcpSocket->readAll().toStdString());
        QStringList strlist=msg.split("%");
        qDebug()<<"客服端接收"<<strlist;
        if(strlist.at(1)=="first"){
            this->updatefriends(strlist.at(0));
            //直接返回
            return;
        }
        //如果是管理员
        //QString msg="管理员"+tr("%")+tr("qunfa")+tr("%")+str+tr("%")+tr("null");
        if(strlist.at(1)=="qunfa"){
            this->test +=strlist.at(0)+":"+"\n"+strlist.at(2)+'\n';
            //先清理文本框
            ui->textEdit->clear();
            //输出内容
            ui->textEdit->setPlainText(test);
            return ;
        }
        //如果是信息
        // QString msg=toname+tr("%")+tr("xinxi")+tr("%")+ccQString+tr("%")+wherename;
        if(strlist.at(1)=="xinxi"){


            //            shiping ("hai", "xinxi", "shiping", "allen")
            if(strlist.at(2)=="shiping"){

                ////////////////////////////////////////////////////////////
                QMessageBox::information(this,tr("ok"),tr("shiping!!!"));
                //new 一个 sokect
                this->test +=strlist.at(3)+":"+"\n"+strlist.at(2)+'\n';
                //先清理文本框
                ui->textEdit->clear();
                //输出内容
                ui->textEdit->setPlainText(test);
                qDebug()<<"shiping"<<strlist;
                sping = new spingserver();
                sping->show();

                return;

                ////////////////////////////////////////////////////////////
            }
            //            winjian ("hai", "xinxi", "winjian", "allen")
            if(strlist.at(2)=="winjian"){

                ////////////////////////////////////////////////////////////
                QMessageBox::information(this,tr("ok"),tr("文件来了，请点击接收!!!"));
                //new 一个 sokect
                this->test +=strlist.at(3)+":"+"\n"+strlist.at(2)+'\n';
                //先清理文本框
                ui->textEdit->clear();
                //输出内容
                ui->textEdit->setPlainText(test);
                qDebug()<<"winjian"<<strlist;
                myreceivemainwindow = new receiveMainWindow();
                myreceivemainwindow->show();

                return;

                ////////////////////////////////////////////////////////////
            }
            this->test +=strlist.at(3)+":"+"\n"+strlist.at(2)+'\n';
            //先清理文本框
            ui->textEdit->clear();
            //输出内容
            ui->textEdit->setPlainText(test);
            return;
        }
        this->test +=strlist.at(0)+":"+"\n"+strlist.at(2)+'\n';

    }
}


//保存聊天记录
void CCmyCharDialog::on_pushButton_6_clicked()
{
    QString str=tr("/Users/allenboy/Desktop/")+this->username+tr(".txt");
    //写
    fstream rfstream(str.toStdString(),ios::out);
    rfstream<<this->test.toStdString();
    qDebug()<<this->test;
    QMessageBox::information(this,tr("ok"),tr("保存成功！！！"));

}
//查看聊天记录
void CCmyCharDialog::on_pushButton_5_clicked()
{
    QMessageBox::information(this,tr("ok"),this->test);

}

//添加好友
void CCmyCharDialog::on_pushButton_4_clicked()
{
    if(ui->lineEdit->text()==""){
        QMessageBox::information(this,tr("error"),tr("输入错误！！！"));
        return;
    }
    if(ui->lineEdit->text()==this->username){
        QMessageBox::information(this,tr("error"),tr("不能添加自己做为好友！！！"));
        return;
    }
    //用于添加好友
    //    QTcpSocket *sqlmytcpSocket;
    //    int sqlport;
    //    QHostAddress *sqlserverIP;
    this->sqlport=8989;
    sqlserverIP =new QHostAddress();
    //    sqlserverIP->setAddress("192.168.1.190");
    sqlserverIP->setAddress("192.168.1.189");
    sqlmytcpSocket = new QTcpSocket(this);
    sqlmytcpSocket->connectToHost(*sqlserverIP,sqlport);
    QString login=tr("tainjia");
    //获取添加名字
    QString username=ui->lineEdit->text();
    QString msg=username+"%"+ tr("null")+"%"+login;
    sqlmytcpSocket->write(msg.toUtf8().data(),strlen(msg.toUtf8().data()));
    //检测链接信号
    connect(sqlmytcpSocket,SIGNAL(connected()),this,SLOT(sqlslotConnected()));
    //检测如果断开
    connect(sqlmytcpSocket,SIGNAL(disconnected()),this,SLOT(sqlslotDisconnected()));
    //检测如果有新可以读信号
    connect(sqlmytcpSocket,SIGNAL(readyRead()),this,SLOT(sqldataReceived()));
    connect(sqlmytcpSocket,
            static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
            [=] (QAbstractSocket::SocketError UnconnectedState)
    {
        QMessageBox::information(this,tr("error"),tr("数据库连接失败！！！"));
        //断开连接
        sqlmytcpSocket->close();
    });
}

//检测链接信号
void CCmyCharDialog::sqlslotConnected()
{

}
//检测如果断开
void CCmyCharDialog::sqlslotDisconnected()
{

}
//检测如果有新可以读信号
void CCmyCharDialog::sqldataReceived()
{
    QByteArray datagram;
    datagram.resize(sqlmytcpSocket->bytesAvailable());
    sqlmytcpSocket->read(datagram.data(),datagram.size());
    QString msg=datagram.data();
    qDebug()<<msg;
    //通过服务端确认
    if(msg=="ok"){
        QMessageBox::information(this,tr("ok"),tr("数据库有！！！"));
        //        QMap<QString, TcpClientSocket*>::iterator it;
        //        QMap<bool,  QMap<QString,  QToolButton*>> ::iterator it;;

        this->toolBtn2_1->setEnabled(true);
        this->toolBtn2_1->setText(ui->lineEdit->text());
        QMessageBox::information(this,tr("ok"),tr("好友添加成功！！！"));

    }if(msg=="no"){

        QMessageBox::information(this,tr("error"),tr("数据库没有！！！"));
    }
    if(msg=="error"){
        QMessageBox::information(this,tr("error"),tr("输入错误！！！"));
    }
}

void CCmyCharDialog::open()
{

}
///////////////////////////////////////////////////////////////////////////////////////////
//好友 1
void CCmyCharDialog::on_QtoolBtn2_1_clicked()
{
    QString str=tr("当前会话:")+toolBtn2_1->text();
    ui->label->setText(str);
    ui->pushButton->setEnabled(true);
    this->jeshou=toolBtn2_1->text();
    //    QMessageBox::information(this,tr("error"),toolBtn2_1->text());
}
//好友 2
void CCmyCharDialog::on_QtoolBtn2_2_clicked()
{
    QString str=tr("当前会话:")+toolBtn2_2->text();
    ui->label->setText(str);
    ui->pushButton->setEnabled(true);
    this->jeshou=toolBtn2_2->text();
}
//好友 3
void CCmyCharDialog::on_QtoolBtn3_1_clicked()
{
    QString str=tr("当前会话:")+toolBtn3_1->text();
    ui->label->setText(str);
    ui->pushButton->setEnabled(true);
    this->jeshou=toolBtn3_1->text();
}
// 好友 4
void CCmyCharDialog::on_QtoolBtn3_2_clicked()
{
    QString str=tr("当前会话:")+toolBtn3_1->text();
    ui->label->setText(str);
    ui->pushButton->setEnabled(true);
    this->jeshou=toolBtn3_1->text();
}

//视频聊天
void CCmyCharDialog::on_pushButton_7_clicked()
{
    //发送内容
    QString msg=username+tr("%")+tr("shiping")+tr("%")+tr("shiping")+tr("%")+this->jeshou;
    mytcpSocket->write(msg.toStdString().data());

    mycamaraGet=new camaraGet();
    mycamaraGet->show();

}
//发文件
void CCmyCharDialog::on_pushButton_8_clicked()
{
    //发送内容
    QString msg=username+tr("%")+tr("winjian")+tr("%")+tr("winjian")+tr("%")+this->jeshou;
    mytcpSocket->write(msg.toStdString().data());
    send = new sendMainWindow();
    send->show();
}
