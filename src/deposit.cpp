#include "deposit.h"

#include "ui_deposit.h"

deposit::deposit(QWidget *parent) : QDialog(parent), ui(new Ui::deposit) {
  ui->setupUi(this);
}

deposit::~deposit() { delete ui; }

void deposit::on_pushButton_calculate_clicked() {
  s21::Controller control;
  double sum = ui->doubleSpinBox_sum->value();
  int period = ui->spinBox_period->value();
  double procent = ui->doubleSpinBox_procent->value();
  double nalog = ui->doubleSpinBox_taxProcent->value();

  std::map<double, int> arrPush;
  std::map<double, int> arrPop;

  int type = 0;
  if (ui->radioButton_once->isChecked()) type = 1;
  if (ui->radioButton_eachMonth->isChecked()) type = 2;

  int capital = 0;
  if (ui->checkBox_capitalization->isChecked()) capital = 1;

  if (ui->checkBox_addition->isChecked()) {
    if (period > 2) {
      for (int i = 0; i < period - 2; i++) {
        QTableWidgetItem *item_p = ui->tableWidget_add->item(i, 0);
        QTableWidgetItem *item_s = ui->tableWidget_min->item(i, 0);
        if (item_p != 0) {
          arrPush.insert({item_p->text().toDouble(), i});
        }
        if (item_s != 0) {
          arrPop.insert({item_s->text().toDouble(), i});
        }
      }
    }
  }
  std::vector<double> result = control.deposit(sum, procent, period, nalog,
                                               arrPush, arrPop, type, capital);
  ui->label_taxesToPay->setText(QString::number(result[0], 'f', 2));
  ui->label_sumOfProcentEnd->setText(QString::number(result[1], 'f', 2));
  ui->label_sumRemain->setText(QString::number(result[2], 'f', 2));
}

void deposit::on_pushButton_clear_clicked() {
  ui->doubleSpinBox_sum->setValue(0);
  ui->spinBox_period->setValue(0);
  ui->doubleSpinBox_procent->setValue(0);
  ui->doubleSpinBox_taxProcent->setValue(0);

  ui->checkBox_capitalization->setChecked(0);
  ui->checkBox_addition->setChecked(0);

  ui->label_taxesToPay->setText("0");
  ui->label_sumOfProcentEnd->setText("0");
  ui->label_sumRemain->setText("0");

  ui->tableWidget_add->setColumnCount(0);
  ui->tableWidget_add->setRowCount(0);
  ui->tableWidget_min->setColumnCount(0);
  ui->tableWidget_min->setRowCount(0);
}

void deposit::on_pushButton_addDeposit_clicked() {
  int period = ui->spinBox_period->value();
  if (period > 2) {
    ui->tableWidget_add->setColumnCount(1);
    ui->tableWidget_add->setRowCount(period - 2);
    ui->tableWidget_add->setHorizontalHeaderLabels(QStringList()
                                                   << "Пополнить, руб");
    ui->tableWidget_add->horizontalHeader()->resizeSection(0, 225);

    ui->tableWidget_min->setColumnCount(1);
    ui->tableWidget_min->setRowCount(period - 2);
    ui->tableWidget_min->setHorizontalHeaderLabels(QStringList()
                                                   << "Снять, руб");
    ui->tableWidget_min->horizontalHeader()->resizeSection(0, 225);

    ui->checkBox_addition->setChecked(1);
  }
}
