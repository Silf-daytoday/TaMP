/**
 * @file mytcpserver.h
 * @brief Simple Echo Server implementation
 * 
 * This class implements a basic echo server that:
 * - Accepts client connections
 * - Echoes back received messages
 * - Handles basic command processing
 * - Manages client disconnections
 */

#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor initializes the echo server
     * @param parent Parent QObject
     */
    explicit MyTcpServer(QObject *parent = nullptr);
    
    /**
     * @brief Destructor closes the server and cleans up resources
     */
    ~MyTcpServer();

public slots:
    /**
     * @brief Handles new client connections
     * Creates a new socket for the client and sets up signal connections
     */
    void slotNewConnection();

    /**
     * @brief Handles client disconnections
     * Cleans up resources when a client disconnects
     */
    void slotClientDisconnected();

    /**
     * @brief Processes incoming data from clients
     * Echoes back received messages and handles basic commands
     */
    void slotServerRead();

private:
    QTcpServer *m_server;     ///< TCP server instance
    QTcpSocket *m_client;     ///< Current client connection
    //int server_status;
};
#endif // MYTCPSERVER_H
