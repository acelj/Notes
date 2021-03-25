#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

#include "tcpserver.h"
#include "define.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // 直接程序创建一个TCP server, 手动写在程序中
    /// @ create server ip and and
    void TcpServerConnect(QString& ip, qint16 port);
    bool CreateTcpServer(QString& ip, qint16 port);

    int TcpClientLinkCnt = 0;
    QList<int> tcpClientSocketFdList;	// Save all client fd  0: all, 后面的客户端
    QList<QString> ipAndPortList;    // Save all client ip and port 

    // TCP Client
    /// @ ip : remote server ip and port
    void TcpClientCreate(QString& ip, qint16 port);

   // UDP Server
    void UdpServerCreate(QString& ip, int port);

   // UDP Client
    void UdpClientCreate(QString& ip, int port);


signals:
    // 服务器发送客户端信号
    void sendDataToClient(char *msg, int length, int socketDescriptor, int socketDescriptorEx);

public slots:
    void tcpServerDataRecv(char* msg, int length, int socketDescriptorEx);

    void addClientLink(QString clientAddrPort, int socketDescriptor);
    void removeClientLink(QString clientAddrPort, int socketDescriptor);

    /// @ msg  send data context
    /// @ flag network mode    TCP_SERVER   TCP_CLIENT   UDP
    /// @ idx  which fd send data
	void toSendData(QString& msg, int flag, int idx);

    // TCP client
    void tcpClientDataRecv();

    // UDP Server
    void udpDataRecv();

private:
    Ui::MainWindow *ui;

    TcpServer* mtcpServer{nullptr};

    // TCP client
    QTcpSocket* tcpClientSocket{nullptr};
    QList<QTcpSocket*> tcpClientSocketList;
    QMap<QTcpSocket*, QString> tcpMapMessage;

    // UDP Server
    QUdpSocket* udpSocket{nullptr};
    QList<QUdpSocket*> udpSocketList;
    QMap<QUdpSocket*, QString> udpServerMap;

    // UDP Client
    QUdpSocket* udpSocketClient{nullptr};
    QMap<QUdpSocket*, QString> udpClientMap;

};

#endif // MAINWINDOW_H
