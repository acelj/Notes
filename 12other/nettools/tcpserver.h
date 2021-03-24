#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(QObject* parent = 0);
    QList<QTcpSocket*> tcpClientSocketList;

signals:
    void updateTcpServer(char*, int, int);
    /// @ QString : client ip and port
    /// @ int :     新连接的描述符
    void addClientLink(QString, int);

    /// @ QString : client ip and port
    /// @ int :     tcp 客户端的state =0 的描述符
    void removeClientLink(QString, int);

public slots:
    void clientDisconnected();

    /// 发送信息给指定的client
    void sendDataToClient(char *msg, int length, int socketDescriptor, int socketDescriptorEx);
    void acceptNewClient();    // accept a new connection
    void clientDataReceived();

};

#endif // TCPSERVER_H
