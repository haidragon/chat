#ifndef CCMYCHARDIALOG_H
#define CCMYCHARDIALOG_H
#include "personlist.h"
#include "spingserver.h"
#include "camaraget.h"
#include "sendmainwindow.h"
#include "receivemainwindow.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QToolButton>
#include <QTcpSocket>
#include <QToolBox>
#include<QHostAddress>
#include <QVBoxLayout>

//extern spingserver sping;
namespace Ui {
class CCmyCharDialog;
}

class CCmyCharDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit CCmyCharDialog(QWidget *parent = 0);
    ~CCmyCharDialog();

    personList* ccpersonList;
    //////////////////////////
    QToolBox* QToolBox_1;

    QToolButton* toolBtn1_1;
    QToolButton* toolBtn1_2;
    QToolButton* toolBtn1_3;
    QToolButton* toolBtn1_4;
    QToolButton* toolBtn1_5;

    QToolButton* toolBtn2_1;
    QToolButton* toolBtn2_2;

    QToolButton* toolBtn3_1;
    QToolButton* toolBtn3_2;

    void set(QString use,QString pawssd);
//保存套节字
QTcpSocket *mytcpSocket;
int port;
QHostAddress *serverIP;
void setQTcpSocket(QTcpSocket *);
void setAddandport(int port,QHostAddress *serverIP);
//好友
QMap<QString,  QToolButton*> QToolButtonMap;
// QToolButtonMap;
QVBoxLayout *layout1;

//用于添加好友
QTcpSocket *sqlmytcpSocket;
int sqlport;
QHostAddress *sqlserverIP;
QMap<bool,  QMap<QString,  QToolButton*>> QToolButtonfriendMap;
private:
    //当前用户名
    QString username;
    QString userpasswd;
    QString test;
    QString jeshou;
    Ui::CCmyCharDialog *ui;
    //设置好友
    void setfriend();
    //更新好友列表
    void updatefriends(QString username);
//当用户关闭时
protected:

     void closeEvent(QCloseEvent *event);
signals:
     void myclose();
private slots:

     void on_pushButton_6_clicked();

     void on_pushButton_5_clicked();

     void on_pushButton_4_clicked();

     void on_pushButton_7_clicked();

     void on_pushButton_8_clicked();

public slots:
    void slotConnected();
    void slotDisconnected();
    void dataReceived();
//    void slotSend();
    void on_pushButton_clicked();
     //点击
    void on_QToolButton1_clicked();
    void on_QToolButton2_clicked();
    void on_QToolButton3_clicked();
    void on_QToolButton4_clicked();
    void on_QToolButton5_clicked();
    //toolbox 改变时
    void currentChangedsolts(int index);
    //好友
     void on_QtoolBtn2_1_clicked();
     void on_QtoolBtn2_2_clicked();
     void on_QtoolBtn3_1_clicked();
     void on_QtoolBtn3_2_clicked();
//添加好友
public slots:
    void sqlslotConnected();
    void sqlslotDisconnected();
    void sqldataReceived();

public:
    spingserver* sping;
    void open();
    //
    camaraGet* mycamaraGet;
    //
    sendMainWindow* send;
    //
    receiveMainWindow* myreceivemainwindow;
};

#endif // CCMYCHARDIALOG_H
