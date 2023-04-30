#ifndef MAINCIRCUITO_H
#define MAINCIRCUITO_H

#include <QMainWindow>
#include <QLabel>
#include "circuito.h"
#include "modifyporta.h"
#include "modifysaida.h"
#include "newcircuito.h"
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class maincircuito; }
QT_END_NAMESPACE

class maincircuito : public QMainWindow
{
    Q_OBJECT

public:
    maincircuito(QWidget *parent = nullptr);
    ~maincircuito();

    void ExibirTabelas();
    void ExibirPorta(unsigned idPorta);
    void ExibirSaida(unsigned idPorta);

private slots:
    void on_actionNovo_triggered();

    void on_actionLer_triggered();

    void on_actionSalvar_triggered();

    void on_actionSair_triggered();

    void on_actionGerar_tabela_triggered();

    void on_portasConexoesWidget_cellDoubleClicked(int row, int);

    void on_saidasWidget_cellDoubleClicked(int row, int);

    void slotNewCircuito(QString nEntradas, QString nSaidas, QString nPortas);

    void slotModifyPorta(QString idPorta, QString tipoPorta, QString nEntradas, QString id[4]);

    void slotModifySaida(QString idSaida, QString idOrigem);

signals:
    void signPortaID(int row);

    void signSaidaID(int row);

    void signIntervaloPorta(int min, int max);

    void signIntervaloSaida(int min, int max);

private:
    Ui::maincircuito *ui;

    // Classe circuito
    Circuit C;
    // Janelas
    modifyPorta *modPorta;
    modifySaida *modSaida;
    newCircuito *newCirc;
    // StatusBar
    QLabel *totalEntradas, *totalSaidas, *totalPortas;
};
#endif // MAINCIRCUITO_H
