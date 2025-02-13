#pragma once
#include "../s21_decimal.h"
int s21_get_order(s21_decimal val);
int s21_get_order_from_float(unsigned int bits);
int s21_from_long_decimal_to_decimal(s21_long_decimal res, int order, int sign,
                                     s21_decimal* result);
void s21_set_order(s21_decimal* value, int exponent);
void s21_set_sign(s21_decimal* value, unsigned int sign);
s21_long_decimal s21_from_decimal_to_long_decimal(s21_decimal value_1,
                                                  int order);
char s21_non_double_coding_substitution(int order1, int order2);
char s21_get_sign(s21_decimal value);
s21_decimal s21_get_int_max_in_decimal_form();
s21_decimal s21_get_int_min_in_decimal_form();
int s21_not_null_bit(s21_long_decimal res);
void s21_long_decimal_left_shift(s21_long_decimal* val);
void s21_negative_case(int i, char* negative_number, char* error_flag);
void s21_digit_case(char tmp_symbol, s21_long_decimal* val);
int s21_rounding(s21_long_decimal res, int order, int sign, s21_decimal* result,
                 s21_type_of_rounding type);
bool s21_rounding_cycle_condition(int i, int order, int first_not_null,
                                  int new_order, s21_type_of_rounding type);
bool s21_upper_rounding_condition(unsigned long long surplus,
                                  s21_long_decimal val,
                                  s21_type_of_rounding type, int sign);
void s21_long_decimal_increment(s21_long_decimal* val);
void s21_decimal_div(s21_decimal* val2, s21_decimal* surplus,
                     s21_decimal value_2, s21_decimal* div_val);
void s21_shifting_and_rounding(unsigned long long* surplus,
                               s21_long_decimal* val, int* used_bit,
                               s21_type_of_rounding type, int sign,
                               s21_long_decimal res);
int s21_get_bit(s21_decimal decl, int index);