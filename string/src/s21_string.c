#include "s21_string.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "s21_sprintf_internal.h"
#include "s21_stringerror.h"

void *s21_memchr(const void *str, int c, size_t n) {
  void *ptr = NULL;
  for (size_t i = 0; ptr == NULL && i < n; ++i)
    if (((const char *)str)[i] == c) ptr = (void *)((const char *)str + i);
  return ptr;
}

int s21_memcmp(const void *str1, const void *str2, size_t n) {
  int mem = 0;
  for (size_t i = 0; mem == 0 && i < n; i++)
    mem = ((const char *)str1)[i] - ((const char *)str2)[i];
  if (mem < 0) mem = -1;
  if (mem > 0) mem = 1;
  return mem;
}

void *s21_memcpy(void *dest, const void *src, size_t n) {
  for (size_t i = 0; i < n; i++)
    ((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
  return dest;
}

void *s21_memset(void *str, int c, size_t n) {
  for (size_t i = 0; i < n; i++) *((unsigned char *)str + i) = c;
  return str;
}

char *s21_strncat(char *dest, const char *src, size_t n) {
  size_t len = s21_strlen(dest);
  s21_memcpy(dest + len, src, n);
  dest[len + n] = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *ptr = NULL;
  size_t i = 0;
  do
    if ((unsigned char)str[i] == c) ptr = (char *)(str + i);
  while (ptr == NULL && str[i++] != '\0');
  return ptr;
}

int s21_strncmp(const char *str1, const char *str2, size_t n) {
  int result = 0;
  for (size_t i = 0; result == 0 && i < n; i++) result = str1[i] - str2[i];
  return result;
}

char *s21_strncpy(char *dest, const char *src, size_t n) {
  size_t src_len = s21_strlen(src);
  for (size_t i = 0; i < n; i++) dest[i] = i < src_len ? src[i] : '\0';
  return dest;
}

size_t s21_strcspn(const char *str1, const char *str2) {
  size_t count = 0;
  bool out = false;
  while (!out && str1[count] != '\0') {
    for (size_t i = 0; !out && str2[i] != '\0'; ++i)
      out = str1[count] == str2[i];
    if (!out) count++;
  }
  return count;
}

char *s21_strerror(int errnum) {
  static char error_string[100] = {0};
  if (errnum < LIST_ERRORS_LENGTH && errnum >= 0) {
    const char *errors[] = LIST_ERRORS;
    s21_strncpy(error_string, errors[errnum], s21_strlen(errors[errnum]) + 1);
  } else
    s21_sprintf(error_string, LIST_ERRORS_FORMAT, errnum);
  return error_string;
}

size_t s21_strlen(const char *str) {
  size_t len = 0;
  while (str[len] != '\0') len++;
  return len;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *ptr = NULL;
  for (size_t i = 0; ptr == NULL && str1[i] != '\0'; i++)
    for (size_t j = 0; ptr == NULL && str2[j] != '\0'; j++)
      if (str1[i] == str2[j]) ptr = (char *)(str1 + i);
  return ptr;
}

char *s21_strrchr(const char *str, int c) {
  if (c == '\0') return s21_strchr(str, c);

  char *ptr = NULL;
  for (size_t i = 0; str[i] != '\0'; ++i)
    if ((unsigned char)str[i] == c) ptr = (char *)(str + i);

  return ptr;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = NULL;
  for (; result == NULL && *haystack != '\0'; ++haystack) {
    int i = 0;
    while (needle[i] != '\0' && haystack[i] != '\0' && haystack[i] == needle[i])
      i++;
    if (needle[i] == '\0') result = (char *)haystack;
  }
  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *token = NULL;
  static char *end_str = NULL;
  if (str != NULL && *str != '\0') {
    end_str = str + s21_strlen(str) + 1;
    while (*str != '\0') {
      size_t index = s21_strcspn(str, delim);
      str[index] = '\0';
      if (token == NULL) token = str;
      str = str + index + 1;
    }
    if (*token == '\0') token++;
  } else if (token != end_str && token != NULL) {
    while (*token != '\0') token++;
    while (*token == '\0' && token != end_str) token++;
  }
  if (token == end_str) token = NULL;
  return token;
}

void *s21_to_upper(const char *str) {
  if (str == NULL) return NULL;
  size_t str_len = s21_strlen(str);
  char *dest = calloc(str_len + 1, sizeof(char));
  for (size_t i = 0; str[i] != '\0'; i++)
    dest[i] = str[i] >= 'a' && str[i] <= 'z' ? str[i] - 32 : str[i];
  dest[str_len] = '\0';
  return (void *)dest;
}

void *s21_to_lower(const char *str) {
  if (str == NULL) return NULL;
  size_t str_len = s21_strlen(str);
  char *dest = malloc((str_len + 1) * sizeof(char));
  for (size_t i = 0; str[i] != '\0'; i++)
    dest[i] = str[i] >= 'A' && str[i] <= 'Z' ? str[i] + 32 : str[i];
  dest[str_len] = '\0';
  return (void *)dest;
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
  if (src == NULL || str == NULL) return NULL;
  size_t src_len = s21_strlen(src), str_len = s21_strlen(str);
  char *dest = NULL;
  if (start_index <= src_len) {
    char *dest_cur = dest = calloc(str_len + src_len + 1, sizeof(char));
    s21_memcpy(dest, src, start_index);
    dest_cur += start_index;
    src += start_index;
    s21_memcpy(dest_cur, str, str_len);
    dest_cur += str_len;
    s21_memcpy(dest_cur, src, src_len - start_index);
    dest_cur[src_len - start_index] = '\0';
  }
  return (void *)dest;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == NULL || trim_chars == NULL) return NULL;

  const char *copy_trim_chars = *trim_chars == '\0' ? " " : trim_chars;
  while (s21_strcspn(src, copy_trim_chars) == 0 && *src != '\0') src++;

  size_t src_rlen = s21_strlen(src);
  while (src_rlen > 0 && s21_strcspn(src + src_rlen - 1, copy_trim_chars) == 0)
    src_rlen--;

  char *dest = malloc((src_rlen + 1) * sizeof(char));
  s21_memcpy(dest, src, src_rlen);
  dest[src_rlen] = '\0';

  return (void *)dest;
}

int s21_sprintf(char *str, const char *format, ...) {
  int result = 0;
  char *str_cur = str;
  const char *format_cur = format;
  va_list args;
  va_start(args, format);
  while (*format_cur != 0 && result >= 0)
    if (*format_cur != '%')
      s21_sprintf_write_byte(&str_cur, &result, *(format_cur++));
    else {
      s21_token token = {0};
      s21_token_make(&format_cur, &token, args);
      s21_token_write(&str_cur, &result, args, &token);
    }
  va_end(args);
  *str_cur = '\0';
  return result;
}