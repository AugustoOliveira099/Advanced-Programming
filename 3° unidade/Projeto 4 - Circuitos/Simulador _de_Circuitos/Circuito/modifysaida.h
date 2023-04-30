#ifndef MODIFYSAIDA_H
#define MODIFYSAIDA_H

#include <QDialog>

namespace Ui {
class modifySaida;
}

class modifySaida : public QDialog
{
    Q_OBJECT

public:
    explicit modifySaida(QWidget *parent = nullptr);
    ~modifySaida();

signals:
    void signModifySaida(QString idSaida, QString idOrigem);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void slotSaidaID(int row);

    void slotIntervaloSaida(int min, int max);

private:
    Ui::modifySaida *ui;
};

#endif // MODIFYSAIDA_H
