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
    explicit ClientManager(QHostAddress ip = QHostAddress::LocalHost, ushort port = 4500, QObject *parent = nullptr);
    explicit ClientManager(QTcpSocket *client, QObject *parent = nullptr);

    void connnectToServer();
    void disconnectFromHost();

    void sendMessage(QString message);
    void sendName(QString name);
    void sendStatus(ChatProtocol::Status status);
    void sendIsTyping();
    QString name() const;

    void sendInitSendingFile(QString fileName);
    void sendAcceptFile();
    void sendRejectFile();


signals:
    void connected();
    void disconnected();
//    void dataReceived(QByteArray data);
    void textMessageReceived(QString message,QString receiver);
    void isTyping();
    void nameChanged(QString prevName , QString name);
    void statusChanged(ChatProtocol::Status status);

    void initReceivingFile(QString clientName,QString fileName,qint64 fileSize);
    void rejectReceivingFile();
    void fileSaved(QString path);
private slots:
    void readyRead();
private:
    QTcpSocket *_socket;
    QHostAddress _ip;
    ushort _port;
    ChatProtocol _protocol;
    QString _tmpFileName;
    QString _path;

private: //methods
    void setupClient();
    void sendFile();
    void saveFile();
};

#endif // CLIENTMANAGER_H
