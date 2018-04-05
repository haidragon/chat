#include "tcpserver.h"
#include <QMessageBox>
TcpServer::TcpServer(QWidget *parent,Qt::WindowFlags f)
    : QDialog(parent,f)
{
    setWindowTitle(tr("TCP Server"));
    ContentListWidget = new QListWidget;
    PortLabel = new QLabel(tr("接听端口："));
    PortLineEdit = new QLineEdit;
    sendQtextEdit = new QTextEdit;
    CreateBtn = new QPushButton(tr("群聊"));
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(ContentListWidget,0,0,1,2);
    mainLayout->addWidget(PortLabel,1,0);
    mainLayout->addWidget(PortLineEdit,1,1);
    mainLayout->addWidget(sendQtextEdit,2,0,1,2);
    mainLayout->addWidget(CreateBtn,3,0,1,2);


    port=4444;
    PortLineEdit->setText(QString::number(port));
    //启动服务器
    server = new Server(this,port);
    //检测更新服务器信号
    connect(server,SIGNAL(updateServer(QString,int)),this,SLOT(updateServer(QString,int)));
    connect(CreateBtn,SIGNAL(clicked()),this,SLOT(slotsend()));
}

TcpServer::~TcpServer()
{
    
}
//创建聊天室
void TcpServer::slotCreateServer()
{

}


//点击群发
void TcpServer::slotsend()
{
    if(sendQtextEdit->toPlainText()==""){
        QMessageBox::information(this,tr("error"),tr("陈独秀同志,你要说啥！！！"));
        return;
    }
    //调群发函数
//    qDebug()<<"陈独秀同志:"<<sendQtextEdit->toPlainText();
    server->senClients(sendQtextEdit->toPlainText(),sendQtextEdit->toPlainText().length());
    QMessageBox::information(this,tr("ok"),tr("陈独秀同志，消息已发送！"));
    sendQtextEdit->clear();
}

//更新服务器
void TcpServer::updateServer(QString msg,int length)
{
    ContentListWidget->addItem(msg.left(length));

//    PortLineEdit->setText(msg);
}
