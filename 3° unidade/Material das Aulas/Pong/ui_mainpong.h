/********************************************************************************
** Form generated from reading UI file 'mainpong.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINPONG_H
#define UI_MAINPONG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainPong
{
public:
    QAction *actionIniciar;
    QAction *actionEncerrar;
    QAction *actionSair;
    QWidget *centralWidget;
    QLabel *labelBola;
    QLabel *labelBarra;
    QSlider *sliderBarra;
    QMenuBar *menuBar;
    QMenu *menuPong;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainPong)
    {
        if (MainPong->objectName().isEmpty())
            MainPong->setObjectName(QString::fromUtf8("MainPong"));
        MainPong->resize(243, 241);
        actionIniciar = new QAction(MainPong);
        actionIniciar->setObjectName(QString::fromUtf8("actionIniciar"));
        actionEncerrar = new QAction(MainPong);
        actionEncerrar->setObjectName(QString::fromUtf8("actionEncerrar"));
        actionSair = new QAction(MainPong);
        actionSair->setObjectName(QString::fromUtf8("actionSair"));
        centralWidget = new QWidget(MainPong);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        labelBola = new QLabel(centralWidget);
        labelBola->setObjectName(QString::fromUtf8("labelBola"));
        labelBola->setGeometry(QRect(43, 0, 200, 200));
        labelBarra = new QLabel(centralWidget);
        labelBarra->setObjectName(QString::fromUtf8("labelBarra"));
        labelBarra->setGeometry(QRect(22, 0, 21, 200));
        sliderBarra = new QSlider(centralWidget);
        sliderBarra->setObjectName(QString::fromUtf8("sliderBarra"));
        sliderBarra->setGeometry(QRect(0, 0, 22, 200));
        sliderBarra->setMinimum(-100);
        sliderBarra->setMaximum(100);
        sliderBarra->setSingleStep(10);
        sliderBarra->setValue(0);
        sliderBarra->setOrientation(Qt::Vertical);
        MainPong->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainPong);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 243, 21));
        menuPong = new QMenu(menuBar);
        menuPong->setObjectName(QString::fromUtf8("menuPong"));
        MainPong->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainPong);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainPong->setStatusBar(statusBar);

        menuBar->addAction(menuPong->menuAction());
        menuPong->addAction(actionIniciar);
        menuPong->addAction(actionEncerrar);
        menuPong->addSeparator();
        menuPong->addAction(actionSair);

        retranslateUi(MainPong);

        QMetaObject::connectSlotsByName(MainPong);
    } // setupUi

    void retranslateUi(QMainWindow *MainPong)
    {
        MainPong->setWindowTitle(QCoreApplication::translate("MainPong", "Pong - Exemplo de threads em Qt", nullptr));
        actionIniciar->setText(QCoreApplication::translate("MainPong", "Iniciar", nullptr));
        actionEncerrar->setText(QCoreApplication::translate("MainPong", "Encerrar", nullptr));
        actionSair->setText(QCoreApplication::translate("MainPong", "Sair", nullptr));
        labelBola->setText(QString());
        labelBarra->setText(QString());
        menuPong->setTitle(QCoreApplication::translate("MainPong", "Pong", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainPong: public Ui_MainPong {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINPONG_H
