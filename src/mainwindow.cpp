#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  x_var = false;
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->pushButton_multi, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->pushButton_beginBreket, SIGNAL(clicked()), this,
          SLOT(digitsNumbers()));
  connect(ui->pushButton_endBreket, SIGNAL(clicked()), this,
          SLOT(digitsNumbers()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functionsShow()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functionsShow()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functionsShow()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functionsShow()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functionsShow()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functionsShow()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functionsShow()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functionsShow()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functionsShow()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(functionsShow()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digitsNumbers() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  if (ui->resultShow->text().contains(".") && button->text() == "0") {
    new_label = ui->resultShow->text() + button->text();
  } else {
    new_label = ui->resultShow->text() + button->text();
  }
  ui->resultShow->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked() {
  ui->resultShow->setText(ui->resultShow->text() + ".");
}

void MainWindow::on_pushButton_clear_clicked() { ui->resultShow->clear(); }

void MainWindow::on_pushButton_eq_clicked() {
  QString equal = ui->resultShow->text();
  qarray = equal.toLocal8Bit();
  if (this->x_var == true) {
    question = new Question;
    question->show();
    connect(question, &Question::signalQuestion, this,
            &MainWindow::slotQuestion);
  } else if (qarray == "") {
    ui->resultShow->clear();
  } else {
    calculation();
  }
  this->x_var = false;
}

void MainWindow::calculation() {
  QString string_ = ui->resultShow->text();
  std::string stringInp_ = string_.toLocal8Bit().data();

  s21::Controller control(stringInp_);
  std::pair<std::string, double> res = control.calc();
  char outStr[250] = {0};
  if (res.first.size() == 0) {
    res.second = res.second == -0.0 ? 0.0 : res.second;
    sprintf(outStr, "%.15g", res.second);
    ui->resultShow->setText(outStr);
  } else {
    QString tempStr = QString::fromLocal8Bit(res.first.c_str());
    ui->resultShow->setText(tempStr);
  }
}

void MainWindow::on_pushButton_back_clicked() {
  QString str = ui->resultShow->text();
  str = str.left(str.count() - 1);
  ui->resultShow->setText(str);
}

void MainWindow::functionsShow() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  new_label = ui->resultShow->text() + button->text() + "(";
  ui->resultShow->setText(new_label);
}

void MainWindow::on_pushButton_x_clicked() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  new_label = ui->resultShow->text() + button->text();
  ui->resultShow->setText(new_label);
  x_var = true;
}

void MainWindow::slotQuestion(QString str) {
  QString x_a = str;
  bool ok;
  x_a.toDouble(&ok);
  if (ok == false) {
    ui->resultShow->setText("Error: smg wrong with data for X");
  } else {
    QByteArray byteArray = x_a.toLocal8Bit();
    char *var = byteArray.data();
    char var_2[250] = {0};
    snprintf(var_2 + strlen(var_2), 200, "%s", var);
    qarray.replace("x", var_2);
    QString string_ = qarray;
    QString strInp = string_.toLocal8Bit().data();
    ui->resultShow->setText(strInp);
    calculation();
  }
}

void MainWindow::on_pushButton_gr_clicked() {
  graph window(nullptr, ui->resultShow->text());
  window.setModal(true);
  window.exec();
}

void MainWindow::on_pushButton_credit_clicked() {
  Credit window(nullptr);
  window.setModal(true);
  window.exec();
}

void MainWindow::on_pushButton_deposit_clicked() {
  deposit window(nullptr);
  window.setModal(true);
  window.exec();
}

void MainWindow::on_pushButton_e_clicked() {
  ui->resultShow->setText(ui->resultShow->text() + "2.718281828459045");
}
