#include "../headers/s21_decimal_support_functions.h"
#include "../s21_decimal.h"
int s21_floor(s21_decimal value, s21_decimal *result) {
  int order = s21_get_order(value);
  s21_long_decimal tmp = s21_from_decimal_to_long_decimal(value, order);
  int return_val = s21_rounding(tmp, order, s21_get_sign(value), result, FLOOR);
  return return_val;
}
int s21_round(s21_decimal value, s21_decimal *result) {
  int order = s21_get_order(value);
  int sign = s21_get_sign(value);
  s21_long_decimal tmp = s21_from_decimal_to_long_decimal(value, order);
  int return_val = s21_rounding(tmp, order, sign, result, ROUND);
  return return_val;
}
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int order = s21_get_order(value);
  s21_long_decimal tmp = s21_from_decimal_to_long_decimal(value, order);
  int return_val =
      s21_rounding(tmp, order, s21_get_sign(value), result, TRUNCATE);
  return return_val;
}
int s21_negate(s21_decimal value, s21_decimal *result) {
  int return_val = CONVERSION_ERROR;
  s21_decimal zero = {{0, 0, 0, 0}};
  if ((result) && (s21_is_not_equal(value, zero))) {
    for (int i = 0; i < 3; i++) {
      result->bits[i] = value.bits[i];
    }
    s21_set_order(result, s21_get_order(value));
    s21_set_sign(result, !(s21_get_sign(value)));
    return_val = OPERATION_IS_OK;
  }
  return return_val;
}