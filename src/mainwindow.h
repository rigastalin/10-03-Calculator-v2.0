#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "controller.h"
#include "credit.h"
#include "deposit.h"
#include "graph.h"
#include "qcustomplot.h"
#include "question.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QByteArray qarray;
  QString intXStr;
  bool x_var;
  double x_question;

 private:
  Ui::MainWindow *ui;
  Question *question;

 private slots:
  void digitsNumbers();
  void on_pushButton_dot_clicked();
  void on_pushButton_clear_clicked();
  void on_pushButton_eq_clicked();
  void functionsShow();
  void calculation();
  void on_pushButton_x_clicked();
  void on_pushButton_back_clicked();
  void on_pushButton_gr_clicked();
  void on_pushButton_credit_clicked();
  void on_pushButton_deposit_clicked();

  void on_pushButton_e_clicked();

 public slots:
  void slotQuestion(QString a);
};
#endif  // MAINWINDOW_H
