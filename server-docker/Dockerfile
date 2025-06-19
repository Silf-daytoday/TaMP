FROM ubuntu:20.04

# Отключаем интерактивные вопросы (например, про часовой пояс)
ENV DEBIAN_FRONTEND=noninteractive

# Устанавливаем зависимости: Qt, SQLite, компилятор и tzdata
RUN apt-get update && apt-get install -y \
    tzdata \
    qt5-qmake qtbase5-dev build-essential \
    libqt5sql5 libqt5sql5-sqlite sqlite3

# Рабочая директория внутри контейнера
WORKDIR /app

# Копируем весь проект в контейнер
COPY . /app

# Собираем Qt-проект
RUN qmake echoSERVER_241-351.pro && make

# Запускаем сервер
CMD ["./echoSERVER_241-351"]
