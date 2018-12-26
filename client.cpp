#include "client.h"
#include <QAbstractSocket>
#include <QDir>

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    socket->bind(QHostAddress::LocalHost, 100);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    /*connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    //connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(logIn()),this, SLOT(logIn()));*/

}

void Client::connecttohost()
{
    socket->connectToHost(QHostAddress::LocalHost, 21);
}
void Client::doConnect()
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    qDebug() << "connecting...";


    socket->connectToHost(QHostAddress::LocalHost, 21);

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
void Client::logIn()
{
    qDebug() << "Username:";
    QTextStream s(stdin);
    QString user = s.readLine();

    qDebug() << "Password:";
    QTextStream p(stdin);
    QString pass = p.readLine();

    QString u = "USER ";
    u += user;
    u += "\r\n\r\n";

    QString pa = "PASS ";
    pa += pass;
    pa += "\r\n\r\n";

    socket->write(u.toStdString().c_str());
    socket->write(pa.toStdString().c_str());
    socket->waitForBytesWritten();

}

void Client::list(const QString &dir)
{
    socket->write("PWD ");
    socket->write("TYPE A\r\n");
    socket->write(Passive ? "PASV\r\n" : "PORT\r\n");

    socket1 = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead1()),this, SLOT(readyRead1()));
    socket1->bind(QHostAddress::LocalHost, 101);
    socket1->connectToHost(QHostAddress::LocalHost, 1024);

    if (dir.isEmpty())
       socket1->write("LIST\r\n");
    else
       socket1->write("LIST -al \r\n\r\n");

}

void Client::readyRead()
{
    QByteArray buffer;
    buffer.append(socket->readAll());
    qDebug() << buffer;

}
void Client::readyRead1()
{
    QByteArray buffer1;
    buffer1.append(socket1->readAll());
    qDebug() << buffer1;

}
void Client::disconnected(){
    socket->write("QUIT \r\n");
    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
    }
}
