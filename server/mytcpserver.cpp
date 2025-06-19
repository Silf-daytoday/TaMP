#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include <QString>

#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>

MyTcpServer::~MyTcpServer()
{
    m_server->close();
    //server_status=0;
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    m_server = new QTcpServer(this);
    connect(m_server, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);
    
    if(!m_server->listen(QHostAddress::Any, 33333)){
        qDebug() << "Server failed to start";
    } else {
        qDebug() << "Server started successfully";
    }
}

void MyTcpServer::slotNewConnection()
{
    QTcpSocket* clientSocket = m_server->nextPendingConnection();
    m_clients.append(clientSocket);
    
    connect(clientSocket, &QTcpSocket::readyRead, this, [this, clientSocket]() {
        slotServerRead(clientSocket);
    });
    connect(clientSocket, &QTcpSocket::disconnected, this, [this, clientSocket]() {
        slotClientDisconnected(clientSocket);
    });
}

void MyTcpServer::slotServerRead(QTcpSocket* socket)
{
    QByteArray data = socket->readAll();
    qDebug() << "Received from client:" << data;
    
    // Echo back to the client
    socket->write(data);
}

void MyTcpServer::slotClientDisconnected(QTcpSocket* socket)
{
    m_clients.removeAll(socket);
    socket->deleteLater();
}
