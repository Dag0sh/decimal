#include <check.h>

#include "s21_decimal.h"
// "79228162514264337593543950335" is a max supported value of decimal(if value
// is greater than that, it will be an overflow and all zeros in bits)

/// @brief Tests to show a workability of comparing functions
START_TEST(s21_equality_test_case_1) {
  char* string1 =
      "1."
      "000000000000000000000000000000000000000000000000000000000000000000000000"
      "000";
  char* string2 = "1";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  ck_assert(s21_is_equal(val1, val2));
}
START_TEST(s21_equality_test_case_2) {
  char* string1 = "-1";
  char* string2 = "1";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  ck_assert(!s21_is_equal(val1, val2));
}
START_TEST(s21_equality_test_case_3) {
  char* string1 = "79228162514264337593543950335";
  char* string2 = "79228162514264337593543950335.00000000000000000";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  ck_assert(s21_is_equal(val1, val2));
}
START_TEST(s21_equality_test_case_4) {
  char* string1 = "79228162514264337593543950335.1";  // will be rounded down
  char* string2 = "79228162514264337593543950335.00000000000000000";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  ck_assert(s21_is_equal(val1, val2));
}
START_TEST(s21_lessity_test_case_1) {
  char* string1 = "-79228162514264337593543950335.1";
  char* string2 = "79228162514264337593543950335.00000000000000000";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  ck_assert(s21_is_less(val1, val2));
}
START_TEST(s21_lessity_test_case_2) {
  char* string1 = "79228162514264337593.5439503351";
  char* string2 = "7922816251426.4337593543950335";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  ck_assert(!s21_is_less(val1, val2));
}
START_TEST(s21_lessity_test_case_3) {
  char* string1 = "5010.2321232";
  char* string2 = "798989.8922328391282319";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  ck_assert(s21_is_less(val1, val2));
}
START_TEST(s21_lessity_test_case_4) {
  char* string1 = "42949.67296";
  char* string2 = "42949.67297";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  ck_assert(s21_is_less(val1, val2));
}

