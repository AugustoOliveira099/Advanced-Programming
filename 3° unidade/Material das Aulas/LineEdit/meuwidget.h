#ifndef MEUWIDGET_H
#define MEUWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MeuWidget; }
QT_END_NAMESPACE

class MeuWidget : public QWidget
{
    Q_OBJECT

public:
    MeuWidget(QWidget *parent = nullptr);
    ~MeuWidget();

    void setName(const QString &name);
    //
    QString name() const;

private:
    Ui::MeuWidget *ui;
};
#endif // MEUWIDGET_H
