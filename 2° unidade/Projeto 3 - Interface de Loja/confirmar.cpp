#include "confirmar.h"
#include "ui_confirmar.h"

Confirmar::Confirmar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Confirmar)
{
    ui->setupUi(this);
}

Confirmar::~Confirmar()
{
    delete ui;
}

void Confirmar::on_Excluir_accepted()
{
    QString i;
    emit signConfirmar(i);
}
