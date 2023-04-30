#include "notepad.h"
#include "ui_notepad.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <cmath>
#include "QTextStream"


Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
}

Notepad::~Notepad()
{
    delete ui;
}


void Notepad::on_quitButton_clicked()
{
    QCoreApplication::quit();
}

void Notepad::on_actionOpen_triggered()
{

      QString fileName = QFileDialog::
          getOpenFileName(this,
                          "Open File",
                          QString(),
                          "Text Files (*.txt);;C++ Files (*.cpp *.h)");

      if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
          // error message
          QMessageBox::critical(this, tr("Error"), tr("Could not open file to read"));
          return;
        }
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
      }

}

void Notepad::on_actionSave_triggered()
{
    QString fileName = QFileDialog::
          getSaveFileName(this,
                          "Save File",
                          QString(),
                          "Text Files (*.txt);;C++ Files (*.cpp *.h)");

      if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
          // error message
          QMessageBox::critical(this, tr("Error"), tr("Could not open file to save"));
          return;
        }
        QTextStream stream(&file);
        stream << ui->textEdit->toPlainText();
        stream.flush();
        file.close();
      }
}
