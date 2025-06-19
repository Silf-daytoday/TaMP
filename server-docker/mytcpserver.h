#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QtNetwork>
#include <QByteArray>
#include <QDebug>
#include <QList>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
public slots:
    void slotNewConnection();
    void slotClientDisconnected(QTcpSocket* socket);
    void slotServerRead(QTcpSocket* socket);
private:
    QTcpServer *m_tcpServer;
    QList<QTcpSocket*> m_clients;
};

#endif // MYTCPSERVER_H
