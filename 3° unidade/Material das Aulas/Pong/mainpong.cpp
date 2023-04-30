#include <iostream>
#include "mainpong.h"
#include "ui_mainpong.h"

#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QMessageBox>

#define LARGURA_BARRA 20

MainPong::MainPong(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainPong),
  imgBarra(),
  imgBola(),
  P(this)
{
  ui->setupUi(this);

  // Conexao dos sinais
  // Reexibir a bola
  connect(&P, SIGNAL(signExibirBola()),
          this, SLOT(exibirBola()));
  // Iniciar a thread de simulacao por acao no menu
  connect(this, SIGNAL(signIniciarPongMenu()),
          &P, SLOT(iniciar()));
  // Encerrar a thread de simulacao por acao no menu
  connect(this, SIGNAL(signEncerrarPongMenu()),
          &P, SLOT(encerrar()));
  // Encerrar a thread de simulacao porque o usuario perdeu
  connect(&P, SIGNAL(signEncerrarPongPerdeu()),
          &P, SLOT(encerrar()));
  // Alterar a posicao da barra
  connect(this, SIGNAL(signPosBarra(double)),
          &P, SLOT(setPosBarra(double)));

  // Redimensiona os widgets de acordo com o tamanho do Pong
  QRect geom, geom_ant;

  // Redimensiona o deslizador vertical
  geom.setX(0);
  geom.setY(0);
  geom.setWidth(LARGURA_BARRA+1);
  geom.setHeight(P.getDimY());
  ui->sliderBarra->setGeometry(geom);
  geom_ant = geom;

  // Redimensiona o label e a imagem da barra
  geom.setX(geom_ant.x()+geom_ant.width());
  geom.setY(0);
  geom.setWidth(LARGURA_BARRA+1);
  geom.setHeight(P.getDimY());
  ui->labelBarra->setGeometry(geom);
  geom_ant = geom;
  imgBarra = QPixmap(LARGURA_BARRA+1, P.getDimY());

  // Redimensiona a imagem do tabuleiro do Pong
  geom.setX(geom_ant.x()+geom_ant.width());
  geom.setY(0);
  geom.setWidth(P.getDimX());
  geom.setHeight(P.getDimY());
  ui->labelBola->setGeometry(geom);
  geom_ant = geom;
  imgBola = QPixmap(P.getDimX(), P.getDimY());

  // Redimensiona o widget central
  geom.setX(0);
  geom.setY(0);
  geom.setWidth((LARGURA_BARRA+1) + (LARGURA_BARRA+1) + P.getDimX());
  geom.setHeight(P.getDimY());
  ui->centralWidget->setGeometry(geom);
  geom_ant = geom;

  // Redimensiona a janela principal
  resize(geom_ant.width(),
         geom_ant.height() + ui->menuBar->height() + ui->statusBar->height());

  // desenha a barra de acordo com sua posicao
  exibirBarra();

  // desenha o tabuleiro de acordo com a posicao do jogo
  exibirBola();
}

MainPong::~MainPong()
{
  delete ui;
}

/// Redesenha a barra (raquete)
void MainPong::exibirBarra()
{
  // Preenche o espaco da barra com uma cor de fundo
  imgBarra.fill(QColor(255,255,255));

  QPen pen;
  QBrush brush(Qt::SolidPattern);
  QPainter painter;

  // Desenha a barra
  pen.setWidth(1);
  pen.setColor(Qt::black);
  brush.setColor(Qt::lightGray);
  painter.begin(&imgBarra);
  painter.setPen(pen);
  painter.setBrush(brush);

  int pos_barra_min, pos_barra_max;
  P.getPosBarra(pos_barra_min, pos_barra_max);
  painter.drawRect(0,P.getYmax()-pos_barra_max,
                   LARGURA_BARRA,P.getAlturaBarra());
  painter.end();

  ui->labelBarra->setPixmap(imgBarra);
}

/// Redesenha o tabuleiro com a bola
void MainPong::exibirBola()
{

  // Preenche o tabuleiro com uma cor de fundo
  imgBola.fill(QColor(220,255,220));

  QPen pen;
  QBrush brush(Qt::SolidPattern);
  QPainter painter;

  // Desenha a bola
  pen.setWidth(1);
  if (P.getEmJogo())
  {
    pen.setColor(Qt::blue);
    brush.setColor(Qt::cyan);
  }
  else
  {
    pen.setColor(Qt::red);
    brush.setColor(Qt::magenta);
  }
  painter.begin(&imgBola);
  painter.setPen(pen);
  painter.setBrush(brush);

  int pos_bola_x, pos_bola_y;
  P.getPosBola(pos_bola_x, pos_bola_y);
  painter.drawEllipse(QPoint(pos_bola_x, P.getYmax()-pos_bola_y),
                      P.getRaioBola(), P.getRaioBola());
  painter.end();

  ui->labelBola->setPixmap(imgBola);

  QString Msg = "NIVEL: "+QString::number(P.getNivel())+
                "   TEMPO TOTAL: "+QString::number(P.getTempo(),'f',1)+"s" +
                "   DISTANCIA PERCORRIDA: "+QString::number(P.getDistancia());
  statusBar()->showMessage(Msg);
}

void MainPong::on_actionIniciar_triggered()
{
  emit signIniciarPongMenu();
  if (!P.getEmJogo())
  {
    QMessageBox::critical(this, "Erro na simulacao", "Erro ao iniciar a thread de simulacao do Pong!");
  }
}

void MainPong::on_actionEncerrar_triggered()
{
  emit signEncerrarPongMenu();
}

void MainPong::on_actionSair_triggered()
{
  emit signEncerrarPongMenu();
  QCoreApplication::quit();
}

void MainPong::on_sliderBarra_valueChanged(int value)
{
  emit signPosBarra(value/100.0);
  exibirBarra();
}
