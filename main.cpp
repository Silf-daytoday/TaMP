/**
 * @file main.cpp
 * @brief Main entry point for the echo server application
 * 
 * This file contains the main function that:
 * - Creates the application instance
 * - Initializes the echo server
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
 * Creates the application instance, initializes the echo server,
 * and starts the event loop to handle client connections.
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    // Create and initialize the echo server
    MyTcpServer server;
    
    return a.exec();
}
