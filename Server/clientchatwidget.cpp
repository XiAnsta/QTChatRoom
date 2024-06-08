#include "clientchatwidget.h"
#include "ui_clientchatwidget.h"

ClientChatWidget::ClientChatWidget(QTcpSocket *client,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientChatWidget)
{
    ui->setupUi(this);
    _client = new ClientManager(client,this);
 //   connect(_client,&QTcpSocket::readyRead,this,&ClientChatWidget::dataReceived);
    connect(_client,&ClientManager::disconnected,this,&ClientChatWidget::clientDisconnected);
    connect(_client,&ClientManager::textMessageReceived,this,&ClientChatWidget::textMessageReceived);
    connect(_client,&ClientManager::isTyping,this,&ClientChatWidget::onTyping);
    connect(_client,&ClientManager::nameChanged,this,&ClientChatWidget::onclientNameChanged);
    connect(_client,&ClientManager::statusChanged,this,&ClientChatWidget::statusChanged);
    connect(_client, &ClientManager::initReceivingFile, this, &ClientChatWidget::onInitReceivingFile);
    connect(_client, &ClientManager::fileSaved, this, &ClientChatWidget::onFileSaved);
    connect(ui->lnMessage,&QLineEdit::textChanged,_client,&ClientManager::sendIsTyping);

    dir.mkdir(_client->name());
    dir.setPath("./" + _client->name());

}

void ClientChatWidget::disconnect()
{
    _client->disconnectFromHost();
}

ClientChatWidget::~ClientChatWidget()
{
    delete ui;
}


/**
void ClientChatWidget::dataReceived()
{
    auto data = _client->readAll();
    ui->lstMessage->addItem(data);
}
**/



void ClientChatWidget::on_btnSend_clicked()
{
    auto message = ui->lnMessage->text().trimmed();

    _client->sendMessage(message);

    ui->lnMessage->setText("");


    ui->lstMessage->addItem(message);
}

void ClientChatWidget::clientDisconnected()
{
    ui->wdgSend->setEnabled(false);
}

void ClientChatWidget::textMessageReceived(QString message , QString receiver)
{
    if(receiver == "Server"|| receiver == "All"){
                ui->lstMessage->addItem(message);
    }

    if(receiver != "Server"){
        emit textForOtherClients(message,receiver,_client->name());
    }

}

void ClientChatWidget::onInitReceivingFile(QString clientName, QString fileName, qint64 fileSize)
{
    auto message = QString("客户端(%1)想要发送一个文件。您要接受它吗\n文件名:%2\n大小:%3bytes")
                       .arg(clientName,fileName)
                       .arg(fileSize);
    auto result = QMessageBox::question(this,"接受文件",message);
    if(result == QMessageBox::Yes){
        _client->sendAcceptFile();
    }else{
        _client->sendRejectFile();
    }
}

void ClientChatWidget::onFileSaved(QString path)
{
    auto message = QString("文件被储存在:\n%1").arg(path);
    QMessageBox::information(this, "文件已下载", message);
}

void ClientChatWidget::onTyping()
{
    emit isTyping(QString("%1 正在输入").arg(_client->name()));
}


void ClientChatWidget::on_lblOpenFolder_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(_client->name()));
}

void ClientChatWidget::onclientNameChanged(QString preName , QString name)
{
    QFile::rename(dir.canonicalPath(),name);
    emit clientNameChanged(preName,name);
}

