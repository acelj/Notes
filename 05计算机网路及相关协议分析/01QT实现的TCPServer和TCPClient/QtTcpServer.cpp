#include "QtTcpServer.h"

QtTcpServer::QtTcpServer(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

	tcpServer = new QTcpServer(this);

	tcpServer->listen(QHostAddress::Any, 8888);
	setWindowTitle("Server  8888");

	connect(tcpServer, &QTcpServer::newConnection,this, [=] {    //  多加了this参数
		// 取出建立好连接的套接字
		tcpSocket = tcpServer->nextPendingConnection();

		// 
		QString ip = tcpSocket->peerAddress().toString();
		qint16 port = tcpSocket->peerPort();
		QString tmp = QStringLiteral("[%1:%2] : 连接成功!").arg(ip).arg(port);
		
		ui.textEdit_DATA->append(tmp);

		connect(tcpSocket, &QTcpSocket::readyRead, this, [=] {
			QByteArray str = tcpSocket->readAll();
			ui.textEdit_DATA->append(str);
		});
	});

	connect(ui.pushButton_SEND, &QPushButton::clicked, this, [=] {
		if (tcpSocket == nullptr)
		{
			return;
		}
		QString str = ui.textEdit_DATA->toPlainText();
		tcpSocket->write(str.toUtf8().data());
	});

	connect(ui.pushButton_DISCONNECT, &QPushButton::clicked, this, [=] {
		if (tcpSocket == nullptr) return;
		tcpSocket->disconnectFromHost();
		tcpSocket->close();
		tcpSocket == nullptr;
	});

	connect(ui.pushButton_CLEAR, &QPushButton::clicked, this, [=] {
		ui.textEdit_DATA->clear();
	});
}

QtTcpServer::~QtTcpServer()
{
	delete &ui;
}


