#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox->setEnabled(false);
    setupIPAndPort();
    setupClient();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupClient()
{
    _client = new ClientManager(_serverIp,_serverPort);
    connect(_client,&ClientManager::connected,[this](){
        ui->groupBox->setEnabled(true);
    });
    connect(_client,&ClientManager::disconnected,[this](){
        ui->groupBox->setEnabled(false);
    });

    connect(_client,&ClientManager::textMessageReceived,this,&MainWindow::dataReceived);
    connect(_client,&ClientManager::isTyping,this,&MainWindow::onTyping);
    connect(_client,&ClientManager::initReceivingFile,this,&MainWindow::onInitReceivingFile);
    connect(_client,&ClientManager::rejectReceivingFile,this,&MainWindow::onRejectReceivingFile);

    connect(ui->lnMessage,&QLineEdit::textChanged,_client,&ClientManager::sendIsTyping);
    connect(_client, &ClientManager::connectionACK, this, &MainWindow::onConnectionACK);
    connect(_client, &ClientManager::newClientConnectedToServer, this, &MainWindow::onNewClientConnectedToServer);
    connect(_client, &ClientManager::clientDisconnected, this, &MainWindow::onClientDisconnected);
    connect(_client, &ClientManager::clientNameChanged, this, &MainWindow::onClientNameChanged);
}

void MainWindow::setupIPAndPort()
{
    _serverIp.setAddress(ui->lnIP->text());
    _serverPort = ui->lnPort->text().toUShort();
}

void MainWindow::on_actionconnect_triggered()
{

    _client->connnectToServer();
}

void MainWindow::dataReceived(QString message)
{
    //ui->lstMassages->addItem(data);
    auto chatWidget = new ChatItemWidget(this);
    chatWidget->setMessage(message);
    auto listItemWidget = new QListWidgetItem();
    listItemWidget->setSizeHint(QSize(0,65));
    ui->lstMassages->addItem(listItemWidget);
    listItemWidget->setBackground(QColor(167,255,237));
    ui->lstMassages->setItemWidget(listItemWidget,chatWidget);
}


void MainWindow::on_btnSend_clicked()
{
    auto message = ui->lnMessage->text().trimmed();
    _client->sendMessage(message,ui->cmbDestination->currentText());
    ui->lnMessage->setText("");
 //   ui->lstMassages->addItem(message);

    auto chatWidget = new ChatItemWidget(this);
    chatWidget->setMessage(message,true);
    auto listItemWidget = new QListWidgetItem();
    listItemWidget->setSizeHint(QSize(0,65));
    ui->lstMassages->addItem(listItemWidget);
    //listItemWidget->setBackground(QColor(167,255,237));
    ui->lstMassages->setItemWidget(listItemWidget,chatWidget);
}


void MainWindow::on_lnClientName_editingFinished()
{
    auto name = ui->lnClientName->text().trimmed();
    _client->sendName(name);
}


void MainWindow::on_cmbStatus_currentIndexChanged(int index)
{
    auto status = (ChatProtocol::Status)index;
    _client->sendStatus(status);
}

void MainWindow::onTyping()
{
    statusBar()->showMessage("server is typing ...",750);
}


void MainWindow::on_btnSendFile_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this,"选择一个文件","/home");
    _client->sendInitSendingFile(fileName);
}

void MainWindow::onRejectReceivingFile()
{
    QMessageBox::critical(this,"发送文件","被拒绝...");
}

void MainWindow::onInitReceivingFile(QString clientName, QString fileName, qint64 fileSize)
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

void MainWindow::onConnectionACK(QString myName, QStringList clientsName)
{
    ui->cmbDestination->clear();
    clientsName.prepend("All");
    clientsName.prepend("Server");
    foreach (auto client, clientsName) {
        ui->cmbDestination->addItem(client);
    }
    setWindowTitle(myName);
}

void MainWindow::onNewClientConnectedToServer(QString clientName)
{
    ui->cmbDestination->addItem(clientName);
}

void MainWindow::onClientNameChanged(QString prevName, QString clientName)
{
    for (int i = 0; i < ui->cmbDestination->count(); ++i) {
        if (ui->cmbDestination->itemText(i) == prevName) {
            ui->cmbDestination->setItemText(i, clientName);
            return;
        }
    }
}

void MainWindow::onClientDisconnected(QString clientName)
{
    for (int i = 0; i < ui->cmbDestination->count(); ++i) {
        if (ui->cmbDestination->itemText(i) == clientName) {
            ui->cmbDestination->removeItem(i);
            return;
        }
    }
}

