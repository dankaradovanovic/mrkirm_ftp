#include <QCoreApplication>
#include <client.h>
#include <stdlib.h>
#include <QList>

struct Command {
    QString cmd;
    QString args;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    client.connecttohost();
    //client.sendUsername();

    QList<Command> commands({
            {"cmd.USER", "danka"},// login
            {"cmd.PORT", ""},         // announce port for data connection, args added below.
            //{"cmd.RETR", file}        // retrieve a file
        });

    return a.exec();
}
