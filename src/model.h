#ifndef SRC_MODEL_H_
#define SRC_MODEL_H_

#include <cctype>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
class Model {
 private:
  enum Symbol : char {
    FIN,
    NUM,
    PLUS = '+',
    MIN = '-',
    MUL = '*',
    DIV = '/',
    MODE = 'm',
    POW = '^',
    SIN = 's',
    COS = 'c',
    TAN = 't',
    ASIN = 'i',
    ACOS = 'o',
    ATAN = 'a',
    SQRT = 'q',
    LOG = 'n',
    LN = 'l',
    LBRAC = '(',
    RBRAC = ')'
  };

  enum Num : char {
    n0 = '0',
    n1 = '1',
    n2 = '2',
    n3 = '3',
    n4 = '4',
    n5 = '5',
    n6 = '6',
    n7 = '7',
    n8 = '8',
    n9 = '9',
    POINT = '.'
  };

 private:
  std::istream* isStr;
  std::string initStr;
  Symbol symbol;
  double number_;

  Symbol parcer();
  double power(bool flag);
  std::string checkFunc();
  void resultStr(size_t& i, size_t& j, int& pos, bool& err, size_t step,
                 bool flag);
  void checkString(std::string str);
  void checkPoint(std::string str);
  double checkFu(bool flag);
  double expression(bool flag);
  double termina(bool flag);
  void errnoFunc(std::string std, int pos, bool& err);

 public:
  Model(std::string str);
  ~Model() {}

  struct creditOut {
    std::vector<std::pair<double, double>> monthPay;
    double fullLoan;
    double overPay;
    double currentLoan;
    std::vector<double> currentDept;
    std::vector<double> bodyCredit;
  };

  double calculate();
  creditOut credit_calc(double sum, double procent, double period);
  creditOut credit_calc_diff(double sum, double procent, double period);

  std::vector<double> deposit_calc(double sum, double procent, int period,
                                   double nalog, std::map<double, int> arrPush,
                                   std::map<double, int> arrPop, int type,
                                   int capital);
  double nalogFun(double procent, double yearProfit_i);
  double arrPopper(std::map<double, int> arrPop, int numMonth);
  double arrPusher(std::map<double, int> arrPush, int numMonth);
};
}  // namespace s21
#endif  // SRC_MODEL_H_
