#include "incluirdvd.h"
#include "ui_incluirdvd.h"

IncluirDVD::IncluirDVD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirDVD)
{
    ui->setupUi(this);
}

IncluirDVD::~IncluirDVD()
{
    delete ui;
}

void IncluirDVD::on_buttonBox_accepted()
{
    QString name = ui->nome->text();
    QString price = ui->preco->text();
    QString duration = ui->duracao->text();

    emit signIncluirDVD(name,price,duration);
    this->hide();
}

void IncluirDVD::on_buttonBox_rejected()
{
    this->hide();
}
