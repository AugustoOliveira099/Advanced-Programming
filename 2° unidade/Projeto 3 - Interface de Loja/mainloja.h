#ifndef MAINLOJA_H
#define MAINLOJA_H

#include <QMainWindow>
#include <loja.h>
#include <incluircd.h>
#include <incluirdvd.h>
#include <incluirlivro.h>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainLoja; }
QT_END_NAMESPACE

class MainLoja : public QMainWindow
{
    Q_OBJECT

public:
    MainLoja(QWidget *parent = nullptr);
    ~MainLoja();

private slots:
    void on_actionSair_triggered();
    
    void on_tabelaLivro_cellDoubleClicked(int row, int column);
    
    void on_tabelaCD_cellDoubleClicked(int row, int column);
    
    void on_tabelaDVD_cellDoubleClicked(int row, int column);
    
    void on_actionIncluir_CD_triggered();
    
    void on_actionIncluir_Livro_triggered();
    
    void on_actionIncluir_DVD_triggered();
    
    void on_actionSalvar_triggered();
    
    void on_actionLer_triggered();

    void slotIncluirLivro(QString nome, QString preco, QString autor);

    void slotIncluirDVD(QString nome, QString preco, QString duracao);

    void slotIncluirCD(QString nome, QString preco, QString numfaixas);

private:
    Ui::MainLoja *ui;
    
    Loja X;
    IncluirLivro *janelaLivro;
    IncluirCD *janelaCD;
    IncluirDVD *janelaDVD;
    
    QLabel *total_itens;

    void exibeListaLivro();
    void exibeListaCD();
    void exibeListaDVD();
    void exibeListas();
    void exibeStatus();

};
#endif // MAINLOJA_H
