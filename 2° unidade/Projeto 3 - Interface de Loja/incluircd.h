#ifndef INCLUIRCD_H
#define INCLUIRCD_H

#include <QDialog>

namespace Ui {
class IncluirCD;
}

class IncluirCD : public QDialog
{
    Q_OBJECT

signals:
    void signIncluirCD(QString,QString,QString);

public:
    explicit IncluirCD(QWidget *parent = nullptr);
    ~IncluirCD();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::IncluirCD *ui;
};

#endif // INCLUIRCD_H
