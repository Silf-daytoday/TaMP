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
    void slotClientDisconnected(QTcpSocket* socket); // изменено
    void slotServerRead(QTcpSocket* socket);         // изменено
private:
    QTcpServer* m_server;
    QList<QTcpSocket*> m_clients;  ///< List of connected clients
};

#endif // MYTCPSERVER_H
