#include <QCoreApplication>
#include "myclient.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    MyClient* client = new MyClient();
    client->connectToServer();
    return a.exec();
}
