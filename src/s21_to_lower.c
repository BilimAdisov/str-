#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *new_str = s21_NULL;

  if (str != s21_NULL) {
    int size = s21_strlen(str);

    new_str = malloc((size + 1) * sizeof(char));
    if (new_str != s21_NULL) {
      s21_strncpy(new_str, str, size);
      new_str[size] = '\0';

      for (int i = 0; new_str[i] != '\0'; i++) {
        if (new_str[i] >= 'A' && new_str[i] <= 'Z') {
          new_str[i] += 32;
        }
      }
    }
  }

  return new_str;
}