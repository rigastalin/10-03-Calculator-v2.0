#include <gtest/gtest.h>

#include <iostream>

#include "controller.h"
#include "model.h"

TEST(calculator, test_1) {
  std::string str = "log(100)";
  double result = 2;
  s21::Model model(str);
  double res = model.calculate();
  ASSERT_EQ(result, res);
}

TEST(calculator, test1) {
  std::string str = "2+3+4+5-5-4-3-2-6";
  double result = -6;
  s21::Model model(str);
  double res = model.calculate();
  ASSERT_EQ(result, res);
}

TEST(calculator, test_2) {
  std::string str = "ln(2.718281828459045)";
  double result = 1;
  s21::Model model(str);
  double res = model.calculate();
  ASSERT_EQ(result, res);
}

TEST(calculator, test_3) {
  std::string str = "2^3^4";
  double result = 4096;
  s21::Model model(str);
  double res = model.calculate();
  ASSERT_EQ(result, res);
}

TEST(calculator, test31) {
  std::string str = "sqrt(9)";
  double result = 3;
  s21::Model model(str);
  double res = model.calculate();
  ASSERT_EQ(result, res);
}

TEST(calculator, test_4) {
  std::string str = "cos(3.141592653589793)";
  double result = -1;
  s21::Model model(str);
  double res = model.calculate();
  ASSERT_EQ(result, res);
}

TEST(calculator, test4) {
  std::string str = "sin(0)";
  double result = 0;
  s21::Model model(str);
  double res = model.calculate();
  ASSERT_EQ(result, res);
}

TEST(calculator, test_5) {
  std::string str =
      "1+2+3+4+5+6+7+8+9+0-1-2-3-4-5-6-7-8-9*1*2*3*4*5*6*7*8*9/1/2/3/4/5/6/7/8/"
      "9";
  double result = 0;
  s21::Model model(str);
  double res = model.calculate();
  ASSERT_EQ(result, res);
}

TEST(calculator, test_6) {
  std::string str = "(4+456)-(2343-666)*((45*3)-(55-666))";
  double result = -1250582;
  s21::Model model(str);
  double res = model.calculate();
  ASSERT_EQ(result, res);
}

TEST(calculator, test_7) {
  std::string str = "tan(0)";
  double result = 0;
  s21::Model model(str);
  double res = model.calculate();
  ASSERT_EQ(result, res);
}

TEST(calculator, test_8) {
  std::string str = "atan(0)";
  double result = 0;
  s21::Model model(str);
  double res = model.calculate();
  ASSERT_EQ(result, res);
}

TEST(calculator, test_9) {
  std::string str = "asin(1)";
  double result = 1.5707963267948966;
  s21::Model model(str);
  double res = model.calculate();
  ASSERT_EQ(result, res);
}

TEST(calculator, test_10) {
  std::string str = "acos(0)";
  double result = 1.5707963267948966;
  s21::Model model(str);
  double res = model.calculate();
  ASSERT_EQ(result, res);
}

TEST(calculator, test_11) {
  std::string str = "1mod(5)";
  double result = 1;
  s21::Model model(str);
  double res = model.calculate();
  ASSERT_EQ(result, res);
}

TEST(calculator, credit) {
  double sum = 100000;
  double period = 12;
  double procent = 10;
  s21::Model::creditOut res;
  s21::Model model("");
  res = model.credit_calc(sum, procent, period);
  ASSERT_EQ(res.overPay, 5499.08);
  ASSERT_EQ(res.fullLoan, 105499.08);
  ASSERT_EQ(res.monthPay[1].first, 8791.59);
}

TEST(calculator, credit2) {
  double sum = 100000;
  double period = 12;
  double procent = 10;
  s21::Model::creditOut res;
  s21::Model model("");
  res = model.credit_calc_diff(sum, procent, period);
  ASSERT_EQ(res.overPay, 5416.67);
  ASSERT_EQ(res.fullLoan, 105416.67);
}

TEST(calculator, deposit) {
  double sum = 1300000;
  double period = 12;
  double procent = 10;
  double nalog = 13;
  std::map<double, int> arrPush;
  std::map<double, int> arrPop;
  int type = 1;
  int capital = 1;
  std::vector<double> res;
  s21::Model model("");
  res = model.deposit_calc(sum, procent, period, nalog, arrPush, arrPop, type,
                           capital);
  ASSERT_EQ(res[0], 6500.000000000017280);
  ASSERT_EQ(res[1], 130000.0000000001300);
  ASSERT_EQ(res[2], 1430000.000000000232831);
}

TEST(calculator, deposit2) {
  double sum = 1300000;
  double period = 12;
  double procent = 10;
  double nalog = 13;
  std::map<double, int> arrPush;
  std::map<double, int> arrPop;
  int type = 2;
  int capital = 1;
  std::vector<double> res;
  s21::Model model("");
  res = model.deposit_calc(sum, procent, period, nalog, arrPush, arrPop, type,
                           capital);
  ASSERT_EQ(res[0], 7296.520833333353949);
  ASSERT_EQ(res[1], 136127.083333333488554);
  ASSERT_EQ(res[2], 1436127.083333333488554);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
