#include "test_strfunc.h"

#include <check.h>

#include "../s21_string.h"

/******************************************************************************/
/*                                  strncat                                   */
/******************************************************************************/

START_TEST(test_strncat_1) {
  char dest_1[20] = "val: ";
  char dest_2[20] = "val: ";
  ck_assert_str_eq(strncat(dest_1, "21", 0), s21_strncat(dest_2, "21", 0));
}
END_TEST

START_TEST(test_strncat_2) {
  char dest_1[20] = "val: ";
  char dest_2[20] = "val: ";
  ck_assert_str_eq(strncat(dest_1, "21", 3), s21_strncat(dest_2, "21", 3));
}
END_TEST

START_TEST(test_strncat_3) {
  char dest_1[20] = "val: \0   ";
  char dest_2[20] = "val: \0   ";
  ck_assert_str_eq(strncat(dest_1, "21", 1), s21_strncat(dest_2, "21", 1));
}
END_TEST

Suite *s21_suite_strncat(void) {
  Suite *suite = suite_create("s21_strncat");
  TCase *tc = tcase_create("s21_strncat_tc");

  tcase_add_test(tc, test_strncat_1);
  tcase_add_test(tc, test_strncat_2);
  tcase_add_test(tc, test_strncat_3);

  suite_add_tcase(suite, tc);

  return suite;
}

/******************************************************************************/
/*                                   strchr                                   */
/******************************************************************************/

START_TEST(test_strchr_1) {
  const char src[] = "0123456789";
  ck_assert_ptr_eq(strchr(src, '8'), s21_strchr(src, '8'));
}
END_TEST

START_TEST(test_strchr_2) {
  const char src[] = "0123456789";
  ck_assert_ptr_eq(strchr(src, 'a'), s21_strchr(src, 'a'));
}
END_TEST

START_TEST(test_strchr_3) {
  const char src[] = "0123456789";
  ck_assert_ptr_eq(strchr(src, '\0'), s21_strchr(src, '\0'));
}
END_TEST

START_TEST(test_strchr_4) {
  const char src[] = "";
  ck_assert_ptr_eq(strchr(src, '1'), s21_strchr(src, '1'));
}
END_TEST

Suite *s21_suite_strchr(void) {
  Suite *suite = suite_create("s21_strchr");
  TCase *tc = tcase_create("s21_strchr_tc");

  tcase_add_test(tc, test_strchr_1);
  tcase_add_test(tc, test_strchr_2);
  tcase_add_test(tc, test_strchr_3);
  tcase_add_test(tc, test_strchr_4);

  suite_add_tcase(suite, tc);

  return suite;
}

/******************************************************************************/
/*                                  strncmp                                   */
/******************************************************************************/

START_TEST(test_strncmp_1) {
  ck_assert_int_eq(s21_strncmp("abcdefg", "abcdefg", 8),
                   strncmp("abcdefg", "abcdefg", 8));
}
END_TEST

START_TEST(test_strncmp_2) {
  ck_assert_int_eq(strncmp("abcdefg", "abcdefa", 8),
                   s21_strncmp("abcdefg", "abcdefa", 8));
}
END_TEST

START_TEST(test_strncmp_3) {
  ck_assert_int_eq(strncmp("abcdefa", "abcdefg", 8),
                   s21_strncmp("abcdefa", "abcdefg", 8));
}
END_TEST

START_TEST(test_strncmp_4) {
  ck_assert_int_eq(strncmp("abcdefg", "abc", 8),
                   s21_strncmp("abcdefg", "abc", 8));
}
END_TEST

START_TEST(test_strncmp_5) {
  ck_assert_int_eq(s21_strncmp("abc", "abcdefg", 3),
                   strncmp("abc", "abcdefg", 3));
}
END_TEST

START_TEST(test_strncmp_6) {
  ck_assert_int_eq(s21_strncmp(" ", "", 0), strncmp(" ", "", 0));
}
END_TEST

Suite *s21_suite_strncmp(void) {
  Suite *suite = suite_create("s21_strncmp");
  TCase *tc = tcase_create("s21_strncmp_tc");

  tcase_add_test(tc, test_strncmp_1);
  tcase_add_test(tc, test_strncmp_2);
  tcase_add_test(tc, test_strncmp_3);
  tcase_add_test(tc, test_strncmp_4);
  tcase_add_test(tc, test_strncmp_5);
  tcase_add_test(tc, test_strncmp_6);

  suite_add_tcase(suite, tc);

  return suite;
}

