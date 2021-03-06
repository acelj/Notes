#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtTCPClient.h"
#include <QTcpSocket>

class QtTCPClient : public QWidget
{
    Q_OBJECT

public:
    QtTCPClient(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtTCPClientClass ui;

	QTcpSocket* tcpSocket{ nullptr };
};
