#ifndef RECEIVEMAINWINDOW_H
#define RECEIVEMAINWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
class QFile;
class QString;
class QTcpServer;
class QTcpSocket;
namespace Ui {
class receiveMainWindow;
}

class receiveMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit receiveMainWindow(QWidget *parent = 0);
    ~receiveMainWindow();

private:
    Ui::receiveMainWindow *ui;
private slots:
    void accept_connect();
    void recevie_file();
    void show_error(QAbstractSocket::SocketError);
    void on_listenBtn_clicked();

private:
    QTcpServer *server;
    QTcpSocket *receive;
    QString fileName;
    QFile *file;
    /* 已接受数据，总数据，文件名长度 */
    qint64 gotBytes, fileBytes, nameSize;
};

#endif // RECEIVEMAINWINDOW_H
