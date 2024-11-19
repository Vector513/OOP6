#include "TcpClient.h"
#include <QDebug>

TcpClient::TcpClient(QObject *parent)
    : QObject(parent)
    , socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &TcpClient::onDataReceived);
    connect(socket, &QTcpSocket::errorOccurred, this, &TcpClient::onErrorOccurred);
}

bool TcpClient::isConnected() const
{
    return socket->state() == QAbstractSocket::ConnectedState;
}

bool TcpClient::connectToServer(const QString &host, quint16 port)
{
    qDebug() << "Подключение к серверу:" << host << port;
    socket->connectToHost(host, port);

    if (!socket->waitForConnected(5000)) {
        qCritical() << "Не удалось подключиться к серверу!" << socket->errorString();
        return false;
    } else {
        qDebug() << "Подключение к серверу завершено успешно!" << host << ":" << port;
        return true;
    }
}

void TcpClient::disconnectFromServer()
{
    socket->disconnectFromHost();
    if (socket->state() != QAbstractSocket::UnconnectedState && !socket->waitForDisconnected(3000)) {
        qWarning() << "Не удалось отключиться от сервера. Принудительное отключение.";
        socket->abort();
    } else {
        qDebug() << "Отключено от сервера.";
    }
}

void TcpClient::sendData(const QString &data)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "Отправка данных:" << data;

        socket->write(data.toUtf8());

        if (!socket->waitForBytesWritten(5000)) {
            qWarning() << "Ошибка при отправке данных:" << socket->errorString();
        } else {
            qDebug() << "Данные отправлены!";
        }
    } else {
        qWarning() << "Нет подключения к серверу!";
    }
}

void TcpClient::onDataReceived()
{
    QByteArray response = socket->readAll();
    emit messageReceived(response);
    qDebug() << "Ответ от сервера:" << response;
}

void TcpClient::onConnected()
{
    qDebug() << "Подключено к серверу!";
}

void TcpClient::onDisconnected()
{
    qDebug() << "Соединение с сервером закрыто.";
}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        qWarning() << "Удалённый хост закрыл соединение!";
        break;
    case QAbstractSocket::HostNotFoundError:
        qWarning() << "Хост не найден!";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qWarning() << "Подключение отклонено!";
        break;
    default:
        qWarning() << "Ошибка сокета:" << socket->errorString();
        break;
    }
}