/// @brief Tests to show a workability of standard operations functions
START_TEST(s21_addity_test_case_1) {
  char* string1 = "7922816251426433759354395033.5";
  char* string2 = "0.79228162514264337593543950335";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  ck_assert(
      (s21_add(val1, val2, &result) == OPERATION_IS_OK) &&
      s21_is_equal(
          result,
          s21_from_string_to_decimal(
              "7922816251426433759354395034.29228162514264337593543950335")));
}
START_TEST(s21_addity_test_case_2) {
  char* string1 = "1";
  char* string2 = "2";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  ck_assert((s21_add(val1, val2, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("3")));
}
START_TEST(s21_addity_test_case_3) {
  char* string1 = "79228162514264337593543950335";
  char* string2 = "-79228162514264337593543950335";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  ck_assert((s21_add(val1, val2, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("0")));
}
START_TEST(s21_addity_test_case_4) {
  char* string1 = "79228162514264337593543950335";
  char* string2 = "1";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  ck_assert((s21_add(val1, val2, &result) == NUMBER_IS_INF));
}
START_TEST(s21_addity_test_case_5) {
  char* string1 = "-79228162514264337593543950335";
  char* string2 = "79228162514264337593543950335";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  ck_assert((s21_add(val1, val2, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("0")));
}
START_TEST(s21_subity_test_case_1) {
  char* string1 = "0.12345678912345";
  char* string2 = "0.01234567801234";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  ck_assert(
      (s21_sub(val1, val2, &result) == OPERATION_IS_OK) &&
      s21_is_equal(result, s21_from_string_to_decimal("0.11111111111111")));
}
START_TEST(s21_subity_test_case_2) {
  char* string1 = "184467440737095.51616";
  char* string2 = "1";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  int val = s21_sub(val1, val2, &result);
  ck_assert((val == OPERATION_IS_OK) &&
            s21_is_equal(result,
                         s21_from_string_to_decimal("184467440737094.51616")));
}
START_TEST(s21_subity_test_case_3) {
  char* string1 = "-1";
  char* string2 = "-2";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  ck_assert((s21_sub(val1, val2, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("1")));
}
START_TEST(s21_subity_test_case_4) {
  char* string1 = "-79228162514264337593543950335";
  char* string2 = "1";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  ck_assert((s21_sub(val1, val2, &result) == NUMBER_IS_MINUS_INF));
}
START_TEST(s21_subity_test_case_5) {
  char* string1 = "1";
  char* string2 = "10000000";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  ck_assert((s21_sub(val1, val2, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("-9999999")));
}
START_TEST(s21_mulity_test_case_1) {
  char* string1 = "1";
  char* string2 = "-2.00000000000";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  ck_assert((s21_mul(val1, val2, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("-2")));
}
START_TEST(s21_mulity_test_case_2) {
  char* string1 = "0.15555";
  char* string2 = "2";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  ck_assert((s21_mul(val1, val2, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("0.3111")));
}
START_TEST(s21_mulity_test_case_3) {
  char* string1 = "99.9";
  char* string2 = "-999";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  ck_assert((s21_mul(val1, val2, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("-99800.1")));
}
START_TEST(s21_mulity_test_case_4) {
  char* string1 = "-79228162514264337593543950335";
  char* string2 = "1";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  ck_assert((s21_mul(val1, val2, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal(
                                     "-79228162514264337593543950335")));
}
START_TEST(s21_divity_test_case_1) {
  char* string1 = "1.00000000";
  char* string2 = "2";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  ck_assert((s21_div(val1, val2, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("0.5")));
}
START_TEST(s21_divity_test_case_2) {
  char* string1 = "4294967295";
  char* string2 = "128";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  ck_assert(
      (s21_div(val1, val2, &result) == OPERATION_IS_OK) &&
      s21_is_equal(result, s21_from_string_to_decimal("33554431.9921875")));
}
START_TEST(s21_divity_test_case_3) {
  char* string1 = "184467440737095.5162";
  char* string2 = "3";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  int flag = s21_div(val1, val2, &result);
  ck_assert((flag == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal(
                                     "61489146912365.172066666666667")));
}
START_TEST(s21_divity_test_case_4) {
  char* string1 = "1";
  char* string2 = "20";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal val2 = s21_from_string_to_decimal(string2);
  s21_decimal result = {{0}};
  ck_assert((s21_div(val1, val2, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("0.05")));
}

/// @brief rounding functions tests
START_TEST(s21_roundity_test_case_1) {
  char* string1 = "79228.162514264337593543950335";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal result = {{0}};
  s21_round(val1, &result);
  ck_assert(s21_is_equal(result, s21_from_string_to_decimal("79228")));
}
START_TEST(s21_roundity_test_case_2) {
  char* string1 = "1.0";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal result = {{0}};
  ck_assert((s21_round(val1, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("1")));
}
START_TEST(s21_roundity_test_case_3) {
  char* string1 = "0.79228162514264337593543950335";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal result = {{0}};
  ck_assert((s21_round(val1, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("1")));
}
START_TEST(s21_roundity_test_case_4) {
  char* string1 = "0.1234321";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal result = {{0}};
  int res = s21_round(val1, &result);
  ck_assert(res == OPERATION_IS_OK &&
            s21_is_equal(result, s21_from_string_to_decimal("0")));
}
START_TEST(s21_floority_test_case_1) {
  char* string1 = "0.12345678912345";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal result = {{0}};
  ck_assert((s21_floor(val1, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("0")));
}
START_TEST(s21_floority_test_case_2) {
  char* string1 = "1.5";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal result = {{0}};
  ck_assert((s21_floor(val1, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("1")));
}
START_TEST(s21_floority_test_case_3) {
  char* string1 = "-1.5";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal result = {{0}};
  ck_assert((s21_floor(val1, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("-2")));
}
START_TEST(s21_floority_test_case_4) {
  char* string1 = "-79228162.50000";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal result = {{0}};
  ck_assert((s21_floor(val1, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("-79228163")));
}
START_TEST(s21_truncateity_test_case_1) {
  char* string1 = "1.54454425431323897189782";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal result = {{0}};
  ck_assert((s21_truncate(val1, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("1")));
}
START_TEST(s21_truncateity_test_case_2) {
  char* string1 = "0.15555";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal result = {{0}};
  ck_assert((s21_truncate(val1, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("0")));
}
START_TEST(s21_truncateity_test_case_3) {
  char* string1 = "99.9999999999999";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal result = {{0}};
  ck_assert((s21_truncate(val1, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("99")));
}
START_TEST(s21_truncateity_test_case_4) {
  char* string1 = "-7";
  s21_decimal val1 = s21_from_string_to_decimal(string1);
  s21_decimal result = {{0}};
  ck_assert((s21_truncate(val1, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("-7")));
}

/// @brief convertors tests
START_TEST(s21_int_to_decimality_test_case_1) {
  int val1 = -1;
  s21_decimal result = {{0}};
  ck_assert((s21_from_int_to_decimal(val1, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("-1")));
}
START_TEST(s21_int_to_decimality_test_case_2) {
  int val1 = INT32_MAX;
  s21_decimal result = {{0}};
  ck_assert((s21_from_int_to_decimal(val1, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("2147483647")));
}
START_TEST(s21_int_to_decimality_test_case_3) {
  int val1 = INT32_MIN;
  s21_decimal result = {{0}};
  ck_assert((s21_from_int_to_decimal(val1, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("-2147483648")));
}
START_TEST(s21_int_to_decimality_test_case_4) {
  int val1 = 10;
  s21_decimal result = {{0}};
  ck_assert((s21_from_int_to_decimal(val1, &result) == OPERATION_IS_OK) &&
            s21_is_equal(result, s21_from_string_to_decimal("10")));
}
START_TEST(s21_decimal_to_intity_test_case_1) {
  int val1 = 0;
  s21_decimal result = s21_from_string_to_decimal("-2147483648");
  ck_assert((s21_from_decimal_to_int(result, &val1) == OPERATION_IS_OK) &&
            (val1 == INT32_MIN));
}
START_TEST(s21_decimal_to_intity_test_case_2) {
  int val1 = 0;
  s21_decimal result = s21_from_string_to_decimal("2147483647");
  ck_assert((s21_from_decimal_to_int(result, &val1) == OPERATION_IS_OK) &&
            (val1 == INT32_MAX));
}
START_TEST(s21_decimal_to_intity_test_case_3) {
  int val1 = 0;
  s21_decimal result = s21_from_string_to_decimal("123.54454545454545");
  ck_assert((s21_from_decimal_to_int(result, &val1) == OPERATION_IS_OK) &&
            (val1 == 123));
}
START_TEST(s21_decimal_to_intity_test_case_4) {
  int val1 = 0;
  s21_decimal result = s21_from_string_to_decimal("-1.5");
  ck_assert((s21_from_decimal_to_int(result, &val1) == OPERATION_IS_OK) &&
            (val1 == -1));
}
START_TEST(s21_string_to_decimality_test_case_1) {
  char* string = "79228162514264337593543950335.313213311313131313131";
  s21_decimal val = s21_from_string_to_decimal(string);
  s21_decimal etalon = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  ck_assert(s21_is_equal(val, etalon));
}
START_TEST(s21_string_to_decimality_test_case_2) {
  char* string = "-79228162514264337593543950335.31321331131313131313";
  s21_decimal val = s21_from_string_to_decimal(string);
  s21_decimal etalon = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, (1 << 31)}};
  ck_assert(s21_is_equal(val, etalon));
}
START_TEST(s21_string_to_decimality_test_case_3) {
  char* string = "1";
  s21_decimal val = s21_from_string_to_decimal(string);
  s21_decimal etalon = {{1, 0, 0, 0}};
  ck_assert(s21_is_equal(val, etalon));
}
START_TEST(s21_float_to_decimality_test_case_1) {
  float src = 1051231;
  s21_decimal val = {{0}};
  ck_assert(s21_from_float_to_decimal(src, &val) == OPERATION_IS_OK &&
            (s21_is_equal(val, s21_from_string_to_decimal("1051231"))));
}
START_TEST(s21_float_to_decimality_test_case_2) {
  float src = 1E-29;
  s21_decimal val = {{0}};
  ck_assert((s21_from_float_to_decimal(src, &val) == CONVERSION_ERROR) &&
            (s21_is_equal(val, s21_from_string_to_decimal("0"))));
}
START_TEST(s21_float_to_decimality_test_case_3) {
  float src = 79E29;
  s21_decimal val = {{0}};
  ck_assert((s21_from_float_to_decimal(src, &val) == CONVERSION_ERROR));
}
START_TEST(s21_float_to_decimality_test_case_4) {
  float src = 12.34552;
  s21_decimal val = {{0}};
  ck_assert(s21_from_float_to_decimal(src, &val) == OPERATION_IS_OK &&
            (s21_is_equal(val, s21_from_string_to_decimal("12.34552"))));
}
START_TEST(s21_decimal_to_floatity_test_case_1) {
  char* src = "1.01234";
  float dst = 0;
  ck_assert(s21_from_decimal_to_float(s21_from_string_to_decimal(src), &dst) ==
                OPERATION_IS_OK &&
            (dst - 1.01234 < 1E-6));
}
START_TEST(s21_decimal_to_floatity_test_case_2) {
  char* src = "1234.567891234";
  float dst = 0;
  ck_assert(s21_from_decimal_to_float(s21_from_string_to_decimal(src), &dst) ==
                OPERATION_IS_OK &&
            (dst - 1234.567891234 < 1E-6));
}
START_TEST(s21_decimal_to_floatity_test_case_3) {
  char* src = "0";
  float dst = 0;
  ck_assert(s21_from_decimal_to_float(s21_from_string_to_decimal(src), &dst) ==
                OPERATION_IS_OK &&
            (dst == (float)0));
}
START_TEST(s21_decimal_to_floatity_test_case_4) {
  char* src = "-2345.123";
  float dst = 0;
  ck_assert(s21_from_decimal_to_float(s21_from_string_to_decimal(src), &dst) ==
                OPERATION_IS_OK &&
            (dst + 2345.123 < 1E-6));
}
Suite* equal_suite(void) {
  Suite* s;
  TCase* equal_case[4];
  int number_of_equality_tests = 4;
  s = suite_create("equality");
  equal_case[0] = tcase_create("case 1:");
  equal_case[1] = tcase_create("case 2:");
  equal_case[2] = tcase_create("case 3:");
  equal_case[3] = tcase_create("case 4:");
  tcase_add_test(equal_case[0], s21_equality_test_case_1);
  tcase_add_test(equal_case[1], s21_equality_test_case_2);
  tcase_add_test(equal_case[2], s21_equality_test_case_3);
  tcase_add_test(equal_case[3], s21_equality_test_case_4);
  for (int i = 0; i < number_of_equality_tests; i++)
    suite_add_tcase(s, equal_case[i]);
  return s;
}
Suite* less_suite(void) {
  Suite* s;
  TCase* less_case[4];
  int number_of_lessity_tests = 4;
  s = suite_create("Lessity");
  less_case[0] = tcase_create("case 1:");
  less_case[1] = tcase_create("case 2:");
  less_case[2] = tcase_create("case 3:");
  less_case[3] = tcase_create("case 4:");
  tcase_add_test(less_case[0], s21_lessity_test_case_1);
  tcase_add_test(less_case[1], s21_lessity_test_case_2);
  tcase_add_test(less_case[2], s21_lessity_test_case_3);
  tcase_add_test(less_case[3], s21_lessity_test_case_4);
  for (int i = 0; i < number_of_lessity_tests; i++)
    suite_add_tcase(s, less_case[i]);
  return s;
}

Suite* add_suite(void) {
  Suite* s;
  TCase* add_case[5];
  int number_of_addity_tests = 5;
  s = suite_create("addity");
  add_case[0] = tcase_create("case 1:");
  add_case[1] = tcase_create("case 2:");
  add_case[2] = tcase_create("case 3:");
  add_case[3] = tcase_create("case 4:");
  add_case[4] = tcase_create("case 5:");
  tcase_add_test(add_case[0], s21_addity_test_case_1);
  tcase_add_test(add_case[1], s21_addity_test_case_2);
  tcase_add_test(add_case[2], s21_addity_test_case_3);
  tcase_add_test(add_case[3], s21_addity_test_case_4);
  tcase_add_test(add_case[3], s21_addity_test_case_5);
  for (int i = 0; i < number_of_addity_tests; i++)
    suite_add_tcase(s, add_case[i]);
  return s;
}

Suite* sub_suite(void) {
  Suite* s;
  TCase* sub_case[5];
  int number_of_subity_tests = 5;
  s = suite_create("subity");
  sub_case[0] = tcase_create("case 1:");
  sub_case[1] = tcase_create("case 2:");
  sub_case[2] = tcase_create("case 3:");
  sub_case[3] = tcase_create("case 4:");
  sub_case[4] = tcase_create("case 5:");
  tcase_add_test(sub_case[0], s21_subity_test_case_1);
  tcase_add_test(sub_case[1], s21_subity_test_case_2);
  tcase_add_test(sub_case[2], s21_subity_test_case_3);
  tcase_add_test(sub_case[3], s21_subity_test_case_4);
  tcase_add_test(sub_case[4], s21_subity_test_case_5);
  for (int i = 0; i < number_of_subity_tests; i++)
    suite_add_tcase(s, sub_case[i]);
  return s;
}

Suite* string_to_decimal_suite(void) {
  Suite* s;
  TCase* string_to_decimal_case[4];
  int number_of_string_to_decimality_tests = 4;
  s = suite_create("string_to_decimality");
  string_to_decimal_case[0] = tcase_create("case 1:");
  string_to_decimal_case[1] = tcase_create("case 2:");
  string_to_decimal_case[2] = tcase_create("case 3:");
  string_to_decimal_case[3] = tcase_create("case 4:");
  tcase_add_test(string_to_decimal_case[0],
                 s21_string_to_decimality_test_case_1);
  tcase_add_test(string_to_decimal_case[1],
                 s21_string_to_decimality_test_case_2);
  tcase_add_test(string_to_decimal_case[2],
                 s21_string_to_decimality_test_case_3);
  for (int i = 0; i < number_of_string_to_decimality_tests; i++)
    suite_add_tcase(s, string_to_decimal_case[i]);
  return s;
}

Suite* mul_suite(void) {
  Suite* s;
  TCase* mul_case[4];
  int number_of_mulity_tests = 4;
  s = suite_create("mulity");
  mul_case[0] = tcase_create("case 1:");
  mul_case[1] = tcase_create("case 2:");
  mul_case[2] = tcase_create("case 3:");
  mul_case[3] = tcase_create("case 4:");
  tcase_add_test(mul_case[0], s21_mulity_test_case_1);
  tcase_add_test(mul_case[1], s21_mulity_test_case_2);
  tcase_add_test(mul_case[2], s21_mulity_test_case_3);
  tcase_add_test(mul_case[3], s21_mulity_test_case_4);
  for (int i = 0; i < number_of_mulity_tests; i++)
    suite_add_tcase(s, mul_case[i]);
  return s;
}

Suite* round_suite(void) {
  Suite* s;
  TCase* round_case[4];
  int number_of_roundity_tests = 4;
  s = suite_create("roundity");
  round_case[0] = tcase_create("case 1:");
  round_case[1] = tcase_create("case 2:");
  round_case[2] = tcase_create("case 3:");
  round_case[3] = tcase_create("case 4:");
  tcase_add_test(round_case[0], s21_roundity_test_case_1);
  tcase_add_test(round_case[1], s21_roundity_test_case_2);
  tcase_add_test(round_case[2], s21_roundity_test_case_3);
  tcase_add_test(round_case[3], s21_roundity_test_case_4);
  for (int i = 0; i < number_of_roundity_tests; i++)
    suite_add_tcase(s, round_case[i]);
  return s;
}

Suite* floor_suite(void) {
  Suite* s;
  TCase* floor_case[4];
  int number_of_floority_tests = 4;
  s = suite_create("floority");
  floor_case[0] = tcase_create("case 1:");
  floor_case[1] = tcase_create("case 2:");
  floor_case[2] = tcase_create("case 3:");
  floor_case[3] = tcase_create("case 4:");
  tcase_add_test(floor_case[0], s21_floority_test_case_1);
  tcase_add_test(floor_case[1], s21_floority_test_case_2);
  tcase_add_test(floor_case[2], s21_floority_test_case_3);
  tcase_add_test(floor_case[3], s21_floority_test_case_4);
  for (int i = 0; i < number_of_floority_tests; i++)
    suite_add_tcase(s, floor_case[i]);
  return s;
}

Suite* truncate_suite(void) {
  Suite* s;
  TCase* truncate_case[4];
  int number_of_truncateity_tests = 4;
  s = suite_create("truncateity");
  truncate_case[0] = tcase_create("case 1:");
  truncate_case[1] = tcase_create("case 2:");
  truncate_case[2] = tcase_create("case 3:");
  truncate_case[3] = tcase_create("case 4:");
  tcase_add_test(truncate_case[0], s21_truncateity_test_case_1);
  tcase_add_test(truncate_case[1], s21_truncateity_test_case_2);
  tcase_add_test(truncate_case[2], s21_truncateity_test_case_3);
  tcase_add_test(truncate_case[3], s21_truncateity_test_case_4);
  for (int i = 0; i < number_of_truncateity_tests; i++)
    suite_add_tcase(s, truncate_case[i]);
  return s;
}
Suite* int_to_decimal_suite(void) {
  Suite* s;
  TCase* int_to_decimal_case[4];
  int number_of_int_to_decimality_tests = 4;
  s = suite_create("int_to_decimality");
  int_to_decimal_case[0] = tcase_create("case 1:");
  int_to_decimal_case[1] = tcase_create("case 2:");
  int_to_decimal_case[2] = tcase_create("case 3:");
  int_to_decimal_case[3] = tcase_create("case 4:");
  tcase_add_test(int_to_decimal_case[0], s21_int_to_decimality_test_case_1);
  tcase_add_test(int_to_decimal_case[1], s21_int_to_decimality_test_case_2);
  tcase_add_test(int_to_decimal_case[2], s21_int_to_decimality_test_case_3);
  tcase_add_test(int_to_decimal_case[3], s21_int_to_decimality_test_case_4);
  for (int i = 0; i < number_of_int_to_decimality_tests; i++)
    suite_add_tcase(s, int_to_decimal_case[i]);
  return s;
}
Suite* decimal_to_int_suite(void) {
  Suite* s;
  TCase* decimal_to_int_case[4];
  int number_of_decimal_to_intity_tests = 4;
  s = suite_create("decimal_to_intity");
  decimal_to_int_case[0] = tcase_create("case 1:");
  decimal_to_int_case[1] = tcase_create("case 2:");
  decimal_to_int_case[2] = tcase_create("case 3:");
  decimal_to_int_case[3] = tcase_create("case 4:");
  tcase_add_test(decimal_to_int_case[0], s21_decimal_to_intity_test_case_1);
  tcase_add_test(decimal_to_int_case[1], s21_decimal_to_intity_test_case_2);
  tcase_add_test(decimal_to_int_case[2], s21_decimal_to_intity_test_case_3);
  tcase_add_test(decimal_to_int_case[3], s21_decimal_to_intity_test_case_4);
  for (int i = 0; i < number_of_decimal_to_intity_tests; i++)
    suite_add_tcase(s, decimal_to_int_case[i]);
  return s;
}
Suite* float_to_decimal_suite(void) {
  Suite* s;
  TCase* float_to_decimal_case[4];
  int number_of_float_to_decimality_tests = 4;
  s = suite_create("float_to_decimality");
  float_to_decimal_case[0] = tcase_create("case 1:");
  float_to_decimal_case[1] = tcase_create("case 2:");
  float_to_decimal_case[2] = tcase_create("case 3:");
  float_to_decimal_case[3] = tcase_create("case 4:");
  tcase_add_test(float_to_decimal_case[0], s21_float_to_decimality_test_case_1);
  tcase_add_test(float_to_decimal_case[1], s21_float_to_decimality_test_case_2);
  tcase_add_test(float_to_decimal_case[2], s21_float_to_decimality_test_case_3);
  tcase_add_test(float_to_decimal_case[3], s21_float_to_decimality_test_case_4);
  for (int i = 0; i < number_of_float_to_decimality_tests; i++)
    suite_add_tcase(s, float_to_decimal_case[i]);
  return s;
}
Suite* div_suite(void) {
  Suite* s;
  TCase* div_case[4];
  int number_of_divity_tests = 4;
  s = suite_create("divity");
  div_case[0] = tcase_create("case 1:");
  div_case[1] = tcase_create("case 2:");
  div_case[2] = tcase_create("case 3:");
  div_case[3] = tcase_create("case 4:");
  tcase_add_test(div_case[0], s21_divity_test_case_1);
  tcase_add_test(div_case[1], s21_divity_test_case_2);
  tcase_add_test(div_case[2], s21_divity_test_case_3);
  tcase_add_test(div_case[3], s21_divity_test_case_4);
  for (int i = 0; i < number_of_divity_tests; i++)
    suite_add_tcase(s, div_case[i]);
  return s;
}

Suite* decimal_to_float_suite(void) {
  Suite* s;
  TCase* decimal_to_float_case[4];
  int number_of_decimal_to_floatity_tests = 4;
  s = suite_create("decimal_to_floatity");
  decimal_to_float_case[0] = tcase_create("case 1:");
  decimal_to_float_case[1] = tcase_create("case 2:");
  decimal_to_float_case[2] = tcase_create("case 3:");
  decimal_to_float_case[3] = tcase_create("case 4:");
  tcase_add_test(decimal_to_float_case[0], s21_decimal_to_floatity_test_case_1);
  tcase_add_test(decimal_to_float_case[1], s21_decimal_to_floatity_test_case_2);
  tcase_add_test(decimal_to_float_case[2], s21_decimal_to_floatity_test_case_3);
  tcase_add_test(decimal_to_float_case[3], s21_decimal_to_floatity_test_case_4);
  for (int i = 0; i < number_of_decimal_to_floatity_tests; i++)
    suite_add_tcase(s, decimal_to_float_case[i]);
  return s;
}
int main(void) {
  int number_failed = 0;
  int number_of_runners = 14;
  Suite** s = (Suite**)malloc(sizeof(Suite*) * number_of_runners);
  ;
  SRunner** sr = (SRunner**)malloc(sizeof(SRunner*) * number_of_runners);
  s[0] = equal_suite();
  s[1] = less_suite();
  s[2] = add_suite();
  s[3] = sub_suite();
  s[4] = string_to_decimal_suite();
  s[5] = mul_suite();
  s[6] = round_suite();
  s[7] = floor_suite();
  s[8] = truncate_suite();
  s[9] = int_to_decimal_suite();
  s[10] = decimal_to_int_suite();
  s[11] = float_to_decimal_suite();
  s[12] = div_suite();
  s[13] = decimal_to_float_suite();
  for (int i = 0; i < number_of_runners; i++) {
    sr[i] = srunner_create(s[i]);
    srunner_set_fork_status(sr[i], CK_NOFORK);
    srunner_run_all(sr[i], CK_NORMAL);
    number_failed += srunner_ntests_failed(sr[i]);
    srunner_free(sr[i]);
  }
  free(s);
  free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
