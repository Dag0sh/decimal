#include "../headers/s21_decimal_support_functions.h"

#include "../s21_decimal.h"
int s21_get_order(s21_decimal val) {  // don't want to have a user of lib to get
                                      // an exponent from main
  return (val.bits[3] >> 16) & 0xff;  // only 16-23 bits
}
int s21_get_order_from_float(unsigned int bits) {
  return ((bits >> 23) & 0xff);
}
int s21_from_long_decimal_to_decimal(s21_long_decimal res, int order, int sign,
                                     s21_decimal* result) {
  int return_val = CONVERSION_ERROR;
  if ((result)) {
    return_val = s21_rounding(res, order, sign, result, BANK);
  }
  return return_val;
}
void s21_set_order(s21_decimal* value, int exponent) {
  if ((value) && (exponent <= MAX_DECIMAL_ORDER)) {
    unsigned new_val =
        (exponent << 16) + (unsigned)(s21_get_sign(*value) << 31);
    value->bits[3] = new_val;
  }
}
void s21_set_sign(s21_decimal* value, unsigned int sign) {
  if (value) {
    value->bits[3] = (value->bits[3]) & ((unsigned)(1 << 31) - 1);
    value->bits[3] += (unsigned)(sign << 31);
  }
}
s21_long_decimal s21_from_decimal_to_long_decimal(s21_decimal value_1,
                                                  int order) {
  s21_long_decimal val = {{0}};
  for (int i = 0; i < 3; i++) {
    val.bits[i] = value_1.bits[i];
  }
  for (int j = 0; j < order; j++) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
      unsigned long long tmp =
          (unsigned long long)val.bits[i] * 10UL + (unsigned long long)count;
      count = tmp / (unsigned long long)(1UL << 32);
      tmp %= (unsigned long long)(1UL << 32);
      val.bits[i] = tmp;
    }
  }
  return val;
}
s21_decimal s21_get_int_min_in_decimal_form() {
  s21_decimal val = {{1 << 31, 0, 0, 1 << 31}};
  return val;
}
s21_decimal s21_get_int_max_in_decimal_form() {
  s21_decimal val = {{(unsigned)(1 << 31) - 1, 0, 0, 0}};
  return val;
}
char s21_get_sign(s21_decimal value) { return value.bits[3] >> 31; }
char s21_non_double_coding_substitution(int order1, int order2) {
  return (order1 >= order2) * (order1 - order2);
}

