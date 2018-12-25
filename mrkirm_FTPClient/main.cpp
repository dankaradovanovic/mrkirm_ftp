#include <QCoreApplication>
#include <client.h>
#include <stdlib.h>
#include <QList>
#include <QObject>

struct Command {
    QString cmd;
    QString args;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    client.doConnect();
    client.connected();

    qDebug() << "Username:";
    QTextStream s(stdin);
    QString username = s.readLine();

    qDebug() << "Password required for user";
    QTextStream p(stdin);
    QString pass = p.readLine();
    client.logIn(username, pass);


    return a.exec();
}
