#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtTcpServer.h"

#include <QTcpServer>	// 监听套接字
#include <QTcpSocket> 	// 通信套接字

class QtTcpServer : public QWidget
{
    Q_OBJECT

public:
    QtTcpServer(QWidget *parent = Q_NULLPTR);
	~QtTcpServer();

private:
    Ui::QtTcpServerClass ui;

	QTcpServer* tcpServer{ nullptr };  // 监听套接字
	QTcpSocket* tcpSocket{ nullptr };   // 通信套接字
};
