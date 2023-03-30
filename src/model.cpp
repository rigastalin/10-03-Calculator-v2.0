#include "model.h"

namespace s21 {
Model::Model(std::string str) {
  if (str.length() > 255) {
    throw std::out_of_range("The expression is too long");
  } else {
    initStr = str;
    isStr = nullptr;
    symbol = NUM;
    number_ = n0;
  }
}

typename Model::Symbol Model::parcer() {
  char token;
  do {
    if (!isStr->get(token)) {
      return symbol = FIN;
    }
  } while (token != '\n' && isspace(token));
  switch (token) {
    case 0:
      return symbol = FIN;
    case PLUS:
    case MIN:
    case MUL:
    case DIV:
    case MODE:
    case POW:
    case SIN:
    case COS:
    case TAN:
    case ASIN:
    case ACOS:
    case ATAN:
    case SQRT:
    case LOG:
    case LN:
    case LBRAC:
    case RBRAC:
      return symbol = Symbol(token);
    case n0:
    case n1:
    case n2:
    case n3:
    case n4:
    case n5:
    case n6:
    case n7:
    case n8:
    case n9:
    case POINT: {
      isStr->putback(token);
      *isStr >> number_;
      return symbol = NUM;
    }
    default:
      throw std::invalid_argument("Error: wrong symbol");
  }
}

double Model::checkFu(bool flag) {
  if (flag) parcer();
  switch (symbol) {
    case NUM: {
      double temp = number_;
      parcer();
      return temp;
    }
    case MIN:
      return -checkFu(true);
    case PLUS:
      return checkFu(true);
    case SIN:
      return sin(checkFu(true));
    case COS:
      return cos(checkFu(true));
    case TAN:
      return tan(checkFu(true));
    case ATAN:
      return atan(checkFu(true));
    case ASIN:
      return asin(checkFu(true));
    case ACOS:
      return acos(checkFu(true));
    case LOG:
      return log10(checkFu(true));
    case SQRT:
      return sqrt(checkFu(true));
    case LN:
      return log(checkFu(true));
    case LBRAC: {
      double temp = expression(true);
      if (symbol != RBRAC) {
        throw std::invalid_argument("Error: smt wrong with brakets");
      }
      parcer();
      return temp;
    }
    default:
      throw std::invalid_argument("Error: smt wrong with expression...");
  }
}

double Model::power(bool flag) {
  double temp = checkFu(flag);
  while (true) {
    if (symbol == POW)
      temp = pow(temp, checkFu(true));
    else
      return temp;
  }
}

double Model::expression(bool flag) {
  double temp = termina(flag);
  while (true) {
    switch (symbol) {
      case PLUS:
        temp += termina(true);
        break;
      case MIN:
        temp -= termina(true);
        break;
      case MUL:

      default:
        return temp;
    }
  }
}

double Model::termina(bool flag) {
  double temp = power(flag);
  while (true) {
    switch (symbol) {
      case MUL:
        temp *= power(true);
        break;
      case DIV:
        if (double tmp = power(true)) {
          temp /= tmp;
          break;
        } else {
          throw std::invalid_argument("Error: dividing by 0");
        }
      case MODE:
        if (double tmp = power(true)) {
          temp = fmod(temp, tmp);
          break;
        } else {
          throw std::invalid_argument("Error: 0 mode");
        }
      default:
        return temp;
    }
  }
}

std::string Model::checkFunc() {
  std::string outStr(255, ' ');
  bool err = true;
  int pos = 0;
  size_t i = 0, j = 0;
  for (; i < initStr.size();) {
    if (initStr[i] == 'm') {
      if (initStr[i + 1] == 'o' && initStr[i + 2] == 'd') {
        outStr[j] = 'm';
        resultStr(i, j, pos, err, 3, true);
      } else {
        throw std::invalid_argument("Error: smt wrong with mod");
      }
    } else if (initStr[i] == 's') {
      if (initStr[i + 1] == 'i' && initStr[i + 2] == 'n') {
        outStr[j] = 's';
        resultStr(i, j, pos, err, 3, false);
      } else if (initStr[i + 1] == 'q' && initStr[i + 2] == 'r' &&
                 initStr[i + 3] == 't') {
        outStr[j] = 'q';
        resultStr(i, j, pos, err, 4, false);
      }
      errnoFunc(initStr, pos, err);
    } else if (initStr[i] == 'c') {
      if (initStr[i + 1] == 'o' && initStr[i + 2] == 's') {
        outStr[j] = 'c';
        resultStr(i, j, pos, err, 3, false);
      }
      errnoFunc(initStr, pos, err);
    } else if (initStr[i] == 't') {
      if (initStr[i + 1] == 'a' && initStr[i + 2] == 'n') {
        outStr[j] = 't';
        resultStr(i, j, pos, err, 3, false);
      }
      errnoFunc(initStr, pos, err);
    } else if (initStr[i] == 'a') {
      if (initStr[i + 1] == 't' && initStr[i + 2] == 'a' &&
          initStr[i + 3] == 'n') {
        outStr[j] = 'a';
        resultStr(i, j, pos, err, 4, false);
      } else if (initStr[i + 1] == 's' && initStr[i + 2] == 'i' &&
                 initStr[i + 3] == 'n') {
        outStr[j] = 'i';
        resultStr(i, j, pos, err, 4, false);
      } else if (initStr[i + 1] == 'c' && initStr[i + 2] == 'o' &&
                 initStr[i + 3] == 's') {
        outStr[j] = 'o';
        resultStr(i, j, pos, err, 4, false);
      }
      errnoFunc(initStr, pos, err);
    } else if (initStr[i] == 'l' && initStr[i + 1] == 'o' &&
               initStr[i + 2] == 'g') {
      outStr[j] = 'n';
      resultStr(i, j, pos, err, 3, false);
      errnoFunc(initStr, pos, err);
    } else if (initStr[i] == 'l' && initStr[i + 1] == 'n') {
      outStr[j] = 'l';
      resultStr(i, j, pos, err, 2, false);
      errnoFunc(initStr, pos, err);
    } else if (initStr[i] == 'n' || initStr[i] == 'q' || initStr[i] == 'i' ||
               initStr[i] == 'g' || initStr[i] == 'o') {
      throw std::invalid_argument("Error: there is no such thing");
    } else {
      outStr[j] = initStr[i];
      resultStr(i, j, pos, err, 1, true);
    }
  }
  outStr.erase(outStr.find_last_not_of(' ') + 1, std::string::npos);
  return outStr;
}

void Model::errnoFunc(std::string str, int pos, bool& err) {
  if ((pos >= 0 && str[pos] == ')') ||
      (pos >= 0 && (str[pos] >= '0' && str[pos] <= '9'))) {
    err = true;
  }
  if (err == true) {
    throw std::invalid_argument("Error...");
  }
  err = true;
}

void Model::resultStr(size_t& i, size_t& j, int& pos, bool& err, size_t step,
                      bool flag) {
  pos = i - 1;
  i = i + step;
  ++j;
  err = flag;
}

void Model::checkString(std::string str) {
  std::string contolStr = "0123456789.+-*/^msctlnioaq()";
  std::basic_string<char>::size_type contj;
  int rBr = 0, lBr = 0;
  bool err = false;
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == '(') {
      ++lBr;
      errnoFunc(str, i - 1, err);
      err = false;
    }
    if (str[i] == ')') {
      ++rBr;
      if ((str[i + 1] >= '0' && str[i + 1] <= '9') || str[i + 1] == '(')
        throw std::invalid_argument("Error: wrong input");
    }
    contj = contolStr.find(str[i]);
    if (contj == std::string::npos)
      throw std::invalid_argument("Error: Wrong symbols");
  }
  if (lBr != rBr)
    throw std::invalid_argument("Error: Number of brackets not equal");
}

