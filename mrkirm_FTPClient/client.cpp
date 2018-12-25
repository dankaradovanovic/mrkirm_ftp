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
void Client::doConnect()
{
    socket = new QTcpSocket(this);

    //connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    //connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    //connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(logIn()),this, SLOT(logIn()));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    qDebug() << "connecting...";

    // this is not blocking call
    socket->connectToHost(QHostAddress::LocalHost, 21);

    // we need to wait...
    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
    }
}

void Client::connected()
{
    qDebug() << "connected...";

    // Hey server, tell me about you.
    socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");

}
void Client::logIn(const QString username, const QString pass)
{
   QByteArray user = username.toLocal8Bit().constData();
   QByteArray password = pass.toLocal8Bit().constData();
   //socket->write(user.toStdString().c_str());
   socket->write(user, user.size());
   //socket->write(password.toStdString().c_str());
   socket->write(password, password.size());

   socket->waitForBytesWritten();

}

void Client::readyRead()
{
    QByteArray buffer;
    buffer.append(socket->readAll());
    qDebug() << buffer;

}
