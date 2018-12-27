#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QAbstractSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void connecttohost();
    void doConnect();
    void connected();
    void logIn();
    void list(const QString &dir);
    void downloadFile();
    void disconnected(); 
    void wait();

    enum TransferMode {
            Active,
            Passive
        };


signals:


public slots:
    void readyRead();
    void readyRead1();

private:
    QTcpSocket *socket;
    QTcpSocket *socket1;


};

#endif // CLIENT_H
