#include "graph.h"

#include "controller.h"
#include "ui_graph.h"

graph::graph(QWidget *parent, QString str_out)
    : QDialog(parent), ui(new Ui::graph) {
  ui->setupUi(this);
  strOut = str_out;
}

graph::~graph() { delete ui; }

void graph::on_GraphBuilt_clicked() {
  QPen pen(QColor(182, 56, 56), 1, Qt::DashDotLine, Qt::RoundCap,
           Qt::RoundJoin);
  x_step = 0.0002;
  x_start = ui->x_start->value();
  x_end = ui->x_end->value();
  y_start = ui->y_start->value();
  y_end = ui->y_end->value();

  int err = 0;
  if (x_start >= x_end || y_start >= y_end) {
    err = 1;
  }

  ui->widget->xAxis->setRange(x_start, x_end);
  ui->widget->yAxis->setRange(y_start, y_end);
  for (X = x_start; X <= x_end && err == 0; X += x_step) {
    x.push_back(X);
    char var_2[250] = {0};
    snprintf(var_2, 200, "%lf", X);
    QString buffer = strOut;
    QString strExp = buffer.replace(QString("x"), QString::number(X, 'f', 3));
    std::string strBuf = strExp.toLocal8Bit().data();
    s21::Controller ctr(strBuf);
    std::pair<std::string, double> res = ctr.calc();
    y.push_back(res.second);
  }
  ui->widget->addGraph()->setPen(pen);
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->widget->setBackground(QColor(211, 211, 211));
  ui->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDisc, 2));
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
}