void s21_print_decimal(s21_decimal val) {
  for (int i = 0; i < 3; i++) {
    printf("%d bit: ", i);
    for (int j = 31; j >= 0; j--) {
      printf("%d", ((val.bits[i]) >> j) & 1);
    }
    printf(" == %u", val.bits[i]);
    printf("\n");
  }
  printf("order: %d; sign: %s\n", s21_get_order(val),
         s21_get_sign(val) ? "negative" : "positive");
}
int s21_not_null_bit(s21_long_decimal res) {
  int first_not_null = 7;
  while ((first_not_null > -1) && (res.bits[first_not_null--] == 0));
  first_not_null++;
  return first_not_null;
}
void s21_long_decimal_left_shift(s21_long_decimal* val) {
  unsigned int this_bit = val->bits[0];
  val->bits[0] = 0;
  for (int k = 0; k < 7; k++) {  // left shift
    unsigned int tmp = val->bits[k + 1];
    val->bits[k + 1] = this_bit;
    this_bit = tmp;
  }
}
void s21_digit_case(char tmp_symbol, s21_long_decimal* val) {
  int digit = tmp_symbol - '0';
  int count = 0;
  for (int j = 0; j < 8; j++) {
    unsigned long long tmp1 =
        (unsigned long long)(val->bits[j]) * 10UL + (unsigned long long)count;
    count = tmp1 / (unsigned long long)(1UL << 32);
    tmp1 %= (unsigned long long)(1UL << 32);
    val->bits[j] = tmp1;
  }
  unsigned long long tmp2 =
      (unsigned long long)(val->bits[0]) + (unsigned long long)digit;
  count = tmp2 / (unsigned long long)(1UL << 32);
  tmp2 %= (unsigned long long)(1UL << 32);
  val->bits[0] = tmp2;
  for (int j = 1; j < 8; j++) {
    unsigned long long tmp3 =
        (unsigned long long)(val->bits[j]) + (unsigned long long)count;
    count = tmp3 / (unsigned long long)(1UL << 32);
    tmp3 %= (unsigned long long)(1UL << 32);
    val->bits[j] = tmp3;
  }
}
void s21_negative_case(int i, char* negative_number, char* error_flag) {
  if (i == 0) {
    *negative_number = 1;
  } else {
    *error_flag = 1;
  }
}
int s21_rounding(s21_long_decimal res, int order, int sign, s21_decimal* result,
                 s21_type_of_rounding type) {
  int return_val = CONVERSION_ERROR;
  if (result) {
    return_val = OPERATION_IS_OK;
    int first_not_null = s21_not_null_bit(res);
    int new_order = order;
    for (int i = 0; s21_rounding_cycle_condition(i, order, first_not_null,
                                                 new_order, type);
         i++) {
      s21_long_decimal val = {{0}};
      unsigned long long surplus =
          (unsigned long long)(res.bits[first_not_null]);
      int used_bit = first_not_null;
      while (used_bit > -1) {
        s21_shifting_and_rounding(&surplus, &val, &used_bit, type, sign, res);
      }
      new_order--;
      res = val;
      first_not_null = s21_not_null_bit(res);
    }
    if (first_not_null >= 3) {
      for (int i = 0; i < 3; i++) result->bits[i] = 0;
      return_val = (sign == 0) ? NUMBER_IS_INF : NUMBER_IS_MINUS_INF;
    } else {
      for (int i = 0; i < 3; i++) result->bits[i] = res.bits[i];
      if (type > BANK) new_order = 0;
      s21_set_order(result, new_order);
      s21_set_sign(result, sign);
    }
  }
  return return_val;
}
bool s21_rounding_cycle_condition(int i, int order, int first_not_null,
                                  int new_order, s21_type_of_rounding type) {
  return (((type == BANK) && ((i < order && first_not_null >= 3) ||
                              (new_order > MAX_DECIMAL_ORDER))) ||
          ((type > BANK) && (i < 2 * order)));
}
bool s21_upper_rounding_condition(unsigned long long surplus,
                                  s21_long_decimal val,
                                  s21_type_of_rounding type, int sign) {
  return ((((surplus > 5) || ((surplus == 5) && (val.bits[0] % 2 != 0))) &&
           (type == BANK)) ||
          ((surplus >= 5) && (((type == ROUND) && (sign == 0)) ||
                              ((type == FLOOR) && (sign == 1)))));
}
void s21_long_decimal_increment(s21_long_decimal* val) {
  if (val) {
    unsigned long long tmp2 = (unsigned long long)(val->bits[0]) + 1UL;
    int count = tmp2 / (unsigned long long)(1UL << 32);
    tmp2 %= (unsigned long long)(1UL << 32);
    val->bits[0] = tmp2;
    for (int j = 1; j < 8 && count > 0; j++) {
      unsigned long long tmp3 =
          (unsigned long long)(val->bits[j]) + (unsigned long long)count;
      count = tmp3 / (unsigned long long)(1UL << 32);
      tmp3 %= (unsigned long long)(1UL << 32);
      val->bits[j] = tmp3;
    }
  }
}
void s21_decimal_div(s21_decimal* val2, s21_decimal* surplus,
                     s21_decimal value_2, s21_decimal* div_val) {
  int count = 0;
  int flag = OPERATION_IS_OK;
  s21_decimal two = {{2, 0, 0, 0}};
  while ((val2->bits[3] == 0) && s21_is_less_or_equal(*val2, *surplus) &&
         (flag == OPERATION_IS_OK)) {
    flag = s21_mul(*val2, two, val2);
    count++;
  }
  s21_decimal pow_two = {{1, 0, 0, 0}};
  for (int i = 0; i < count - 1; i++) {
    s21_mul(pow_two, two, &pow_two);
  }
  s21_mul(value_2, pow_two, val2);
  s21_add(*div_val, pow_two, div_val);
  s21_decimal sur = *surplus;
  s21_sub(sur, *val2, surplus);
  *val2 = value_2;
}
void s21_shifting_and_rounding(unsigned long long* surplus,
                               s21_long_decimal* val, int* used_bit,
                               s21_type_of_rounding type, int sign,
                               s21_long_decimal res) {
  if (*surplus >= 10) {
    val->bits[0] = (*surplus) / 10UL;
    (*surplus) %= 10UL;
  } else {
    (*used_bit)--;
    if (*used_bit > -1) {
      (*surplus) = (unsigned long)((*surplus) << 32) +
                   (unsigned long)(res.bits[(*used_bit)]);
      s21_long_decimal_left_shift(val);
    } else if (s21_upper_rounding_condition(*surplus, *val, type, sign)) {
      s21_long_decimal_increment(val);
    }
  }
}
int s21_get_bit(s21_decimal decl, int index) {
  int num_int = index / 32;
  int num_bit = index % 32;
  return (decl.bits[num_int] & (1u << num_bit)) >> num_bit;
}