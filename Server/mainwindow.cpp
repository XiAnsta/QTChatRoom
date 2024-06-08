#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newClientConnected(QTcpSocket *client)
{
    auto id = client->property("id").toInt();
    ui->lstClients->addItem(QString("客户机加入 %1").arg(id));
    auto chatWidget= new ClientChatWidget(client);
    ui->tbChats->addTab(chatWidget,QString("客户机(%1)").arg(id));

    connect(chatWidget,&ClientChatWidget::clientNameChanged,this,&MainWindow::setClientName);
    connect(chatWidget,&ClientChatWidget::statusChanged,this,&MainWindow::setClientStatus);
    connect(chatWidget,&ClientChatWidget::isTyping,[this](QString name){
        this->statusBar()->showMessage(name,750);
    });

    connect(chatWidget,&ClientChatWidget::textForOtherClients,_server,&ServerManager::onTextForOtherClients);

}

void MainWindow::clientDisconnected(QTcpSocket *client)
{
    auto id = client->property("id").toInt();
    ui->lstClients->addItem(QString("客户机离开 %1").arg(id));

}

void MainWindow::setClientName(QString prevName,QString name)
{
    auto widget = qobject_cast<QWidget *>(sender());
    auto index =ui->tbChats->indexOf(widget);
    ui->tbChats->setTabText(index,name);

    _server->notifyOtherClients(prevName,name);
}

void MainWindow::setClientStatus(ChatProtocol::Status status)
{
    auto widget = qobject_cast<QWidget *>(sender());
    auto index =ui->tbChats->indexOf(widget);
    QString iconName = ":/icons/";
    switch (status) {
    case ChatProtocol::Available:
        iconName.append("available.png");
        break;
    case ChatProtocol::Away:
        iconName.append("away.png");
        break;
    case ChatProtocol::Busy:
        iconName.append("busy.png");
        break;
    default:
        iconName = "";
        break;
    }

    QIcon icon = (QIcon)QString(iconName);
    ui->tbChats->setTabIcon(index, icon);
}

void MainWindow::setupServer()
{
    _server = new ServerManager();

    connect(_server,&ServerManager::newClientConnected,this ,&MainWindow::newClientConnected);
    connect(_server,&ServerManager::clientDisconnected,this ,&MainWindow::clientDisconnected);
}


void MainWindow::on_tbChats_tabCloseRequested(int index)
{
    auto chatWidget =qobject_cast<ClientChatWidget *>( ui->tbChats->widget(index));

    chatWidget->disconnect();

    ui->tbChats->removeTab(index);
}


void MainWindow::on_btnDisconnectAll_clicked()
{
    auto num = ui->tbChats->count();
    while(num --){
        on_tbChats_tabCloseRequested(num);
    }
}

