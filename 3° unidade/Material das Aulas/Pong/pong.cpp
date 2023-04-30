#include <iostream>
#include <cmath>
#include <cstdlib> // para srand
#include <chrono>
#include "pong.h"

using namespace std;

/// Retorna um numero aleatorio entre -1.0 e 1.0
static inline double rnd()
{
  return ((2.0*rand())/RAND_MAX)-1.0;
}

/// Retorna o sinal de um numero: +1 ou -1
static inline double sgn(double x)
{
  return (x>=0.0 ? 1.0 : -1.0);
}

/// Construtor default
Pong::Pong(QObject *parent):
  QObject(parent),
  raio_bola(10),     // bola tem raio de 10px
  // Todas as dimensoes sao inicializadas em funcao do raio da bola
  altura_barra(5*raio_bola),
  x_max(45*raio_bola),
  y_max(15*raio_bola), // A altura do campo eh 2*y_max
  t_nivel(20.0),       // muda de nivel a cada 20s
  v_min(100.0),        // vel minima = 100px/s
  mult_v(1.5),         // ao mudar de nivel, vel aumenta 50%
  delta_t(0.03)        // simula e exibe a cada 30ms
{
  srand (time(NULL));
  valores_iniciais();
}

/// Valores iniciais do jogo
void Pong::valores_iniciais()
{
  // Inicia parado (nao estah em jogo)
  em_jogo = false;
  thr = std::thread();

  // Primeiro nivel
  nivel = 1;
  t = 0.0;

  // Comeca com barra no centro
  pos_barra = 0.0;

  // Comeca do lado direito do campo com posicao y e angulo aleatorios
  x = x_max-raio_bola;
  y = 0.8*(y_max-raio_bola)*rnd();        // entre +- 0.8*(dim_y/2)-raio_bola
  theta = (M_PI/3.0)*rnd();               // +60 a -60 graus: 1 ou 4 quadrantes
  theta = atan2(sin(theta), -cos(theta)); // converte 1->2 ou 4->3 quadr
  dist = 0.0;

  // Comeca com vel minima
  v = v_min;

  // Calcula o passo de simulacao
  epsilon_t = raio_bola/(10.0*v);         // percorre raio/10 em 1 passo de simulacao
  if (epsilon_t > delta_t) epsilon_t=delta_t;
}

/// Calcula o intervalo de posicionamento da barra ("pb_min" a "pb_max", em px)
/// a partir da sua posicao percentual ("pos_barra")
void Pong::getPosBarra(int& pb_min, int& pb_max) const
{
  // O centro da barra deve estah posicionado da seguinte forma:
  // pos_barra ==  1.0 -> pb_centro ==  (dim_y-altura_barra)/2
  // pos_barra ==  0.0 -> pb_centro == 0
  // pos_barra == -1.0 -> pb_centro == -(dim_y-altura_barra)/2
  int pb_centro = round((y_max-(altura_barra/2.0))*pos_barra);
  pb_min = pb_centro-altura_barra/2;
  pb_max = pb_centro+altura_barra/2;
}

/// Retorna a posicao x,y da bola (em px)
void Pong::getPosBola(int& pb_x, int& pb_y) const
{
  pb_x = round(x);
  pb_y = round(y);
}

void Pong::setPosBarra(double pos)
{
  if (pos<-1.0) pos = -1.0;
  if (pos>1.0) pos = 1.0;
  pos_barra = pos;
}

/// Simula o sistema por "delta_t" segundos
/// Obs: o periodo da simulacao (delta_t) eh diferente do passo de simulacao (epsilon_t)
/// epsilon_t <= delta_t
void Pong::simular()
{
  // Se o jogo estah parado, a simulacao nao faz nada
  if (!em_jogo) return;

  // Tempo transcorrido nessa chamada da simulacao
  double t_sim = 0.0;

  while (t_sim < delta_t)
  {
    x += v*cos(theta)*epsilon_t;
    y += v*sin(theta)*epsilon_t;
    dist += v*epsilon_t;
    t_sim += epsilon_t;
    t += epsilon_t;

    // Verifica se mudou de nivel
    if (t >= nivel*t_nivel)
    {
      nivel++;
      v *= mult_v;
      epsilon_t = raio_bola/(10.0*v);
      if (epsilon_t > delta_t) epsilon_t=delta_t;
    }

    // Verifica se colidiu com alguma das paredes

    // Parede inferior ou superior
    if ( abs(y) >= y_max-raio_bola )
    {
      y = sgn(y)*(y_max-raio_bola);
      theta = atan2(-sin(theta), cos(theta)); // 2<->3 ou 1<->4 quadrantes
    }

    // Parede direita
    if (x >= x_max-raio_bola)
    {
      x = x_max-raio_bola;
      theta = atan2(sin(theta), -cos(theta)); // 1->2 ou 4->3 quadrantes
    }

    // Lado esquerdo: ou ricocheteia na barra ou se perde (fim do jogo)
    if (x <= raio_bola)
    {
      x = raio_bola;
      // Calcula a regiao onde estah a barra no momento
      int pb_min, pb_max;
      getPosBarra(pb_min, pb_max);
      // Verifica se bateu na barra ou nao
      if (y>=pb_min && y<=pb_max)
      {
        // Ricocheteou
        theta = atan2(sin(theta), -cos(theta)); // 2->1 ou 3->4 quadrantes
      }
      else
      {
        // Se perdeu: fim de jogo
        em_jogo = false;
        emit signEncerrarPongPerdeu();
        // FALTA FAZER!!
        // Nessa hora, ninguem dah join na thread
        // Se der iniciar de novo, CRASH!!
      }
    }

  }
}

/// Este eh o metodo principal da thread
/// Ela simula e atualiza o jogo
void Pong::main()
{
  while (em_jogo)
  {
    this_thread::sleep_for(chrono::milliseconds(unsigned(1000*delta_t)));
    simular();
    emit signExibirBola();
  }
}

/// A chamada ao metodo "main" atraves de uma funcao C
void main_pong(Pong* P)
{
  P->main();
}

/// Inicia/reinicia o jogo
void Pong::iniciar()
{
  valores_iniciais();
  em_jogo = true;
  thr = std::thread(::main_pong, this);
}

/// Terminar a thread
void Pong::encerrar(void)
{
  em_jogo = false;
  if (thr.joinable()) thr.join();
  thr = std::thread();
}