/******************************************************************************/
/*                                  strncpy                                   */
/******************************************************************************/

START_TEST(test_strncpy_1) {
  char dest_1[20] = "                   ";
  char dest_2[20] = "                   ";
  ck_assert_str_eq(strncpy(dest_1, "abcde", 10),
                   s21_strncpy(dest_2, "abcde", 10));
  ck_assert_int_eq(dest_1[15], dest_2[15]);
}
END_TEST

START_TEST(test_strncpy_2) {
  // char dest_1[20] = "                   ";
  char dest_2[20] = "                   ";
  // strncpy(dest_1, "abcde", 3),
  ck_assert_str_eq("abc                ", s21_strncpy(dest_2, "abcde", 3));
}
END_TEST

START_TEST(test_strncpy_3) {
  char dest_1[20] = "                   ";
  char dest_2[20] = "                   ";
  ck_assert_str_eq(strncpy(dest_1, "", 10), s21_strncpy(dest_2, "", 10));
  ck_assert_int_eq(dest_1[15], dest_2[15]);
}
END_TEST

START_TEST(test_strncpy_4) {
  char dest_1[20] = "   \0               ";
  char dest_2[20] = "   \0               ";
  ck_assert_str_eq(strncpy(dest_1, "abcdefgh", 20),
                   s21_strncpy(dest_2, "abcdefgh", 20));
  ck_assert_int_eq(dest_1[15], dest_2[15]);
}
END_TEST

START_TEST(test_strncpy_5) {
  // char dest_1[20] = "   \0               ";
  char dest_2[20] = "   \0               ";
  // strncpy(dest_1, "abcd", 4)
  ck_assert_str_eq("abcd               ", s21_strncpy(dest_2, "abcd", 4));
  ck_assert_int_eq(' ', dest_2[15]);
}
END_TEST

Suite *s21_suite_strncpy(void) {
  Suite *suite = suite_create("s21_strncpy");
  TCase *tc = tcase_create("s21_strncpy_tc");

  tcase_add_test(tc, test_strncpy_1);
  tcase_add_test(tc, test_strncpy_2);
  tcase_add_test(tc, test_strncpy_3);
  tcase_add_test(tc, test_strncpy_4);
  tcase_add_test(tc, test_strncpy_5);

  suite_add_tcase(suite, tc);

  return suite;
}

/******************************************************************************/
/*                                  strcspn                                   */
/******************************************************************************/

// TODO

START_TEST(test_strcspn_1) {
  const char test_1[] = "", test_2[] = "4567";
  ck_assert_int_eq(strcspn(test_1, test_2), s21_strcspn(test_1, test_2));
}
END_TEST

START_TEST(test_strcspn_2) {
  const char test_1[] = "1234", test_2[] = "4567";
  ck_assert_int_eq(strcspn(test_1, test_2), s21_strcspn(test_1, test_2));
}
END_TEST

START_TEST(test_strcspn_3) {
  const char test_1[] = "123", test_2[] = "14567";
  ck_assert_int_eq(s21_strcspn(test_1, test_2), strcspn(test_1, test_2));
}
END_TEST

START_TEST(test_strcspn_4) {
  const char test_1[] = "1236", test_2[] = "4567";
  ck_assert_int_eq(s21_strcspn(test_1, test_2), strcspn(test_1, test_2));
}
END_TEST

START_TEST(test_strcspn_5) {
  const char test_1[] = "h", test_2[] = "45671hjd";
  ck_assert_int_eq(s21_strcspn(test_1, test_2), strcspn(test_1, test_2));
}
END_TEST

START_TEST(test_strcspn_6) {
  const char test_1[] = "123", test_2[] = "45671";
  ck_assert_int_eq(s21_strcspn(test_1, test_2), strcspn(test_1, test_2));
}
END_TEST

Suite *s21_suite_strcspn(void) {
  Suite *suite = suite_create("s21_strcspn");
  TCase *tc = tcase_create("s21_strcspn_tc");

  tcase_add_test(tc, test_strcspn_1);
  tcase_add_test(tc, test_strcspn_2);
  tcase_add_test(tc, test_strcspn_3);
  tcase_add_test(tc, test_strcspn_4);
  tcase_add_test(tc, test_strcspn_5);
  tcase_add_test(tc, test_strcspn_6);

  suite_add_tcase(suite, tc);

  return suite;
}

