#include "incluirlivro.h"
#include "ui_incluirlivro.h"

IncluirLivro::IncluirLivro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirLivro)
{
    ui->setupUi(this);
}

IncluirLivro::~IncluirLivro()
{
    delete ui;
}


void IncluirLivro::on_ButtonBox_accepted()
{
    QString name = ui->lineEdit->text();
    QString price = ui->lineEdit_2->text();
    QString author = ui->lineEdit_3->text();

    emit signIncluirLivro(name,price,author);
    this->hide();
}

void IncluirLivro::on_ButtonBox_rejected()
{
    this->hide();
}
