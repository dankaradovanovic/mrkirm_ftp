#include "client.h"
#include <QAbstractSocket>
#include <QDir>
#include <QEventLoop>
#include <QTimer>

QByteArray buffer1;

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
    wait();

}
void Client::logIn()
{
    qDebug() << "Username:";
    QTextStream s(stdin);
    QString user = s.readLine();

    QString u = "USER ";
    u += user;
    u += "\r\n\r\n";
    socket->write(u.toStdString().c_str());
    wait();

    qDebug() << "Password:";
    QTextStream p(stdin);
    QString pass = p.readLine();

    QString pa = "PASS ";
    pa += pass;
    pa += "\r\n\r\n";
    socket->write(pa.toStdString().c_str());
    wait();

}

void Client::list(const QString &dir)
{
    socket->write("PWD ");
    socket->write("TYPE A\r\n");
    wait();
    socket->write(Passive ? "PASV\r\n" : "PORT\r\n");
    wait();

    socket1 = new QTcpSocket(this);
    socket1->bind(QHostAddress::LocalHost, 101);
    connect(socket1, SIGNAL(readyRead()),this, SLOT(readyRead1()));
    socket1->connectToHost(QHostAddress::LocalHost, 1024);

    if (dir.isEmpty())
       socket->write("LIST\r\n");
    else{
       socket->write("LIST -al\r\n\r\n");
        wait();
        buffer1.clear();
    }


}

void Client::readyRead()
{
    QByteArray buffer;
    buffer.append(socket->readAll());
    qDebug() << buffer;

}
void Client::readyRead1()
{
    //QByteArray buffer1;
    buffer1.append(socket1->readAll());

    for(int i=0; i<buffer1.size();i++ ){
        buffer1.replace("\r\n","\n                                                          ");
    }

    qDebug() << buffer1;
    wait();


}
void Client::downloadFile()
{
    socket1->connectToHost(QHostAddress::LocalHost, 1024);

     socket->write(Passive ? "PASV\r\n" : "PORT\r\n");
     wait();

     qDebug() << "File to download:";
     QTextStream p(stdin);
     QString filename = p.readLine();
     QString fi = "RETR ";
     fi += filename;
     fi += "\r\n\r\n\r\n\r\n";

     QString f = "SIZE ";
     f += filename;
     f += "\r\n\r\n\r\n\r\n";

     socket->write(f.toStdString().c_str());
      wait();

     socket->write(fi.toStdString().c_str());
     wait();

     QString file_name= "C:/Users/Danka/Desktop/mrkirm/";
     file_name += filename;

     QFile file(file_name);
     file.open(QIODevice::ReadWrite);
     file.write(buffer1);

     file.close();


}

void Client::disconnected(){
    socket->write("QUIT \r\n");
    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
    }
}

void Client::wait()
{
    QEventLoop loop;
    QTimer::singleShot(1000, &loop, SLOT(quit()));
    loop.exec();
}