/******************************************************************************/
/*                                  strerror                                  */
/******************************************************************************/

START_TEST(test_strerror_1) { ck_assert_str_eq(strerror(0), s21_strerror(0)); }
END_TEST

START_TEST(test_strerror_2) {
  ck_assert_str_eq(strerror(2), s21_strerror(2));
  ck_assert_str_eq(strerror(1), s21_strerror(1));
}
END_TEST

START_TEST(test_strerror_3) {
  ck_assert_str_eq(strerror(23), s21_strerror(23));
}
END_TEST

START_TEST(test_strerror_4) {
  ck_assert_str_eq(strerror(106), s21_strerror(106));
}
END_TEST

START_TEST(test_strerror_5) {
  ck_assert_str_eq(strerror(107), s21_strerror(107));
}
END_TEST

START_TEST(test_strerror_6) {
  ck_assert_str_eq(strerror(-123), s21_strerror(-123));
}
END_TEST

START_TEST(test_strerror_7) {
  ck_assert_str_eq(strerror(133), s21_strerror(133));
}
END_TEST

START_TEST(test_strerror_8) {
  ck_assert_str_eq(strerror(134), s21_strerror(134));
}
END_TEST

START_TEST(test_strerror_9) {
  ck_assert_str_eq(strerror(324), s21_strerror(324));
}
END_TEST

Suite *s21_suite_strerror(void) {
  Suite *suite = suite_create("s21_strerror");
  TCase *tc = tcase_create("s21_strerror_tc");

  tcase_add_test(tc, test_strerror_1);
  tcase_add_test(tc, test_strerror_2);
  tcase_add_test(tc, test_strerror_3);
  tcase_add_test(tc, test_strerror_4);
  tcase_add_test(tc, test_strerror_5);
  tcase_add_test(tc, test_strerror_6);
  tcase_add_test(tc, test_strerror_7);
  tcase_add_test(tc, test_strerror_8);
  tcase_add_test(tc, test_strerror_9);

  suite_add_tcase(suite, tc);

  return suite;
}

/******************************************************************************/
/*                                   strlen                                   */
/******************************************************************************/

START_TEST(test_strlen_1) { ck_assert_int_eq(strlen("a"), s21_strlen("a")); }
END_TEST

START_TEST(test_strlen_2) {
  ck_assert_int_eq(strlen("aaaaaaaaaaaaaa"), s21_strlen("aaaaaaaaaaaaaa"));
}
END_TEST

START_TEST(test_strlen_3) { ck_assert_int_eq(strlen(""), s21_strlen("")); }
END_TEST

START_TEST(test_strlen_4) {
  ck_assert_int_eq(strlen("\0hiddenspace"), s21_strlen("\0hiddenspc"));
}
END_TEST

Suite *s21_suite_strlen(void) {
  Suite *suite = suite_create("s21_strlen");
  TCase *tc = tcase_create("s21_strlen_tc");

  tcase_add_test(tc, test_strlen_1);
  tcase_add_test(tc, test_strlen_2);
  tcase_add_test(tc, test_strlen_3);
  tcase_add_test(tc, test_strlen_4);

  suite_add_tcase(suite, tc);

  return suite;
}

/******************************************************************************/
/*                                  strpbrk                                   */
/******************************************************************************/

START_TEST(test_strpbrk_1) {
  const char src[] = "The 3 men and 2 boys ate 5 pigs\n";
  ck_assert_ptr_eq(strpbrk(src, "0123456789"), s21_strpbrk(src, "0123456789"));
}
END_TEST

START_TEST(test_strpbrk_2) {
  const char src[] = "The 3 men and 2 boys ate 5 pigs\n";
  ck_assert_ptr_eq(strpbrk(src, "z"), s21_strpbrk(src, "z"));
}
END_TEST

Suite *s21_suite_strpbrk(void) {
  Suite *suite = suite_create("s21_strpbrk");
  TCase *tc = tcase_create("s21_strpbrk_tc");

  tcase_add_test(tc, test_strpbrk_1);
  tcase_add_test(tc, test_strpbrk_2);

  suite_add_tcase(suite, tc);

  return suite;
}

