#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject
{
    Q_OBJECT

public:
    TcpClient(QObject *parent = nullptr);
    bool isConnected() const;
    bool connectToServer(const QString &host, quint16 port);
    void disconnectFromServer();
    void sendData(const QString &data);

signals:
    void messageReceived(const QByteArray &response);

private slots:
    void onConnected();
    void onDisconnected();
    void onDataReceived();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *socket;
};

#endif // TCPCLIENT_H