void Model::checkPoint(std::string str) {
  for (size_t i = 0; i < str.size(); ++i) {
    int counter = 0;
    while (i < str.size() &&
           ((str[i] >= '0' && str[i] <= '9') || str[i] == '.')) {
      ++i;
      if (str[i] == '.') {
        counter += 1;
      }
    }
    if (counter > 1) {
      throw std::invalid_argument("Error: too many points...");
    }
  }
}

double Model::calculate() {
  std::string string = checkFunc();
  checkString(string);
  checkPoint(string);
  isStr = new std::istringstream(string);
  double result = 0.0;
  while (isStr) {
    parcer();
    if (symbol == FIN) break;
    result = expression(false);
  }
  if (isStr != nullptr) delete isStr;
  return result;
}

// <============================== CREDIT CALCULATOR
// ==============================>
Model::creditOut Model::credit_calc(double sum, double procent, double period) {
  double monthPay, koefAnn = 0.0;
  double monthProc = (procent / 12) / 100;

  koefAnn = (monthProc * (pow(1 + monthProc, period))) /
            ((pow(1 + monthProc, period)) - 1);
  monthPay = koefAnn * sum;

  creditOut result;
  result.fullLoan = 0;
  std::pair<double, double> pay;
  std::vector<double> currentDept;
  std::vector<double> bodyCredit;
  double currentLoan = sum;

  for (int i = 0; i < period; i++) {
    pay.first = round(monthPay * 100) / 100;
    pay.second = round(currentLoan * monthProc * 100) / 100;
    currentLoan -= (pay.first - pay.second);
    result.currentDept.push_back(currentLoan);
    result.currentLoan = currentLoan - pay.first;
    result.bodyCredit.push_back(pay.first - pay.second);
    result.monthPay.push_back(pay);
    result.fullLoan += pay.first;
  }
  result.overPay = result.fullLoan - sum;
  result.fullLoan = round(result.fullLoan * 100) / 100;
  result.overPay = round(result.overPay * 100) / 100;
  return result;
}

