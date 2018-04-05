#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QTextEdit>
#include "server.h"

class TcpServer : public QDialog
{
    Q_OBJECT
    
public:
    TcpServer(QWidget *parent = 0,Qt::WindowFlags f=0);
    ~TcpServer();    
private:
    QListWidget *ContentListWidget;
    QLabel *PortLabel;
    QLineEdit *PortLineEdit;
    QTextEdit *sendQtextEdit;
    QPushButton *CreateBtn;
    QGridLayout *mainLayout;
    int port;
    Server *server;
public slots:
    void slotCreateServer();
    void slotsend();
    void updateServer(QString,int);
};

#endif // TCPSERVER_H
