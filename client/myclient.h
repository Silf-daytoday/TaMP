/**
 * @file myclient.h
 * @brief TCP Client implementation for connecting to the server
 * 
 * This class implements a TCP client that:
 * - Connects to the server
 * - Sends commands
 * - Receives and processes server responses
 * - Handles connection events
 */

#pragma once
#include <QTcpSocket>
#include <QObject>

class MyClient : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructor initializes the client socket
     * @param parent Parent QObject
     */
    explicit MyClient(QObject* parent = nullptr);

    /**
     * @brief Connects to the server
     * Attempts to establish a connection to the server at localhost:33333
     */
    void connectToServer();

    /**
     * @brief Sends a command to the server
     * @param command The command to send
     * 
     * Available commands:
     * - reg login:password - Register new user
     * - auth login:password - Authenticate user
     * - enc message - Encrypt message
     * - hash data - Generate hash
     * - solve problem - Solve problem
     * - hide data - Hide data in image
     */
    void sendCommand(const QString& command);

private slots:
    /**
     * @brief Handles successful connection to the server
     * Automatically sends a test registration command
     */
    void onConnected();

    /**
     * @brief Handles incoming data from the server
     * Processes and displays server responses
     */
    void onReadyRead();

    /**
     * @brief Handles disconnection from the server
     * Logs the disconnection event
     */
    void onDisconnected();

private:
    QTcpSocket* m_socket;  ///< Client socket for server communication
};
