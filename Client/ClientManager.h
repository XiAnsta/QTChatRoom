#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include "ChatProtocol.h"
#include <QDir>

class ClientManager : public QObject
{
    Q_OBJECT
public:
    //explicit ClientManager(QHostAddress ip = QHostAddress::LocalHost, ushort port = 4500, QObject *parent = nullptr);
    explicit ClientManager(QHostAddress ip, ushort port, QObject *parent = nullptr);
    void connnectToServer();

    void sendMessage(QString message, QString receiver);
    void sendName(QString name);
    void sendStatus(ChatProtocol::Status status);
    void sendIsTyping();

    void sendInitSendingFile(QString fileName);
    void sendAcceptFile();
    void sendRejectFile();

signals:
    void connected();
    void disconnected();
//    void dataReceived(QByteArray data);
    void textMessageReceived(QString message);
    void isTyping();
    void nameChanged(QString name);
    void statusChanged(ChatProtocol::Status status);

    void initReceivingFile(QString clientName,QString fileName,qint64 fileSize);
    void rejectReceivingFile();

    void connectionACK(QString myName, QStringList clientsName);
    void newClientConnectedToServer(QString clientName);
    void clientNameChanged(QString prevName, QString clientName);
    void clientDisconnected(QString clientName);

private slots:
    void readyRead();
private:
    QTcpSocket *_socket;
    QHostAddress _ip;
    ushort _port;
    ChatProtocol _protocol;
    QString _tmpFileName;

private: //methods
    void setupClient();
    void sendFile();
};

#endif // CLIENTMANAGER_H
