#include <check.h>
#include <locale.h>

#include "../s21_string.h"
#include "test_memfunc.h"
#include "test_special.h"
#include "test_sprintf.h"
#include "test_strfunc.h"

int main(void) {
  setlocale(LC_CTYPE, "");

  int failed = 0;
  Suite *result[] = {
      s21_suite_memchr(),   s21_suite_memcmp(),   s21_suite_memcpy(),
      s21_suite_memset(),   s21_suite_strncat(),  s21_suite_strchr(),
      s21_suite_strncmp(),  s21_suite_strncpy(),  s21_suite_strcspn(),
      s21_suite_strerror(), s21_suite_strlen(),   s21_suite_strpbrk(),
      s21_suite_strrchr(),  s21_suite_strstr(),   s21_suite_strtok(),
      s21_suite_to_upper(), s21_suite_to_lower(), s21_suite_insert(),
      s21_suite_trim(),     s21_suite_sprintf(),  NULL};

  for (int i = 0; result[i] != NULL; i++) {
    SRunner *runner = srunner_create(result[i]);
    srunner_run_all(runner, CK_NORMAL);
    failed |= srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return (failed == 0) ? 0 : CK_FAILURE;
}