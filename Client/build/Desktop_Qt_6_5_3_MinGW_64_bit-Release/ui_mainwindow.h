/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionconnect;
    QAction *actionExit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lnClientName;
    QComboBox *cmbStatus;
    QListWidget *lstMassages;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *lnMessage;
    QPushButton *btnSend;
    QPushButton *btnSendFile;
    QComboBox *cmbDestination;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(501, 408);
        actionconnect = new QAction(MainWindow);
        actionconnect->setObjectName("actionconnect");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lnClientName = new QLineEdit(groupBox);
        lnClientName->setObjectName("lnClientName");

        horizontalLayout->addWidget(lnClientName);

        cmbStatus = new QComboBox(groupBox);
        cmbStatus->addItem(QString());
        cmbStatus->addItem(QString());
        cmbStatus->addItem(QString());
        cmbStatus->addItem(QString());
        cmbStatus->setObjectName("cmbStatus");

        horizontalLayout->addWidget(cmbStatus);


        verticalLayout->addLayout(horizontalLayout);

        lstMassages = new QListWidget(groupBox);
        lstMassages->setObjectName("lstMassages");

        verticalLayout->addWidget(lstMassages);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 2);

        lnMessage = new QLineEdit(groupBox);
        lnMessage->setObjectName("lnMessage");

        gridLayout->addWidget(lnMessage, 1, 2, 1, 1);

        btnSend = new QPushButton(groupBox);
        btnSend->setObjectName("btnSend");

        gridLayout->addWidget(btnSend, 1, 3, 1, 1);

        btnSendFile = new QPushButton(groupBox);
        btnSendFile->setObjectName("btnSendFile");
        btnSendFile->setMaximumSize(QSize(35, 16777215));

        gridLayout->addWidget(btnSendFile, 1, 4, 1, 1);

        cmbDestination = new QComboBox(groupBox);
        cmbDestination->addItem(QString());
        cmbDestination->addItem(QString());
        cmbDestination->setObjectName("cmbDestination");

        gridLayout->addWidget(cmbDestination, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);


        verticalLayout_2->addWidget(groupBox);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 501, 24));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionconnect);
        menu->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Client", nullptr));
        actionconnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Message", nullptr));
        lnClientName->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\345\256\242\346\210\267\347\253\257\345\220\215\347\247\260", nullptr));
        cmbStatus->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));
        cmbStatus->setItemText(1, QCoreApplication::translate("MainWindow", "Available", nullptr));
        cmbStatus->setItemText(2, QCoreApplication::translate("MainWindow", "Busy", nullptr));
        cmbStatus->setItemText(3, QCoreApplication::translate("MainWindow", "Away", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "\347\233\256\346\240\207", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Massage", nullptr));
        btnSend->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        btnSendFile->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        cmbDestination->setItemText(0, QCoreApplication::translate("MainWindow", "Server", nullptr));
        cmbDestination->setItemText(1, QCoreApplication::translate("MainWindow", "All", nullptr));

        menu->setTitle(QCoreApplication::translate("MainWindow", "\351\200\211\351\241\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
