#ifndef INCLUIRLIVRO_H
#define INCLUIRLIVRO_H

#include <QDialog>

namespace Ui {
class IncluirLivro;
}

class IncluirLivro : public QDialog
{
    Q_OBJECT

signals:
    void signIncluirLivro(QString,QString,QString);

public:
    explicit IncluirLivro(QWidget *parent = nullptr);
    ~IncluirLivro();

private slots:
    void on_ButtonBox_accepted();

    void on_ButtonBox_rejected();

private:
    Ui::IncluirLivro *ui;

};

#endif // INCLUIRLIVRO_H
