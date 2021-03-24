#include "TcpServer.h"

#include <QTcpSocket>

TcpServer::TcpServer(QObject* parent) : QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()), this, SLOT(acceptNewClient()));
}

void TcpServer::acceptNewClient()
{
    int socketDescriptor;
    QTcpSocket *tcpClientSocket = nextPendingConnection();
    socketDescriptor  = tcpClientSocket->socketDescriptor();

    connect(tcpClientSocket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

    // system
    connect(tcpClientSocket, SIGNAL(disconnected()), tcpClientSocket, SLOT(deleteLater()));

    connect(tcpClientSocket, SIGNAL(readyRead()), this, SLOT(clientDataReceived()));

    tcpClientSocketList.append(tcpClientSocket);

    QString cli_port = QString::number(tcpClientSocket->peerPort());
    QString cli_ip_port = tcpClientSocket->peerAddress().toString() + ":" + cli_port;
    emit addClientLink(cli_ip_port, socketDescriptor);
}

void TcpServer::clientDataReceived()
{
    // data receive
    for(int i = 0; i < tcpClientSocketList.count(); i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
        while(item->bytesAvailable() > 0)
        {
            QByteArray datagram;
            datagram.resize(item->bytesAvailable());
            item->read(datagram.data(), datagram.size());
			// 发射信号， 第三个参数是客户端的fd
            emit updateTcpServer((char *)datagram.data(), datagram.size(), item->socketDescriptor());
        }
    }
}

void TcpServer::clientDisconnected()
{
    for(int i = 0; i < tcpClientSocketList.count(); i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->state() == 0)
        {
            QString peerPortStr = QString::number(item->peerPort());
            QString rdClientAddress_Port = item->peerAddress().toString() + ":" + peerPortStr;
            //send the client address and descriptor to NetAssistWidget
            emit removeClientLink(rdClientAddress_Port, item->socketDescriptor());

            tcpClientSocketList.removeAt(i); //remove Client

            break;
        }
    }
}


void TcpServer::sendDataToClient(char *msg, int length, int socketDescriptor, int socketDescriptorEx)
{
    for(int i = 0; i < tcpClientSocketList.count(); i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);

        if(socketDescriptor == 0) {
            if(item->socketDescriptor() != socketDescriptorEx) {
                if(item->write(msg, length) != length)
                {
                    continue;
                }
            }
        } else {
            if(item->socketDescriptor() == socketDescriptor) {
                if(item->write(msg, length) != length)
                {
                    break;
                }
            }
        }
    }
}






