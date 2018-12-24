#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void connecttohost();
    void sendUsername();
    void command(const QByteArray &command, const QByteArray &params);
    QTcpSocket *socket;

signals:

public slots:
    void readyRead();


};

#endif // CLIENT_H
