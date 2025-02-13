#pragma once
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OPERATION_IS_OK 0
#define NUMBER_IS_INF 1
#define NUMBER_IS_MINUS_INF 2
#define DIVISION_BY_ZERO 3
#define CONVERSION_ERROR 4
#define MAX_DECIMAL_ORDER 28

typedef struct s21_decimal {
  unsigned int bits[4];
} s21_decimal;
typedef struct s21_long_decimal {
  unsigned int bits[8];
} s21_long_decimal;
typedef union s21_exponential {
  unsigned int bits;
  float number;
} s21_exponential;
typedef enum s21_type_of_rounding {
  BANK,
  FLOOR,
  TRUNCATE,
  ROUND
} s21_type_of_rounding;

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

s21_decimal s21_from_string_to_decimal(char *string);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

void s21_print_decimal(s21_decimal val);