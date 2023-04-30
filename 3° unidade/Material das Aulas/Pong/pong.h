#ifndef PONG_H
#define PONG_H
#include <QObject>
#include <thread>

/// Classe que representa o jogo Pong
/// O campo tem suas dimensoes definidas por constantes da classe

class Pong: public QObject
{
  Q_OBJECT

private:
  /// Dimensao da bola (em pixels)
  const unsigned raio_bola;
  /// Dimensoes do campo de jogo (em pixels)
  const unsigned altura_barra;  // altura (y) da barra
  const unsigned x_max;         // x de 0 a x_max (x_max+1 px)
  const unsigned y_max;         // y de -y_max a +y_max (2*y_max+1 px)
  /// Parametros da simulacao
  const double t_nivel; // Tempo para troca de nivel (s)
  const double v_min;   // vel inicial da bola em pixels/s
  const double mult_v;  // Aumento percentual da vel a cada nivel
  /// Tempo de exibicao
  /// De quantos em quantos segundos o jogo deve ser simulado e exibido
  const double delta_t; // (1/delta_t) frames por segundo

  /// Simulando (true) ou parado (false)
  bool em_jogo;
  /// Nivel de jogo
  unsigned nivel;   // 1 a infinito

  /// Tempos de simulacao
  double t;         // Tempo total atual (em s)
  double epsilon_t; // Passo de simulacao (em s)

  /// Posicao da barra
  double pos_barra; // de -1.0 a +1.0

  /// Variveis dinamicas da simulacao da bola
  double x,y;       // posicao em pixels
  double theta;     // angulo de orientacao em radianos (-pi a pi)
  double v;         // vel linear em pixels/s
  double dist;      // Distancia total percorrida (em px)

  /// O identificador da thread de simulacao
  std::thread thr;

  /// Valores iniciais do jogo
  void valores_iniciais();

  /// Simula o sistema delta_t segundos
  void simular();

  /// Esta eh a funcao principal da thread
  /// Ela faz um ciclo sem fim de simular e exibir o jogo
  void main();
  /// A chamada ao metodo "main" atraves de uma funcao C
  friend void main_pong(Pong* P);

private slots:
  /// Iniciar a thread
  void iniciar();

  /// Terminar a thread
  void encerrar();

  /// Fixa uma nova posicao para a barra (de -1 a 1)
  void setPosBarra(double pos);

signals:
  /// Sinaliza nova simulacao: a interface deve redesenhar o jogo
  void signExibirBola();
  /// Sinaliza que o usuario perdeu o jogo (nao rebateu a bola)
  /// A interface deve encerrar o jogo
  void signEncerrarPongPerdeu();

public:
  /// Construtor default
  explicit Pong(QObject *parent = nullptr);

  /// Funcoes de consulta
  inline unsigned getRaioBola() const {return raio_bola;}
  inline unsigned getAlturaBarra() const {return altura_barra;}
  inline unsigned getXMax() const {return x_max;}
  inline unsigned getYmax() const {return y_max;}
  inline unsigned getDimX() const {return x_max+1;}
  inline unsigned getDimY() const {return (2*y_max)+1;}
  inline bool getEmJogo() const {return em_jogo;}
  inline unsigned getNivel() const {return nivel;}
  inline double getTempo() const {return t;}
  inline double getDistancia() const {return dist;}
  inline double getPosBarra() const {return pos_barra;}
  /// Retorna a posicao da barra ("pb_min" a "pb_max", em px)
  void getPosBarra(int& pb_min, int& pb_max) const;
  /// Retorna a posicao x,y da bola (em px)
  void getPosBola(int& pb_x, int& pb_y) const;
};

#endif // PONG_H
