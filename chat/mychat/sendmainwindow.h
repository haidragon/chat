#ifndef SENDMAINWINDOW_H
#define SENDMAINWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
class QByteArray;
class QFile;
class QString;
class QTcpSocket;

namespace Ui {
class sendMainWindow;
}

class sendMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit sendMainWindow(QWidget *parent = 0);
    ~sendMainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void start_transfer();
    void continue_transfer(qint64);
    void show_error(QAbstractSocket::SocketError);

private:
    Ui::sendMainWindow *ui;
    QTcpSocket *send;
    QFile *file;
    QString fileName;
    /* 总数据大小，已发送数据大小，剩余数据大小，每次发送数据块大小 */
    qint64 fileBytes, sentBytes, restBytes, loadBytes;
};

#endif // SENDMAINWINDOW_H
