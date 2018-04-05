#ifndef DIALOG_H
#define DIALOG_H
//mychar
#include "ccmychardialog.h"
#include <QDialog>
#include <QHostAddress>
#include <QTcpSocket>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    //test
    void on_test_clicked();

    void on_regist_pushButton_clicked();

private:
    QString username;
    QString userpasswd;
    Ui::Dialog *ui;
    void cclink();

public:
    bool status;
    QString login;
    int port;
    QHostAddress *serverIP;
    QTcpSocket *tcpSocket;
    //窗口
    CCmyCharDialog* myCCmyCharDialog;
public slots:
    void slotConnected();
    void slotDisconnected();
    void dataReceived();
public slots:
    void ccmyclose();
};

#endif // DIALOG_H
