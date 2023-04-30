#include "incluircd.h"
#include "ui_incluircd.h"

IncluirCD::IncluirCD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirCD)
{
    ui->setupUi(this);
}

IncluirCD::~IncluirCD()
{
    delete ui;
}

void IncluirCD::on_buttonBox_accepted()
{
    QString name = ui->nome->text();
    QString price = ui->preco->text();
    QString tracks = ui->faixas->text();

    emit signIncluirCD(name,price,tracks);
    this->hide();
}

void IncluirCD::on_buttonBox_rejected()
{
    this->hide();
}
