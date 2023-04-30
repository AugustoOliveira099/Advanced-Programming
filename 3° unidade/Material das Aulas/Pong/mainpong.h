#ifndef MAINPONG_H
#define MAINPONG_H

#include <QMainWindow>
#include "pong.h"

namespace Ui {
class MainPong;
}

class MainPong : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainPong(QWidget *parent = 0);
  ~MainPong();

signals:
  void signIniciarPongMenu();
  void signEncerrarPongMenu();
  void signPosBarra(double);

private slots:
  /// Redesenha a barra
  void exibirBarra();

  /// Redesenha a bola
  void exibirBola();

  void on_actionSair_triggered();
  void on_actionIniciar_triggered();
  void on_actionEncerrar_triggered();
  void on_sliderBarra_valueChanged(int value);

private:
  Ui::MainPong *ui;

  // A imagem da barra onde fica a "raquete"
  QPixmap imgBarra;
  // A imagem do campo
  QPixmap imgBola;

  // A variavel que contem o estado do jogo
  Pong P;
};

#endif // MAINPONG_H
