#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtTcpServer.h"

#include <QTcpServer>	// �����׽���
#include <QTcpSocket> 	// ͨ���׽���

class QtTcpServer : public QWidget
{
    Q_OBJECT

public:
    QtTcpServer(QWidget *parent = Q_NULLPTR);
	~QtTcpServer();

private:
    Ui::QtTcpServerClass ui;

	QTcpServer* tcpServer{ nullptr };  // �����׽���
	QTcpSocket* tcpSocket{ nullptr };   // ͨ���׽���
};