/******************************************************************************/
/*                                  strrchr                                   */
/******************************************************************************/

START_TEST(test_strrchr_1) {
  const char src[] = "3 3 3 ";
  ck_assert_ptr_eq(strrchr(src, '3'), s21_strrchr(src, '3'));
}
END_TEST

START_TEST(test_strrchr_2) {
  const char src[] = "3 3 3 ";
  ck_assert_ptr_eq(strrchr(src, 'a'), s21_strrchr(src, 'a'));
}
END_TEST

START_TEST(test_strrchr_3) {
  const char src[] = "3 3 3 ";
  ck_assert_ptr_eq(strrchr(src, '\0'), s21_strrchr(src, '\0'));
}
END_TEST

Suite *s21_suite_strrchr(void) {
  Suite *suite = suite_create("s21_strrchr");
  TCase *tc = tcase_create("s21_strrchr_tc");

  tcase_add_test(tc, test_strrchr_1);
  tcase_add_test(tc, test_strrchr_2);
  tcase_add_test(tc, test_strrchr_3);

  suite_add_tcase(suite, tc);

  return suite;
}

/******************************************************************************/
/*                                   strstr                                   */
/******************************************************************************/

START_TEST(test_strstr_1) {
  const char haystack[] = "Hello, world!";
  ck_assert_ptr_eq(strstr(haystack, "world"), s21_strstr(haystack, "world"));
}
END_TEST

START_TEST(test_strstr_2) {
  const char haystack[] = "Hello, world! w.o.r.l.d.";
  ck_assert_ptr_eq(strstr(haystack, "world"), s21_strstr(haystack, "world"));
}
END_TEST

START_TEST(test_strstr_3) {
  const char haystack[] = "Hello, w.o.r.l.d.";
  ck_assert_ptr_eq(strstr(haystack, "w.o"), s21_strstr(haystack, "w.o"));
}
END_TEST

START_TEST(test_strstr_4) {
  const char haystack[] = "123456789abc";
  ck_assert_ptr_eq(strstr(haystack, "9a"), s21_strstr(haystack, "9a"));
}
END_TEST

START_TEST(test_strstr_5) {
  const char haystack[] = "123456789abc";
  ck_assert_ptr_eq(strstr(haystack, "123456789abc"),
                   s21_strstr(haystack, "123456789abc"));
}
END_TEST

START_TEST(test_strstr_6) {
  const char haystack[] = "123456789abc";
  ck_assert_ptr_eq(strstr(haystack, "1"), s21_strstr(haystack, "1"));
}
END_TEST

START_TEST(test_strstr_7) {
  const char haystack[] = "123456789abc";
  ck_assert_ptr_eq(strstr(haystack, "c"), s21_strstr(haystack, "c"));
}
END_TEST

START_TEST(test_strstr_8) {
  const char haystack[] = "123456789abc";
  ck_assert_ptr_eq(strstr(haystack, ""), s21_strstr(haystack, ""));
}
END_TEST

Suite *s21_suite_strstr(void) {
  Suite *suite = suite_create("s21_strstr");
  TCase *tc = tcase_create("s21_strstr_tc");

  tcase_add_test(tc, test_strstr_1);
  tcase_add_test(tc, test_strstr_2);
  tcase_add_test(tc, test_strstr_3);
  tcase_add_test(tc, test_strstr_4);
  tcase_add_test(tc, test_strstr_5);
  tcase_add_test(tc, test_strstr_6);
  tcase_add_test(tc, test_strstr_7);
  tcase_add_test(tc, test_strstr_8);

  suite_add_tcase(suite, tc);

  return suite;
}

/******************************************************************************/
/*                                   strtok                                   */
/******************************************************************************/

START_TEST(test_strtok_1) { ck_assert_ptr_null(s21_strtok(NULL, ",./")); }
END_TEST

