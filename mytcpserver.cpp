/**
 * @file mytcpserver.cpp
 * @brief Implementation of the simple echo server functionality
 */

#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include<QString>

/**
 * @brief Destructor implementation
 * Closes the server connection and cleans up resources
 */
MyTcpServer::~MyTcpServer()
{
    m_server->close();
}

/**
 * @brief Constructor implementation
 * Initializes the TCP server and starts listening for connections
 */
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    m_server = new QTcpServer(this);

    // Connect the newConnection signal to our slot
    connect(m_server, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    // Start listening on port 33333
    if(!m_server->listen(QHostAddress::Any, 33333)){
        qDebug() << "Server failed to start";
    } else {
        qDebug() << "Server started successfully";
    }
}

/**
 * @brief Handles new client connections
 * Creates a new socket for the client and sets up signal connections
 */
void MyTcpServer::slotNewConnection(){
    m_client = m_server->nextPendingConnection();
    
    // Send welcome message to the new client
    m_client->write("Hello, World!!! I am echo server made by group 241-351!\r\n");
    
    // Set up signal connections for the new client
    connect(m_client, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(m_client, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
}

/**
 * @brief Processes incoming data from clients
 * Echoes back received messages and handles basic commands
 * 
 * Supported commands:
 * - enc: Encryption command (not implemented)
 * - hash: Hash generation (not implemented)
 * - solve: Problem solving (not implemented)
 * - hide: Image steganography (not implemented)
 */
void MyTcpServer::slotServerRead(){
    QByteArray receivedData = m_client->readAll();
    QString commandInput = QString::fromUtf8(receivedData).trimmed();

    qDebug() << "Received command:" << commandInput;

    // Handle empty commands
    if (commandInput.isEmpty()) {
        m_client->write("Empty command. Please try again.\r\n");
        return;
    }

    // Process different command types
    if (commandInput.startsWith("enc")) {
        m_client->write("ENC: Encryption not implemented yet.\r\n");
    }
    else if (commandInput.startsWith("hash")) {
        m_client->write("HASH: Hash function not implemented yet.\r\n");
    }
    else if (commandInput.startsWith("solve")) {
        m_client->write("SOLVE: Solver not implemented yet.\r\n");
    }
    else if (commandInput.startsWith("hide")) {
        m_client->write("HIDE: Image embedding not implemented yet.\r\n");
    }
    else {
        m_client->write("Unknown command\r\n");
    }
}

/**
 * @brief Handles client disconnections
 * Closes the client connection and cleans up resources
 */
void MyTcpServer::slotClientDisconnected(){
    m_client->close();
}
