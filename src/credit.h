#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>
#include <QWidget>
#include <vector>

#include "QtGui/qstandarditemmodel.h"
#include "controller.h"
#include "ui_credit.h"

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void on_pushButton_calculate_clicked();

  void on_pushButton_clear_clicked();

 private:
  Ui::Credit *ui;
};

#endif  // CREDIT_H
