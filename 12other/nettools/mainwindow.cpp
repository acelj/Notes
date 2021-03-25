#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <qdebug.h>
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /// =======TCP Server Test================
    /// 说明：目前可以创建多个服务端，然后在外界进行连接
    /// 功能： 外界哪个客户端发过来的信息，可以直接显示客户端的ip + port
    /// 可以通过服务器向执行的client 发送信息
    /// 取消连接还没有进行测试
//    QString ip = "127.0.0.1";
//    for(int i=0; i < MAX_TCP_SERVER_NUM; i++)   // MAX_TCP_SERVER_NUM   10
//        TcpServerConnect(ip, TCP_SERVER_START_PORT + i);   // 8888

//    // 这里手动发送连接的第一个客户端信息
//    connect(ui->pushButton, &QPushButton::clicked, this, [=]{
//        QString s = "12312313";
//        toSendData(s, TCP_SERVER_MODE, 1);
//    });

    /// =======TCP Client Test================
    /// 说明：目前可以直接创建多个客户端，然后通过指定第几个client 发送给建立连接的server 信息
    /// 取消连接还没有测试，应该有问题
    QString ip = "127.0.0.1";
    for(int i=0; i<5; i++)
    {
        TcpClientCreate(ip, TCP_CLIENT_START_PORT - i);   // 9999
    }
    connect(ui->pushButton, &QPushButton::clicked, this,[=]{
        QString s = "123123123123213";
        toSendData(s, TCP_CLIENT_MODE, 1);
    });


    /// =======UDP Server Test ===============
//    QString ip = "127.0.0.1";
//    for(int i=0; i<5; i++)
//        UdpServerCreate(ip, UDP_SERVER_START_PORT + i); // 8866

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TcpServerConnect(QString& ip, qint16 port)
{
    if(!CreateTcpServer(ip, port))
    {
        QMessageBox::information(this, tr("error"), tr("please sure ip and port!"));
        qDebug() << "Error, please sure ip and port!";
        return ;
    }
    qDebug() << "建立服务器成功！";
}

bool MainWindow::CreateTcpServer(QString &ip, qint16 port)
{
    mtcpServer = new TcpServer(this);

    QHostAddress ipAddr;
    ipAddr.setAddress(ip);
    if(!mtcpServer->listen(ipAddr, port))
    {
        return false;
        QMessageBox::information(this, tr("error"), tr("please sure ip and port!"));   //< 在上面的函数中已经实现
    }

    connect(mtcpServer, SIGNAL(addClientLink(QString,int)),this, SLOT(addClientLink(QString, int)));
    connect(mtcpServer, SIGNAL(removeClientLink(QString,int)), this, SLOT(removeClientLink(QString, int)));

    connect(mtcpServer, SIGNAL(updateTcpServer(char*,int,int)), this, SLOT(tcpServerDataRecv(char*, int, int)));
    connect(this, SIGNAL(sendDataToClient(char*,int,int,int)), mtcpServer, SLOT(sendDataToClient(char*,int,int,int)));
    return true;
}

void MainWindow::TcpClientCreate(QString &ip, qint16 port)
{
    QHostAddress remoteServerIp;
    if(!remoteServerIp.setAddress(ip))
    {
        qDebug() << "connect TCP server ip address failed!";
        return ;
    }
    tcpClientSocket = new QTcpSocket(this);
    tcpClientSocketList.append(tcpClientSocket);  // 可以不要
    tcpMapMessage[tcpClientSocket] = ip + ": "+ QString::number(port) ;   // 根据socket 保存 remote server ip

    tcpClientSocket->connectToHost(remoteServerIp, port);
    if(!tcpClientSocket->waitForConnected(2000))
    {
        qDebug() << "try connect ["+ ip + "] server failed?????????????????";
        return ;
    }
    qDebug() << "connect ["+ ip + ":"+ QString::number(port) + "] server success.........................";

    // connect(tcpClientSocket, SIGNAL(readyRead()), this, SLOT(tcpClientDataRecv(port)));
//    connect(tcpClientSocket, &QTcpSocket::channelReadyRead(int), this, [this](int port){
//        qDebug() << port << "+++++++++++++++++++++++";
//        //tcpClientDataRecv(ip, port);
//    });

    connect(tcpClientSocket, SIGNAL(readyRead()), this, SLOT(tcpClientDataRecv()));

}

void MainWindow::UdpServerCreate(QString &ip, int port)
{
    udpSocket = new QUdpSocket(this);

    bool re = udpSocket->bind(port);
    if(!re)
    {
        qDebug() << "udp server bind port failed!????????????????????????????";
        return ;
    }
    qDebug() << "udp server bind port success!.......................";

    udpSocketList.append(udpSocket);
    udpServerMap[udpSocket] = ip + ":" + QString::number(port);


    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(udpDataRecv()));
}

void MainWindow::UdpClientCreate(QString &ip, int port)
{

}

