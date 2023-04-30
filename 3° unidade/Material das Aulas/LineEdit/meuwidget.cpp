#include "meuwidget.h"
#include "ui_meuwidget.h"

MeuWidget::MeuWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MeuWidget)
{
    ui->setupUi(this);
}

MeuWidget::~MeuWidget()
{
    delete ui;
}

void MeuWidget::setName(const QString &name)
{
    ui->lineEdit->setText(name);
}

//QString MeuWidget::name() const
//{
//    return ui->lineEdit->text();
//}

