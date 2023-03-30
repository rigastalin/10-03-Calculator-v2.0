#include "controller.h"

namespace s21 {
std::pair<std::string, double> Controller::calc() {
  std::string err = "";
  double res = 0.0;
  try {
    Model model(initString);
    res = model.calculate();
  } catch (const std::exception& exc) {
    err = exc.what();
  }
  std::pair<std::string, double> result = {err, res};
  return result;
}

Model::creditOut Controller::credit_ann(double sum, double procent,
                                        double period) {
  Model model(initString);
  return model.credit_calc(sum, procent, period);
}

Model::creditOut Controller::creditDiff_calc(double sum, double procent,
                                             double period) {
  Model model(initString);
  return model.credit_calc_diff(sum, procent, period);
}

std::vector<double> Controller::deposit(double sum, double procent, int period,
                                        double nalog,
                                        std::map<double, int> arrPush,
                                        std::map<double, int> arrPop, int type,
                                        int capital) {
  Model model(initString);
  return model.deposit_calc(sum, procent, period, nalog, arrPush, arrPop, type,
                            capital);
}

}  // namespace s21
