#include "QtTCPClient.h"
#include <qdebug.h>
#include <QHostAddress>

QtTCPClient::QtTCPClient(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

	// 获取本机的ip地址
	QHostAddress localip = QHostAddress(QHostAddress::LocalHost);
	QString strip = localip.toString();
	qDebug() << strip;

	tcpSocket = new QTcpSocket(this);
	setWindowTitle("Client");
	connect(tcpSocket, &QTcpSocket::connected, [] {
		qDebug() << QStringLiteral("已经建立好连接");
	});

	connect(tcpSocket, &QTcpSocket::readyRead, [=] {
		
		// read server data  ...
		QByteArray data = tcpSocket->readAll();
		ui.textEdit_DATA->append(data);

	});

	connect(ui.pushButton_CONNECT, &QPushButton::clicked, this, [=] {
		QString ip = ui.lineEdit_IP->text();
		qint16 port = ui.lineEdit__PORT->text().toInt();

		tcpSocket->connectToHost(QHostAddress(ip), port);
	});

	connect(ui.pushButton_DISCONNECT, &QPushButton::clicked, this, [=] {
		tcpSocket->disconnectFromHost();
		tcpSocket->close();
	});

	connect(ui.pushButton_SEND, &QPushButton::clicked, this, [=] {
		QString data = ui.textEdit_DATA->toPlainText();
		tcpSocket->write(data.toUtf8().data());
	});

}
