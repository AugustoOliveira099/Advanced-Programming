#ifndef CONFIRMAR_H
#define CONFIRMAR_H

#include <QDialog>
#include <loja.h>
#include <mainloja.h>

namespace Ui {
class Confirmar;
}

class Confirmar : public QDialog
{
    Q_OBJECT

signals:
    void signConfirmar(QString);

public:
    explicit Confirmar(QWidget *parent = nullptr);
    ~Confirmar();

private slots:
    void on_Excluir_accepted();

private:
    Ui::Confirmar *ui;
};

#endif // CONFIRMAR_H
