/********************************************************************************
** Form generated from reading UI file 'connectserver.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTSERVER_H
#define UI_CONNECTSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_ConnectServer
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *labelServidor;
    QLabel *labelLogin;
    QLineEdit *editServidor;
    QLineEdit *editLogin;

    void setupUi(QDialog *ConnectServer)
    {
        if (ConnectServer->objectName().isEmpty())
            ConnectServer->setObjectName(QString::fromUtf8("ConnectServer"));
        ConnectServer->resize(235, 125);
        buttonBox = new QDialogButtonBox(ConnectServer);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(20, 80, 200, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);
        labelServidor = new QLabel(ConnectServer);
        labelServidor->setObjectName(QString::fromUtf8("labelServidor"));
        labelServidor->setGeometry(QRect(10, 10, 60, 16));
        labelLogin = new QLabel(ConnectServer);
        labelLogin->setObjectName(QString::fromUtf8("labelLogin"));
        labelLogin->setGeometry(QRect(10, 40, 60, 16));
        editServidor = new QLineEdit(ConnectServer);
        editServidor->setObjectName(QString::fromUtf8("editServidor"));
        editServidor->setGeometry(QRect(80, 10, 140, 20));
        editLogin = new QLineEdit(ConnectServer);
        editLogin->setObjectName(QString::fromUtf8("editLogin"));
        editLogin->setGeometry(QRect(80, 40, 140, 20));

        retranslateUi(ConnectServer);
        QObject::connect(buttonBox, SIGNAL(accepted()), ConnectServer, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ConnectServer, SLOT(reject()));

        QMetaObject::connectSlotsByName(ConnectServer);
    } // setupUi

    void retranslateUi(QDialog *ConnectServer)
    {
        ConnectServer->setWindowTitle(QCoreApplication::translate("ConnectServer", "Conex\303\243o ao servidor", nullptr));
        labelServidor->setText(QCoreApplication::translate("ConnectServer", "SERVIDOR:", nullptr));
        labelLogin->setText(QCoreApplication::translate("ConnectServer", "LOGIN:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConnectServer: public Ui_ConnectServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTSERVER_H