Model::creditOut Model::credit_calc_diff(double sum, double procent,
                                         double period) {
  double monthPay = 0.0;
  double monthProc = (procent / 100) / 12;

  creditOut result;
  result.fullLoan = 0;
  std::pair<double, double> pay;
  std::vector<double> currentDept;
  std::vector<double> bodyCredit;

  double currentLoan = sum;
  monthPay = currentLoan / period;

  for (int i = 0; i < period; i++) {
    pay.first = monthPay + (monthProc * currentLoan);
    pay.second = round(currentLoan * monthProc * 100) / 100;
    result.monthPay.push_back(pay);
    currentLoan -= (pay.first - pay.second);
    result.currentDept.push_back(currentLoan);
    result.currentLoan = currentLoan - pay.first;
    result.bodyCredit.push_back(pay.first - pay.second);
    result.fullLoan += pay.first;
  }
  result.overPay = result.fullLoan - sum;
  result.fullLoan = round(result.fullLoan * 100) / 100;
  result.overPay = round(result.overPay * 100) / 100;
  return result;
}

// <============================== DEPOSIT CALCULATOR
// ==============================>
double Model::nalogFun(double procent, double yearProfit_i) {
  double mustPay = 0.0;
  double free = (1000000 * 8) / 100;  // rate CB - 8% in 13.09.2022
  double payment = yearProfit_i - free;
  if (payment > 0) {
    mustPay = (payment * procent) / 100;
  } else {
    mustPay = 0.0;
  }
  return mustPay;
}

double Model::arrPusher(std::map<double, int> arrPush, int numMonth) {
  double res = 0.0;
  auto it = arrPush.begin();
  for (; it != arrPush.end(); ++it) {
    int flag = (int)it->second;
    if (flag == numMonth) {
      res += it->first;
    }
  }
  return res;
}