void MainWindow::tcpServerDataRecv(char *msg, int length, int socketDescriptorEx)
{
	int idx = tcpClientSocketFdList.indexOf(socketDescriptorEx);
    QString str = ipAndPortList.at(idx); // 肯定是有数据的
    qDebug() << "+++";
    //qDebug() << tr("[") + QDateTime::currentDateTime().time()
    qDebug() << tr("[") + QDateTime::currentDateTime().time().toString() + tr(" ") + str + tr("]") + msg;
}

void MainWindow::addClientLink(QString clientAddrPort, int socketDescriptor)
{
    if(TcpClientLinkCnt == 0)
    {
        tcpClientSocketFdList.clear();
        tcpClientSocketFdList.append(0);
		ipAndPortList.append("0");
    }
    TcpClientLinkCnt ++;
    tcpClientSocketFdList.append(socketDescriptor);
    ipAndPortList.append(clientAddrPort);
    qDebug() << "addClientLink()... ip and port = " << clientAddrPort;
}

void MainWindow::removeClientLink(QString clientAddrPort, int socketDescriptor)
{
    if(socketDescriptor != -1)
    {
        return ;
    }
    if(TcpClientLinkCnt <= 1)
    {
        tcpClientSocketFdList.clear();
    }
    else
    {
        // 删除指定的客户端ip
        TcpClientLinkCnt --;
        int idx = ipAndPortList.indexOf(clientAddrPort);
        ipAndPortList.removeAt(idx);
		tcpClientSocketFdList.removeAt(idx);
		// qDebug() << "这里需要检查ipAndPortList 是否正确" << ipAndPortList[0];
		// mtcpServer->clientDisconnected();
    }
}

void MainWindow::toSendData(QString& msg, int flag = 1, int idx = 1)
{
	QByteArray datagram;
	datagram = msg.toLocal8Bit();
	
	if (datagram.size() == 0)
	{
		return;
	}
	// int flag = TCP_SERVER_MODE;  // 这里是选择的协议类型
	if (flag == TCP_SERVER_MODE)
	{
		// int idx = 1;   // 先写成发送固定的客户端程序， 连接的第一个客户端
		if (idx == 0)
		{
			emit sendDataToClient((char*)datagram.data(), datagram.size(), 0, 0);
		}
		else
		{
			emit sendDataToClient((char*)datagram.data(), datagram.size(), tcpClientSocketFdList.at(idx), 0);
		}
	}
	else if (flag == TCP_CLIENT_MODE)
	{
        // 用指定的 tcpSocket 发送信息
        tcpClientSocketList.at(idx -1)->write(datagram.data(), datagram.size());
	}
	else if (flag == UDP_MODE)
	{
        // 用指定的udpSocket 发送信息, 这个需要远程ip and port

        // udpSocketList.at(idx - 1)->writeDatagram(datagram.data(), datagram.size(), remoteIp, remotePort);
	}


}

void MainWindow::tcpClientDataRecv()
{
//    /// qDebug() << "tcpClientDataRecv.. [" +ip << ":" << QString::number(port) << "]";
//    qDebug() << "tcpClientDataRecv.. ["+ QString::number(port) << "]";
//    while(tcpClientSocket->bytesAvailable() > 0)
//    {
//    QByteArray datagram;
//    datagram.resize(tcpClientSocket->bytesAvailable());
//    tcpClientSocket->read(datagram.data(), datagram.size());

//    QString rcvMsg = QString::fromUtf8(datagram, datagram.size());
//    // 找到连接的哪台server ip and port
//    qDebug() << "datagram is = [" << rcvMsg << "]";

    for(auto it = tcpMapMessage.begin(); it != tcpMapMessage.end(); it ++)
    {
        auto item = it.key();
        while(item->bytesAvailable() > 0)
        {
            QByteArray datagram;
            datagram.resize(item->bytesAvailable());
            item->read(datagram.data(), datagram.size());
            qDebug() <<"[ message from "+ tcpMapMessage[item] + "] " + (char*) datagram.data();
        }
    }
//    int idx = tcpClientSocketFdList.indexOf(socketDescriptorEx);
//    QString str = ipAndPortList.at(idx); // 肯定是有数据的
//    qDebug() << "+++";
//    //qDebug() << tr("[") + QDateTime::currentDateTime().time()
//    qDebug() << tr("[") + QDateTime::currentDateTime().time().toString() + tr(" ") + str + tr("]") + msg;

}

void MainWindow::udpDataRecv()
{
    qDebug() << "udpDataRecv().. ";
    // 一个socket 监听多个udp client 的话， socket应该只保存最后一个

    QHostAddress address;
    quint16 port;
    QString IpAndPort = "";

    for(auto it = udpServerMap.begin(); it != udpServerMap.end(); it ++)
    {
        auto item = it.key();
        while(item->hasPendingDatagrams())
        {
            QByteArray datagram;
            datagram.resize(item->pendingDatagramSize());
            if(datagram.size() <= 0) return;
            item->readDatagram(datagram.data(), datagram.size(), &address, &port);

            IpAndPort = address.toString() + ":" +QString::number(port);
            QString msg = QString::fromUtf8(datagram, datagram.size());

            qDebug() << "data from [" + IpAndPort << "] " << msg;
        }
    }

}







