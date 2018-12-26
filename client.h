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
    void disconnected();

    enum TransferMode {
            Active,
            Passive
        };

    //void logIn(const QString user, const QString password);
    //void command(const QByteArray &command, const QByteArray &params);
   // QTcpSocket *socket;

signals:


public slots:
    void readyRead();
    void readyRead1();
    void logIn();
    void list(const QString &dir);

private:
    QTcpSocket *socket;
    QTcpSocket *socket1;

};

#endif // CLIENT_H
