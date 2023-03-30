#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include <string>
#include <vector>

#include "model.h"

namespace s21 {
class Controller {
 private:
  std::string initString;

 public:
  explicit Controller(std::string const &str = "") : initString(str) {}
  std::pair<std::string, double> calc();
  Model::creditOut credit_ann(double sum, double procent, double period);
  Model::creditOut creditDiff_calc(double sum, double procent, double period);
  std::vector<double> deposit(double sum, double procent, int period,
                              double nalog, std::vector<double> arrPush,
                              std::vector<double> arrPop, int type,
                              int capital);
  std::vector<double> deposit(double sum, double procent, int period,
                              double nalog, std::map<double, int> arrPush,
                              std::map<double, int> arrPop, int type,
                              int capital);
};

}  // namespace s21
#endif  // SRC_CONTROLER_H_
