#include "client.h"
#include <QAbstractSocket>

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    socket->bind(QHostAddress::LocalHost, 100);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Client::connecttohost()
{
    socket->connectToHost(QHostAddress::LocalHost, 21);
}

void Client::sendUsername()
{
    QByteArray username= "USER.danka";
    socket->write(username);
}

void Client::command(const QByteArray &command, const QByteArray &params)
{
    QByteArray sendData = command;
    if (!params.isEmpty())
        sendData += " " + params;
    socket->write(sendData + "\r\n");
}

void Client::readyRead()
{
    QByteArray buffer;
    buffer.append(socket->readAll());
    qDebug() << buffer;

}
