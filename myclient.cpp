/**
 * @file myclient.cpp
 * @brief Implementation of the TCP client functionality
 */

#include "myclient.h"
#include <QDebug>

/**
 * @brief Constructor implementation
 * Initializes the client socket and sets up signal connections
 */
MyClient::MyClient(QObject* parent) : QObject(parent) {
    m_socket = new QTcpSocket(this);
    
    // Connect socket signals to our slots
    connect(m_socket, &QTcpSocket::connected, this, &MyClient::onConnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &MyClient::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &MyClient::onDisconnected);
}

/**
 * @brief Connects to the server
 * Attempts to establish a connection to the server at localhost:33333
 */
void MyClient::connectToServer() {
    m_socket->connectToHost("localhost", 33333);
}

/**
 * @brief Sends a command to the server
 * @param command The command to send
 * 
 * Checks if the socket is connected before sending the command.
 * Appends a newline character to the command for proper server parsing.
 */
void MyClient::sendCommand(const QString& command) {
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        m_socket->write(command.toUtf8());
    } else {
        qDebug() << "Not connected to server";
    }
}

/**
 * @brief Handles successful connection to the server
 * Automatically sends a test registration command
 */
void MyClient::onConnected() {
    qDebug() << "Connected to server";
    // Send test registration command
    sendCommand("reg test:makeMeAdmin");
}

/**
 * @brief Handles incoming data from the server
 * Processes and displays server responses
 */
void MyClient::onReadyRead() {
    QByteArray data = m_socket->readAll();
    qDebug() << "Received from server:" << data;
}

/**
 * @brief Handles disconnection from the server
 * Logs the disconnection event
 */
void MyClient::onDisconnected() {
    qDebug() << "Disconnected from server";
}
