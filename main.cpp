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
    client.logIn();

    client.list("Arduino");
    client.downloadFile();

    client.disconnected();


    return a.exec();
}
