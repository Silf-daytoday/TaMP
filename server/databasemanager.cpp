#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager* DatabaseManager::m_instance = nullptr;

DatabaseManager* DatabaseManager::getInstance()
{
    if (m_instance == nullptr) {
        m_instance = new DatabaseManager();
    }
    return m_instance;
}

QSqlDatabase DatabaseManager::getDatabase()
{
    return m_database;
}

DatabaseManager::DatabaseManager()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("server.db");
    
    if (!m_database.open()) {
        qDebug() << "Error: Failed to open database:" << m_database.lastError().text();
    } else {
        qDebug() << "Database opened successfully";
        
        // Create tables if they don't exist
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS users ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "username TEXT UNIQUE NOT NULL,"
                  "password TEXT NOT NULL,"
                  "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
                  ")");
                  
        query.exec("CREATE TABLE IF NOT EXISTS messages ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "sender_id INTEGER NOT NULL,"
                  "content TEXT NOT NULL,"
                  "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
                  "FOREIGN KEY (sender_id) REFERENCES users(id)"
                  ")");
    }
}
