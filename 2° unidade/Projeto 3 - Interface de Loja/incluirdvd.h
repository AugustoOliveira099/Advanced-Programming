#ifndef INCLUIRDVD_H
#define INCLUIRDVD_H

#include <QDialog>

namespace Ui {
class IncluirDVD;
}

class IncluirDVD : public QDialog
{
    Q_OBJECT

signals:
    void signIncluirDVD(QString,QString,QString);

public:
    explicit IncluirDVD(QWidget *parent = nullptr);
    ~IncluirDVD();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::IncluirDVD *ui;
};

#endif // INCLUIRDVD_H
