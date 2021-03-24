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

    QString ip = "127.0.0.1";
    for(int i=0; i < MAX_TCP_SERVER_NUM; i++)
		TcpServerConnect(ip, 8888 + i);


	// 这里手动发送连接的第一个客户端信息
    connect(ui->pushButton, &QPushButton::clicked, this, [=]{
        QString s = "12312313";
        toSendData(s, TCP_SERVER_MODE, 1);
    });


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
    }

    connect(mtcpServer, SIGNAL(addClientLink(QString,int)),this, SLOT(addClientLink(QString, int)));
    connect(mtcpServer, SIGNAL(removeClientLink(QString,int)), this, SLOT(removeClientLink(QString, int)));

    connect(mtcpServer, SIGNAL(updateTcpServer(char*,int,int)), this, SLOT(tcpServerDataRecv(char*, int, int)));
    connect(this, SIGNAL(sendDataToClient(char*,int,int,int)), mtcpServer, SLOT(sendDataToClient(char*,int,int,int)));
    return true;

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

	}
	else if (flag == UDP_MODE)
	{

	}


}