double Model::arrPopper(std::map<double, int> arrPop, int numMonth) {
  double res = 0.0;
  auto it = arrPop.begin();
  for (; it != arrPop.end(); ++it) {
    int flag = (int)it->second;
    if (flag == numMonth) {
      res += it->first;
    }
  }
  return res;
}

std::vector<double> Model::deposit_calc(double sum, double procent, int period,
                                        double nalog,
                                        std::map<double, int> arrPush,
                                        std::map<double, int> arrPop, int type,
                                        int capital) {
  std::vector<double> res = {3};
  double days = 30.4166666666667;
  double year = 365;
  double finalProfit = 0.0;
  double totalSum = 0.0;
  double yearProfit = 0.0;
  double yearProfit_i = 0.0;
  double taxesPay_i = 0.0;
  double taxesPayFull = 0.0;
  double dayProfit = 0.0;
  double monthProfit_i = 0.0;
  double monthSum_i = sum;

  if (sum != 0.0 && period != 0 && procent != 0.0 && nalog != 0.0) {
    if ((type == 1) || (type == 2 && capital == 0)) {
      for (int i = 0; i < period; ++i) {
        if (i != 0 && i % 12 == 0 && type == 2) {
          taxesPay_i = nalogFun(nalog, yearProfit_i);
          taxesPayFull = taxesPayFull + taxesPay_i;
          yearProfit_i = 0;
        }
        if (i != 0 && i != period - 1 && period > 2) {
          monthSum_i = monthSum_i + arrPusher(arrPush, i);
          monthSum_i = monthSum_i - arrPopper(arrPop, i);
          sum = sum + arrPusher(arrPush, i);
          sum = sum - arrPopper(arrPop, i);
        }
        yearProfit = round(monthSum_i * (procent / 100));
        dayProfit = yearProfit / year;
        monthProfit_i = dayProfit * days;

        yearProfit_i = yearProfit_i + monthProfit_i;
        finalProfit = finalProfit + monthProfit_i;
      }

      if (type == 2) {
        taxesPay_i = nalogFun(nalog, yearProfit_i);
        taxesPayFull = taxesPayFull + taxesPay_i;
      } else {
        taxesPayFull = nalogFun(nalog, yearProfit_i);
      }

      if (capital == 0) {
        totalSum = totalSum + sum;
      }
      if (capital == 1) {
        totalSum = totalSum + sum + finalProfit;
      }

      return res = {taxesPayFull, finalProfit, totalSum};

    } else if (type == 2 && capital == 1) {
      for (int i = 1; i <= period; i++) {
        if (i != 1 && i != period && period) {
          monthSum_i = monthSum_i + arrPusher(arrPush, i);
          monthSum_i = monthSum_i - arrPopper(arrPop, i);
          sum = sum + arrPusher(arrPush, i);
          sum = sum - arrPopper(arrPop, i);
        }
        yearProfit = round((monthSum_i * procent) / 100);
        dayProfit = yearProfit / year;
        monthProfit_i = dayProfit * days;

        yearProfit_i = yearProfit_i + monthProfit_i;
        monthSum_i = monthSum_i + monthProfit_i;
        finalProfit = finalProfit + monthProfit_i;

        if (i % 12 == 0) {
          taxesPay_i = nalogFun(nalog, yearProfit_i);
          taxesPayFull = taxesPayFull + taxesPay_i;
          yearProfit_i = 0;
        }
      }
      taxesPay_i = nalogFun(nalog, yearProfit_i);
      taxesPayFull = taxesPayFull + taxesPay_i;
      totalSum = totalSum + finalProfit + sum;

      return res = {taxesPayFull, finalProfit, totalSum};
    } else {
      return res = {taxesPayFull, finalProfit, totalSum};
    }
  }
  return res;
}

}  //  namespace s21
