/**
 * @file main.cpp
 * @brief Main entry point for the feature server application
 * 
 * This file contains the main function that:
 * - Creates the application instance
 * - Initializes the feature server with AES encryption,
 *   SHA-384 hashing, and steganography capabilities
 * - Starts the event loop
 */

#include <QCoreApplication>
#include "mytcpserver.h"

/**
 * @brief Main function
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 * @return Exit code
 * 
 * Creates the application instance, initializes the feature server
 * with advanced capabilities (AES, SHA-384, steganography),
 * and starts the event loop to handle client connections.
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    // Create and initialize the feature server
    MyTcpServer server;
    
    return a.exec();
}
