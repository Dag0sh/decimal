#include "../headers/s21_decimal_support_functions.h"
#include "../s21_decimal.h"
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int val = CONVERSION_ERROR;
  if (dst) {
    dst->bits[3] = (src < 0) << 31;
    dst->bits[2] = 0;
    dst->bits[1] = 0;
    dst->bits[0] = abs(src);
    val = OPERATION_IS_OK;
  }
  return val;
}
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int val = CONVERSION_ERROR;
  if ((dst) && (src - 79228162514264337593543950335.0 < 1E-6) &&
      (fabs(src) > 1E-28)) {
    int len = snprintf(NULL, 0, "%.7e", src);
    char *string = malloc(len + 1);
    if (string) {
      snprintf(string, len + 1, "%.7e", src);
      *dst = s21_from_string_to_decimal(string);  // stupid indian code guys
      val = OPERATION_IS_OK;
      free(string);
    }
  }
  return val;
}
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int return_val = CONVERSION_ERROR;
  if ((dst) &&
      (s21_is_greater_or_equal(src, s21_get_int_min_in_decimal_form())) &&
      (s21_is_less_or_equal(src, s21_get_int_max_in_decimal_form()))) {
    s21_decimal val = {{0}};
    s21_truncate(src, &val);
    int bits = val.bits[0] & ((unsigned)(1 << 31) - 1);
    if (s21_get_sign(val) == 0)
      *dst = bits;
    else {
      *dst = (~bits + 1);
      if (*dst == 0) *dst = -2147483647 - 1;
    }
    return_val = OPERATION_IS_OK;
  }
  return return_val;
}
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int val = OPERATION_IS_OK;

  int order = s21_get_order(src);
  int sign = s21_get_sign(src);
  double tmp = 0.0;
  for (int i = 0; i < 96; i++) {
    if (s21_get_bit(src, i)) {
      tmp += (double)pow(2, i);
    }
  }
  tmp /= pow(10.0, order);
  if (sign) {
    tmp = tmp * (-1.0);
  }
  *dst = (float)tmp;
  return val;
}

s21_decimal s21_from_string_to_decimal(char *string) {
  s21_decimal return_val = {{0}};
  s21_long_decimal val = {{0}};
  int i = 0;
  int fp = 0;
  int new_order = 0;
  char error_flag = 0;
  char negative_number = 0;
  char exp_flag = 0;
  if (string) {
    while (string[i] != '\0' && !error_flag && !exp_flag) {
      switch (string[i]) {
        case '-':
          s21_negative_case(i, &negative_number, &error_flag);
          break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          s21_digit_case(string[i], &val);
          break;
        case '.':
          if (fp)
            error_flag = 1;
          else
            fp = i;
          break;
        case 'E':
        case 'e':
          if (!new_order) {
            exp_flag = 1;
            int j = i + 1;
            int sign = 0;
            while (string[j] != '\0') {
              if (string[j] == '-')
                sign = 1;
              else if ((string[j] <= '9') && (string[j] >= '0'))
                new_order = new_order * 10 + (string[j] - '0');
              j++;
            }
            if (sign) new_order *= -1;
          } else {
            error_flag = 1;
          }
          break;
        default:
          error_flag = 1;
          break;
      }
      i++;
    }
  } else {
    error_flag = 1;
  }
  if (!error_flag) {
    if (new_order) new_order++;
    int order = i - 1 - fp - new_order;
    if (fp == 0) order = 0;
    s21_set_sign(&return_val, negative_number);
    s21_set_order(&return_val, order);
    int error = s21_from_long_decimal_to_decimal(val, order, negative_number,
                                                 &return_val);
    if (error) {
      for (int i = 0; i < 3; i++) return_val.bits[i] = 0;
    }
  }
  return return_val;
}
