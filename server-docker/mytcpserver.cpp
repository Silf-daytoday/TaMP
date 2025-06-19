#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include <QString>

#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>

MyTcpServer::~MyTcpServer()
{
    m_tcpServer->close();
    //server_status=0;
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    m_tcpServer = new QTcpServer(this);

    connect(m_tcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!m_tcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        //server_status=1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection(){
    QTcpSocket *clientSocket = m_tcpServer->nextPendingConnection();
    m_clients.append(clientSocket);

    clientSocket->write("Hello, World!!! I am echo server!\r\n");

    connect(clientSocket, &QTcpSocket::readyRead, this, [=](){
        this->slotServerRead(clientSocket);
    });

    connect(clientSocket, &QTcpSocket::disconnected, this, [=](){
        this->slotClientDisconnected(clientSocket);
    });
}

void MyTcpServer::slotServerRead(QTcpSocket* socket){
    QByteArray array = socket->readAll();
    QString input = QString::fromUtf8(array).trimmed();

    qDebug() << "Получена команда:" << input;

    if (input.startsWith("reg ")) {
        QStringList parts = input.mid(4).split(":");
        if (parts.size() != 2) {
            socket->write("Неверный формат. Используй: reg логин:пароль\r\n");
            return;
        }

        QString login = parts[0].trimmed();
        QString password = parts[1].trimmed();

        QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
        QSqlQuery query;

        query.prepare("SELECT id FROM users WHERE login = :login");
        query.bindValue(":login", login);
        if (query.exec() && query.next()) {
            socket->write("Ошибка: пользователь уже существует\r\n");
            return;
        }

        query.prepare("INSERT INTO users (login, password) VALUES (:login, :password)");
        query.bindValue(":login", login);
        query.bindValue(":password", password);

        if (query.exec()) {
            socket->write("Регистрация успешна\r\n");
        } else {
            socket->write("Ошибка при регистрации\r\n");
        }

        return;
    }

    if (input.startsWith("auth ")) {
        QStringList parts = input.mid(5).split(":");
        if (parts.size() != 2) {
            socket->write("Неверный формат. Используй: auth логин:пароль\r\n");
            return;
        }

        QString login = parts[0].trimmed();
        QString password = parts[1].trimmed();

        QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
        QSqlQuery query;

        query.prepare("SELECT password FROM users WHERE login = :login");
        query.bindValue(":login", login);
        if (query.exec() && query.next()) {
            QString storedPassword = query.value(0).toString();
            if (storedPassword == password) {
                socket->write("Авторизация успешна\r\n");
            } else {
                socket->write("Ошибка: неверный пароль\r\n");
            }
        } else {
            socket->write("Ошибка: пользователь не найден\r\n");
        }

        return;
    }

    if (input.startsWith("enc")) {
        QSqlDatabase db = DatabaseManager::getInstance()->getDatabase();
        QSqlQuery query;
        query.prepare("INSERT INTO messages (message, aes_key, sha_hash, image_path) "
                      "VALUES (:msg, :key, :hash, :img)");
        query.bindValue(":msg", input);               // Пока сохраняем просто введённый текст
        query.bindValue(":key", "demo_key");          // Заглушка для AES-ключа
        query.bindValue(":hash", "demo_hash");        // Заглушка для SHA-384
        query.bindValue(":img", "demo_path.png");     // Путь к изображению (заглушка)
        if (query.exec()) {
            socket->write("ENC: Сообщение сохранено в БД\r\n");
        } else {
            socket->write("Ошибка при сохранении в БД\r\n");
            qDebug() << "Ошибка БД:" << query.lastError().text();
        }
    }

    else if (input.startsWith("hash")) {
        socket->write("HASH: заглушка. Хэш пока не реализован.\r\n");
    }
    else if (input.startsWith("solve")) {
        socket->write("SOLVE: заглушка. Решатель ещё не готов.\r\n");
    }
    else if (input.startsWith("hide")) {
        socket->write("HIDE: заглушка. Пока не встраиваем в картинки.\r\n");
    }
    else {
        socket->write("Неизвестная команда\r\n");
    }
}

void MyTcpServer::slotClientDisconnected(QTcpSocket* socket){
    m_clients.removeAll(socket);
    socket->deleteLater();
}
