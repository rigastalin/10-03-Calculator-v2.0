#include "credit.h"

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
}

Credit::~Credit() { delete ui; }

void Credit::on_pushButton_calculate_clicked() {
  s21::Model::creditOut monthPay;
  double sum = ui->doubleSpinBo_sumCredit->value();
  double procent = ui->doubleSpinBox_procent->value();
  int period = ui->spinBox_period->value();
  if (sum != 0.0 && procent != 0.0 && period != 0.0) {
    int method = 0;
    if (ui->radioButton_type1->isChecked()) {
      method = 1;
      s21::Controller control;
      monthPay = control.credit_ann(sum, procent, period);
    }
    if (ui->radioButton_type2->isChecked()) {
      method = 2;
      s21::Controller control;
      monthPay = control.creditDiff_calc(sum, procent, period);
    }
    QStandardItemModel *model =
        new QStandardItemModel(monthPay.monthPay.size(), 4, this);
    ui->tableView->setModel(model);
    for (size_t row = 0; row < monthPay.monthPay.size(); row++) {
      model->setData(model->index(row, 0, QModelIndex()),
                     monthPay.monthPay[row].first);
      model->setData(model->index(row, 1, QModelIndex()),
                     monthPay.monthPay[row].second);
      model->setData(model->index(row, 2, QModelIndex()),
                     monthPay.bodyCredit[row]);
      model->setData(model->index(row, 3, QModelIndex()),
                     monthPay.currentDept[row]);
    }
    model->setHeaderData(0, Qt::Horizontal, "Платеж, руб");
    model->setHeaderData(1, Qt::Horizontal, "Проценты, руб");
    model->setHeaderData(2, Qt::Horizontal, "Тело кредита, руб");
    model->setHeaderData(3, Qt::Horizontal, "Остаток, руб");
    ui->tableView->horizontalHeader()->resizeSection(0, 125);
    ui->tableView->horizontalHeader()->resizeSection(1, 125);
    ui->tableView->horizontalHeader()->resizeSection(2, 125);
    ui->tableView->horizontalHeader()->resizeSection(3, 120);
    ui->label_sumToPay_B->setText(QString::number(monthPay.fullLoan, 'f', 2));
    ui->label_procToPay_B->setText(QString::number(monthPay.overPay, 'f', 2));

    if (method == 1) {
      ui->label_monthToPay_B->setText(
          QString::number(monthPay.monthPay[1].first, 'f', 2));
    } else {
      ui->label_monthToPay_B->setText("изменчивый");
    }
  } else {
    ui->doubleSpinBo_sumCredit->setValue(sum);
    ui->spinBox_period->setValue(period);
    ui->doubleSpinBox_procent->setValue(procent);
  }
}

void Credit::on_pushButton_clear_clicked() {
  ui->doubleSpinBo_sumCredit->setValue(0);
  ui->doubleSpinBox_procent->setValue(0);
  ui->spinBox_period->setValue(0);

  ui->label_sumToPay_B->setText("0");
  ui->label_procToPay_B->setText("0");
  ui->label_monthToPay_B->setText("0");

  static double sum = ui->doubleSpinBo_sumCredit->value();
  static double procent = ui->doubleSpinBox_procent->value();
  static int period = ui->spinBox_period->value();
  s21::Model::creditOut zeroMode;
  s21::Controller control;
  zeroMode = control.credit_ann(sum, procent, period);

  ui->label_sumToPay_B->setText(QString::number(zeroMode.fullLoan, 'f', 2));
  ui->label_procToPay_B->setText(QString::number(zeroMode.overPay, 'f', 2));

  ui->tableView->setColumnWidth(0, 0);
  ui->tableView->setColumnWidth(1, 0);
  ui->tableView->setColumnWidth(2, 0);
  ui->tableView->setColumnWidth(3, 0);

  //    ui->radioButton_type1->setChecked(false);
  //    ui->radioButton_type2->setChecked(false);
}
