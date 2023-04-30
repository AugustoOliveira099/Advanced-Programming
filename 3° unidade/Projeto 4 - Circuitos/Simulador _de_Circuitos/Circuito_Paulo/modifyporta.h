#ifndef MODIFYPORTA_H
#define MODIFYPORTA_H

#include <QDialog>

namespace Ui {
class modifyPorta;
}

class modifyPorta : public QDialog
{
    Q_OBJECT

public:
    explicit modifyPorta(QWidget *parent = nullptr);
    ~modifyPorta();

signals:
    void signModifyPorta(QString idPorta, QString tipoPorta, QString nEntradas, QString id[4]);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_tipoPortaComboBox_currentIndexChanged(const QString &arg1);

    void on_nEntradasSpinBox_valueChanged(int arg1);

    void slotPortaID(int row);

    void slotIntervaloPorta(int min, int max);

    void slotMaximoEntradas(int max);

private:
    Ui::modifyPorta *ui;
    int maxEntradas;
};

#endif // MODIFYPORTA_H
