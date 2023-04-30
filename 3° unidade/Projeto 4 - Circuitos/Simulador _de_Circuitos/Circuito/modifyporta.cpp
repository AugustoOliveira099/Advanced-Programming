#include "modifyporta.h"
#include "ui_modifyporta.h"
#include <QDebug>

modifyPorta::modifyPorta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifyPorta), maxEntradas(0)
{
    ui->setupUi(this);

    // ===== SETANDO O NOME DAS PORTAS =====
    QStringList portas = (QStringList()<<"NT"<<"AN"<<"NA"<<"OR"<<"NO"<<"XO"<<"NX");
    ui->tipoPortaComboBox->addItems(portas);
}

void modifyPorta::on_tipoPortaComboBox_currentIndexChanged(const QString &arg1)
{
    // ===== SETANDO O CASO DAS RANGES =====
    if(arg1 == "NT") ui->nEntradasSpinBox->setRange(1, 1);
    else ui->nEntradasSpinBox->setRange(2,maxEntradas);
}

void modifyPorta::on_nEntradasSpinBox_valueChanged(int arg1)
{
    switch(arg1){
    case 1:
        ui->id1SpinBox->setEnabled(1);
        ui->id2SpinBox->setEnabled(0);
        ui->id3SpinBox->setEnabled(0);
        ui->id4SpinBox->setEnabled(0);
        break;
    case 2:
        ui->id1SpinBox->setEnabled(1);
        ui->id2SpinBox->setEnabled(1);
        ui->id3SpinBox->setEnabled(0);
        ui->id4SpinBox->setEnabled(0);
        break;
    case 3:
        ui->id1SpinBox->setEnabled(1);
        ui->id2SpinBox->setEnabled(1);
        ui->id3SpinBox->setEnabled(1);
        ui->id4SpinBox->setEnabled(0);
        break;
    case 4:
        ui->id1SpinBox->setEnabled(1);
        ui->id2SpinBox->setEnabled(1);
        ui->id3SpinBox->setEnabled(1);
        ui->id4SpinBox->setEnabled(1);
        break;
    default:
        ui->id1SpinBox->setEnabled(0);
        ui->id2SpinBox->setEnabled(0);
        ui->id3SpinBox->setEnabled(0);
        ui->id4SpinBox->setEnabled(0);
        break;
    }
}

void modifyPorta::slotPortaID(int row)
{
    ui->portaNumberLabel->setNum(row+1);
}

void modifyPorta::slotIntervaloPorta(int min, int max)
{
    ui->id1SpinBox->setRange(min, max);
    ui->id2SpinBox->setRange(min, max);
    ui->id3SpinBox->setRange(min, max);
    ui->id4SpinBox->setRange(min, max);
}

void modifyPorta::slotMaximoEntradas(int max)
{
    maxEntradas = max;
}

modifyPorta::~modifyPorta()
{
    delete ui;
}

void modifyPorta::on_buttonBox_accepted()
{
    QString idPorta, tipoPorta, nEntradas, id[4];

    // Pegar valores
    idPorta = ui->portaNumberLabel->text();
    tipoPorta = ui->tipoPortaComboBox->currentText();
    nEntradas = ui->nEntradasSpinBox->text();
    id[0] = ui->id1SpinBox->text();
    id[1] = ui->id2SpinBox->text();
    id[2] = ui->id3SpinBox->text();
    id[3] = ui->id4SpinBox->text();

    for(int i=0; i<4; i++) qDebug() << "Teste SIGN: " << id[i];

    // Emitir sinal
    emit signModifyPorta(idPorta, tipoPorta, nEntradas, id);

    ui->id1SpinBox->setValue(0);
    ui->id2SpinBox->setValue(0);
    ui->id3SpinBox->setValue(0);
    ui->id4SpinBox->setValue(0);

    QDialog::close();
}

void modifyPorta::on_buttonBox_rejected()
{
    QDialog::close();
}
