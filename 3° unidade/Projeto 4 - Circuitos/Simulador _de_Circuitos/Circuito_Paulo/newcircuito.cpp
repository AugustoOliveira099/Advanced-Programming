#include "newcircuito.h"
#include "ui_newcircuito.h"

#include <QDebug>

newCircuito::newCircuito(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newCircuito)
{
    ui->setupUi(this);
    ui->entradasSpinBox->setRange(0, 4);
}

newCircuito::~newCircuito()
{
    delete ui;
}

void newCircuito::on_buttonBox_accepted()
{
    QString nEntradas, nSaidas, nPortas;

    // Pegar valores
    nEntradas = ui->entradasSpinBox->text();
    nSaidas = ui->saidasSpinBox->text();
    nPortas = ui->portasSpinBox->text();

    emit signNewCircuito(nEntradas, nSaidas, nPortas);
    emit signMaximoEntradas(nEntradas.toInt());
    QDialog::close();
}

void newCircuito::on_buttonBox_rejected()
{
    QDialog::close();
}
