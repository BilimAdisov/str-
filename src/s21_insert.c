#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *new = s21_NULL;

  if (str && src && start_index <= s21_strlen(src)) {
    int new_length = s21_strlen(src) + s21_strlen(str) + 1;
    new = malloc(sizeof(char) * new_length);
    s21_size_t i = 0;
    for (; i < start_index; i++) {
      new[i] = src[i];
    }
    for (s21_size_t j = 0; j < s21_strlen(str); j++) {
      new[i++] = str[j];
    }
    for (s21_size_t j = start_index; j < s21_strlen(src); j++) {
      new[i++] = src[j];
    }
    new[new_length - 1] = '\0';
  }
  return new;
}