START_TEST(test_strtok_2) {
  char str_1[] = "/dfwwrwhrthg";
  char str_2[] = "/dfwwrwhrthg";
  const char *delim = ",./";
  char *ptr_1 = strtok(str_1, delim);
  char *ptr_2 = s21_strtok(str_2, delim);
  while (ptr_1 != NULL && ptr_2 != NULL) {
    ck_assert_str_eq(ptr_1, ptr_2);
    ptr_1 = strtok(NULL, delim);
    ptr_2 = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_null(ptr_1);
  ck_assert_ptr_null(ptr_2);
}
END_TEST

START_TEST(test_strtok_3) {
  char str_1[] = "dfwwrwhrthg";
  char str_2[] = "dfwwrwhrthg";
  const char *delim = ",./";
  char *ptr_1 = strtok(str_1, delim);
  char *ptr_2 = s21_strtok(str_2, delim);
  while (ptr_1 != NULL && ptr_2 != NULL) {
    ck_assert_str_eq(ptr_1, ptr_2);
    ptr_1 = strtok(NULL, delim);
    ptr_2 = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_null(ptr_1);
  ck_assert_ptr_null(ptr_2);
}
END_TEST

START_TEST(test_strtok_4) {
  char str_1[] = "dfwwrwhrthg...";
  char str_2[] = "dfwwrwhrthg...";
  const char *delim = ",./";
  char *ptr_1 = strtok(str_1, delim);
  char *ptr_2 = s21_strtok(str_2, delim);
  while (ptr_1 != NULL && ptr_2 != NULL) {
    ck_assert_str_eq(ptr_1, ptr_2);
    ptr_1 = strtok(NULL, delim);
    ptr_2 = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_null(ptr_1);
  ck_assert_ptr_null(ptr_2);
}
END_TEST

START_TEST(test_strtok_5) {
  char str_1[] = "d.fw.wrw,,hrth//g";
  char str_2[] = "d.fw.wrw,,hrth//g";
  const char *delim = ",./h";
  char *ptr_1 = strtok(str_1, delim);
  char *ptr_2 = s21_strtok(str_2, delim);
  while (ptr_1 != NULL && ptr_2 != NULL) {
    ck_assert_str_eq(ptr_1, ptr_2);
    ptr_1 = strtok(NULL, delim);
    ptr_2 = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_null(ptr_1);
  ck_assert_ptr_null(ptr_2);
}
END_TEST

START_TEST(test_strtok_6) {
  char str_1[] = "d,fwwrwhr123th.g";
  char str_2[] = "d,fwwrwhr123th.g";
  const char *delim = ",./123";
  char *ptr_1 = strtok(str_1, delim);
  char *ptr_2 = s21_strtok(str_2, delim);
  while (ptr_1 != NULL && ptr_2 != NULL) {
    ck_assert_str_eq(ptr_1, ptr_2);
    ptr_1 = strtok(NULL, delim);
    ptr_2 = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_null(ptr_1);
  ck_assert_ptr_null(ptr_2);
}
END_TEST

START_TEST(test_strtok_7) {
  char str_1[] = "";
  char str_2[] = "";
  const char *delim = ",./123";
  char *ptr_1 = strtok(str_1, delim);
  char *ptr_2 = s21_strtok(str_2, delim);
  ck_assert_ptr_null(ptr_1);
  ck_assert_ptr_null(ptr_2);
}
END_TEST

START_TEST(test_strtok_8) {
  char str_1[] = "d,fwwrwhr123th.g";
  char str_2[] = "d,fwwrwhr123th.g";
  const char *delim = "";
  char *ptr_1 = strtok(str_1, delim);
  char *ptr_2 = s21_strtok(str_2, delim);
  while (ptr_1 != NULL && ptr_2 != NULL) {
    ck_assert_str_eq(ptr_1, ptr_2);
    ptr_1 = strtok(NULL, delim);
    ptr_2 = s21_strtok(NULL, delim);
  }
  ck_assert_ptr_null(ptr_1);
  ck_assert_ptr_null(ptr_2);
}
END_TEST

Suite *s21_suite_strtok(void) {
  Suite *suite = suite_create("s21_strtok");
  TCase *tc = tcase_create("s21_strtok_tc");

  tcase_add_test(tc, test_strtok_1);
  tcase_add_test(tc, test_strtok_2);
  tcase_add_test(tc, test_strtok_3);
  tcase_add_test(tc, test_strtok_4);
  tcase_add_test(tc, test_strtok_5);
  tcase_add_test(tc, test_strtok_6);
  tcase_add_test(tc, test_strtok_7);
  tcase_add_test(tc, test_strtok_8);

  suite_add_tcase(suite, tc);

  return suite;
}
