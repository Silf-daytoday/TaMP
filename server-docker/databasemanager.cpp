#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager* DatabaseManager::m_instance = nullptr;

DatabaseManager::DatabaseManager() {
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("project_data.db");

    if (!m_database.open()) {
        qDebug() << "Не удалось открыть БД:" << m_database.lastError().text();
    } else {
        qDebug() << "База данных успешно открыта.";

        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS messages ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "message TEXT, "
                   "aes_key TEXT, "
                   "sha_hash TEXT, "
                   "image_path TEXT)");
        query.exec("CREATE TABLE IF NOT EXISTS users ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "login TEXT UNIQUE, "
                   "password TEXT)");

    }
}

DatabaseManager* DatabaseManager::getInstance() {
    if (!m_instance)
        m_instance = new DatabaseManager();
    return m_instance;
}

QSqlDatabase DatabaseManager::getDatabase() {
    return m_database;
}
