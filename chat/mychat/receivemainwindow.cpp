#include "receivemainwindow.h"
#include "ui_receivemainwindow.h"
#include <iostream>
#include <QDataStream>
#include <QFile>
#include <QHostAddress>
#include <QTcpServer>
#include <QTcpSocket>

const quint16 PORT = 3333;
const int DATA_STREAM_VERSION = QDataStream::Qt_4_8;

receiveMainWindow::receiveMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::receiveMainWindow)
{
    ui->setupUi(this);
    /* 进度条调零 */
    ui->recvProg->setValue(0);
    /* 启用监听按钮 */
    ui->listenBtn->setEnabled(true);
    fileBytes = gotBytes = nameSize = 0;
    file = Q_NULLPTR;
    receive = Q_NULLPTR;
    server = new QTcpServer(this);
    /* 连接请求 -> 接受连接 */
    connect(server, SIGNAL(newConnection()),
            this, SLOT(accept_connect()));
}

receiveMainWindow::~receiveMainWindow()
{
    delete ui;
    delete server;
}


/*--- 接受连接请求 ---*/
void receiveMainWindow::accept_connect()
{
    receive = server->nextPendingConnection();
    /* 有数据到 -> 接受数据 */
    connect(receive, SIGNAL(readyRead()),
            this, SLOT(recevie_file()));
    /* socket出错 -> 出错处理 */
    connect(receive, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(show_error(QAbstractSocket::SocketError)));
    ui->stLabel->setText(QString("Connection Established!"));
    gotBytes = 0;
    server->close();
}

/*--- 接收文件 ---*/
void receiveMainWindow::recevie_file()
{
    QDataStream in(receive);
    in.setVersion(DATA_STREAM_VERSION);

    /* 首部未接收/未接收完 */
    if(gotBytes <= 2 * sizeof(qint64))
    {
        if(!nameSize) // 前两个长度字段未接收
        {
            if(receive->bytesAvailable() >= 2 * sizeof(qint64))
            {
                in >> fileBytes >> nameSize;
                gotBytes += 2 * sizeof(qint64);
                ui->recvProg->setMaximum(fileBytes);
                ui->recvProg->setValue(gotBytes);
            }
            else // 数据不足，等下次
               return;
        }
        else if(receive->bytesAvailable() >= nameSize)
        {
            in >> fileName;
            gotBytes += nameSize;
            ui->recvProg->setValue(gotBytes);
            std::cout << "--- File Name: "
                      << fileName.toStdString() << std::endl;
        }
        else // 数据不足文件名长度，等下次
            return;
    }

    /* 已读文件名、文件未打开 -> 尝试打开文件 */
    if(!fileName.isEmpty() && file == Q_NULLPTR)
    {

        QString str=tr("/Users/allenboy/Desktop/")+fileName;
        file = new QFile(str);

        if(!file->open(QFile::WriteOnly)) // 打开失败
        {
            std::cerr << "*** File Open Failed ***" << std::endl;
            delete file;
            file = Q_NULLPTR;
            return;
        }
        ui->stLabel->setText(QString("Open %1 Successfully!").arg(fileName));
    }
    if(file == Q_NULLPTR) // 文件未打开，不能进行后续操作
        return;

    if(gotBytes < fileBytes) // 文件未接收完
    {
        gotBytes += receive->bytesAvailable();
        ui->recvProg->setValue(gotBytes);

        file->write(receive->readAll());
    }
    if(gotBytes == fileBytes) // 文件接收完
    {
        receive->close(); // 关socket
        file->close(); // 关文件
        delete file;
        ui->stLabel->setText(QString("Finish receiving %1").arg(fileName));
        ui->listenBtn->setEnabled(true);
    }
}

/*--- 出错处理 ---*/
void receiveMainWindow::show_error(QAbstractSocket::SocketError)
{
    std::cerr << "*** Socket Error ***" << std::endl;
    qDebug() << receive->errorString();
    receive->close(); // 关cocket
    receive = Q_NULLPTR;
    file = Q_NULLPTR;
    fileName.clear(); // 清空文件名
    fileBytes = gotBytes = nameSize = 0;
    ui->recvProg->reset(); // 进度条归零
    ui->listenBtn->setEnabled(true); // 启用监听按钮
    ui->stLabel->setText(QString("*** SOCKET ERROR"));
}

//listen
void receiveMainWindow::on_listenBtn_clicked()
{
    /* 禁用监听按钮 */
    ui->listenBtn->setEnabled(false);
    if(!server->listen(QHostAddress::Any, PORT))
    {
        std::cerr << "*** Listen to Port Failed ***" << std::endl;
        qDebug() << server->errorString();
        close();
        ui->listenBtn->setEnabled(false);
        return;
    }
    ui->stLabel->setText(QString("Listing to Port %1").arg(PORT));
}
