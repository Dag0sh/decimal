#include "../headers/s21_decimal_support_functions.h"
#include "../s21_decimal.h"
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int return_val = false;
  int exp_1 = s21_get_order(value_1);
  int exp_2 = s21_get_order(value_2);
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  if ((sign1 == sign2) && (sign1 == 0)) {
    s21_long_decimal val1 = s21_from_decimal_to_long_decimal(
        value_1, s21_non_double_coding_substitution(exp_2, exp_1));
    s21_long_decimal val2 = s21_from_decimal_to_long_decimal(
        value_2, s21_non_double_coding_substitution(exp_1, exp_2));
    int i = 7;
    while ((i > -1) && (val1.bits[i] == val2.bits[i])) {
      i--;
    }
    return_val = (i > -1) && (val1.bits[i] < val2.bits[i]);
  } else if ((sign1 == sign2) && (sign1 == 1)) {
    s21_decimal tmp1 = {{0}};
    s21_decimal tmp2 = {{0}};
    s21_negate(value_1, &tmp1);
    s21_negate(value_2, &tmp2);
    return_val = s21_is_greater(tmp1, tmp2);
  } else if ((sign1) && (sign2 == 0))
    return_val = true;
  return return_val;
}
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int return_val = false;
  int exp_1 = s21_get_order(value_1);
  int exp_2 = s21_get_order(value_2);
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  if (sign1 == sign2) {
    s21_long_decimal val1 = s21_from_decimal_to_long_decimal(
        value_1, s21_non_double_coding_substitution(exp_2, exp_1));
    s21_long_decimal val2 = s21_from_decimal_to_long_decimal(
        value_2, s21_non_double_coding_substitution(exp_1, exp_2));
    int i = 7;
    while ((i > -1) && (val1.bits[i] == val2.bits[i])) {
      i--;
    }
    return_val = (i == -1);
  }
  return return_val;
}
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2));
}
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return !(s21_is_less_or_equal(value_1, value_2));
}
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return !(s21_is_less(value_1, value_2));
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !(s21_is_equal(value_1, value_2));
}