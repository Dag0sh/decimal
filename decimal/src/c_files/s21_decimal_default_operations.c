#include "../headers/s21_decimal_support_functions.h"
#include "../s21_decimal.h"
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_val = OPERATION_IS_OK;
  if (result) {
    int exp_1 = s21_get_order(value_1);
    int exp_2 = s21_get_order(value_2);
    int sign_1 = s21_get_sign(value_1);
    int sign_2 = s21_get_sign(value_2);
    if (sign_1 == sign_2) {
      s21_long_decimal val1 = s21_from_decimal_to_long_decimal(
          value_1, s21_non_double_coding_substitution(exp_2, exp_1));
      s21_long_decimal val2 = s21_from_decimal_to_long_decimal(
          value_2, s21_non_double_coding_substitution(exp_1, exp_2));
      s21_long_decimal res = {{0}};
      unsigned int count = 0;
      for (int i = 0; i < 8; i++) {
        long long unsigned int tmp = (long long unsigned)val1.bits[i] +
                                     (long long unsigned)val2.bits[i] +
                                     (long long unsigned)count;
        count = tmp / (1UL << 32);
        tmp %= (1UL << 32);
        res.bits[i] = tmp;
      }
      int order = (exp_1 >= exp_2) ? exp_1 : exp_2;
      return_val = s21_from_long_decimal_to_decimal(
          res, order, s21_get_sign(value_1), result);
    } else {
      if (s21_get_sign(value_2)) {
        s21_decimal tmp_val = value_2;
        s21_negate(value_2, &tmp_val);
        return_val = s21_sub(value_1, tmp_val, result);
      } else {
        s21_decimal tmp_val = value_1;
        s21_negate(tmp_val, &tmp_val);
        return_val = s21_sub(value_2, tmp_val, result);
      }
    }
  }
  return return_val;
}
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_val = OPERATION_IS_OK;
  if (result) {
    int exp_1 = s21_get_order(value_1);
    int exp_2 = s21_get_order(value_2);
    int sign_1 = s21_get_sign(value_1);
    int sign_2 = s21_get_sign(value_2);
    if (s21_is_greater_or_equal(value_1, value_2)) {
      if ((sign_1 == sign_2) && (sign_1 == 0)) {
        s21_long_decimal val1 = s21_from_decimal_to_long_decimal(
            value_1, s21_non_double_coding_substitution(exp_2, exp_1));
        s21_long_decimal val2 = s21_from_decimal_to_long_decimal(
            value_2, s21_non_double_coding_substitution(exp_1, exp_2));
        s21_long_decimal val = {{0}};
        for (int i = 0; i < 8; i++) {
          long long int tmp = (unsigned long long)val1.bits[i] -
                              (unsigned long long)val2.bits[i];
          if (tmp < 0) {
            tmp += ((unsigned long long)(1UL << 32));
            int tmp_counter = i + 1;
            while ((tmp_counter < 7) && (val1.bits[tmp_counter] == 0)) {
              val1.bits[tmp_counter] = (unsigned long long)(1UL << 32) - 1UL;
              tmp_counter++;
            }
            val1.bits[tmp_counter] -= 1;
          }
          val.bits[i] = tmp;
        }
        int order = (exp_1 >= exp_2) ? exp_1 : exp_2;
        return_val =
            s21_from_long_decimal_to_decimal(val, order, sign_1, result);
      } else if ((sign_1 == sign_2) && (sign_1 == 1)) {
        s21_set_sign(&value_1, 0);
        s21_set_sign(&value_2, 0);
        return_val = s21_sub(value_2, value_1, result);
      } else {
        if (s21_get_sign(value_2))
          s21_set_sign(&value_2, 0);
        else
          s21_set_sign(&value_2, 1);
        return_val = s21_add(value_1, value_2, result);
      }
    } else {
      return_val = s21_sub(value_2, value_1, result);
      if (return_val == NUMBER_IS_INF) return_val = NUMBER_IS_MINUS_INF;
      s21_negate(*result, result);
    }
  }
  return return_val;
}
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_val = CONVERSION_ERROR;
  if (result) {
    s21_long_decimal res = {{0}};
    int count = 0;
    for (int i = 0; i < 3; i++) {
      s21_long_decimal tmp_dec = {{0}};
      for (int j = 0; j < 3; j++) {
        unsigned long tmp = (unsigned long)(value_1.bits[i]) *
                                (unsigned long)(value_2.bits[j]) +
                            (unsigned long)(count);
        count = tmp / (unsigned long)(1UL << 32);
        tmp %= (unsigned long)(1UL << 32);
        tmp_dec.bits[j] = tmp;
      }
      tmp_dec.bits[3] = count;
      count = 0;
      for (int j = 0; j < i; j++) s21_long_decimal_left_shift(&tmp_dec);
      for (int j = 0; j < 8; j++) {
        unsigned long tmp = (unsigned long)(res.bits[j]) +
                            (unsigned long)(tmp_dec.bits[j]) +
                            (unsigned long)(count);
        count = tmp / (unsigned long)(1UL << 32);
        tmp %= (unsigned long)(1UL << 32);
        res.bits[j] = tmp;
      }
    }
    int exp_1 = s21_get_order(value_1);
    int exp_2 = s21_get_order(value_2);
    int sign_1 = s21_get_sign(value_1);
    int sign_2 = s21_get_sign(value_2);
    int order = exp_1 + exp_2;
    int sign = sign_1 > sign_2 ? sign_1 : sign_2;
    return_val = s21_from_long_decimal_to_decimal(res, order, sign, result);
  }
  return return_val;
}
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_val = CONVERSION_ERROR;
  if (result) {
    return_val = OPERATION_IS_OK;
    s21_decimal zero = {{0}};
    if (s21_is_not_equal(value_2, zero)) {
      int exp_1 = s21_get_order(value_1);
      int exp_2 = s21_get_order(value_2);
      int sign_1 = s21_get_sign(value_1);
      int sign_2 = s21_get_sign(value_2);
      int sign = sign_1 > sign_2 ? sign_1 : sign_2;
      s21_decimal val1 = value_1;
      s21_decimal val2 = value_2;
      s21_set_sign(&val1, 0);
      s21_set_sign(&val2, 0);
      s21_set_order(&val1, 0);
      s21_set_order(&val2, 0);
      int new_order = exp_1 - exp_2;
      s21_decimal div_val = {{0}};
      s21_decimal surplus = val1;
      s21_decimal ten = {{10, 0, 0, 0}};
      char flag = OPERATION_IS_OK;
      while (s21_is_greater_or_equal(surplus, val2)) {
        s21_decimal_div(&val2, &surplus, val2, &div_val);
      }
      while ((new_order < 0) && (flag == OPERATION_IS_OK)) {
        flag = s21_mul(div_val, ten, &div_val);
        new_order++;
      }
      if (!flag) {
        s21_set_order(&div_val, new_order);
        s21_decimal mod_val = {{0}};
        while (s21_is_not_equal(surplus, zero) && new_order < 28 &&
               (flag == OPERATION_IS_OK)) {
          flag = s21_mul(surplus, ten, &surplus);
          s21_mul(mod_val, ten, &mod_val);
          while (s21_is_greater_or_equal(surplus, val2)) {
            s21_decimal_div(&val2, &surplus, val2, &mod_val);
          }
          new_order++;
        }
        s21_set_order(&mod_val, new_order);
        s21_add(div_val, mod_val, result);
      } else {
        return_val = (sign == 0) ? NUMBER_IS_INF : NUMBER_IS_MINUS_INF;
      }
    } else {
      return_val = DIVISION_BY_ZERO;
    }
  }
  return return_val;
}