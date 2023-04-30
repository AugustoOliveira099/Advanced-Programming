#include "modifysaida.h"
#include "ui_modifysaida.h"

modifySaida::modifySaida(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifySaida)
{
    ui->setupUi(this);
}

modifySaida::~modifySaida()
{
    delete ui;
}

void modifySaida::on_buttonBox_accepted()
{
    QString idSaida, idOrigem;

    // Pegar valores
    idSaida = ui->saidaNumberlabel->text();
    idOrigem = ui->idOrigemSpinBox->text();

    emit signModifySaida(idSaida, idOrigem);

    QDialog::close();
}

void modifySaida::on_buttonBox_rejected()
{
    QDialog::close();
}

void modifySaida::slotSaidaID(int row)
{
    ui->saidaNumberlabel->setNum(row+1);
}

void modifySaida::slotIntervaloSaida(int min, int max)
{
    ui->idOrigemSpinBox->setRange(min, max);
}
