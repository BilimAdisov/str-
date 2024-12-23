#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *new_str = (const unsigned char *)str;
  unsigned char new_c = (unsigned char)c;
  void *result = s21_NULL;
  for (s21_size_t i = 0; i < n && new_str; i++) {
    if (*new_str == new_c) {
      result = (void *)new_str;
      break;
    }
    new_str++;
  }
  return result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0;
  const unsigned char *new_str1 = (const unsigned char *)str1;
  const unsigned char *new_str2 = (const unsigned char *)str2;
  for (s21_size_t i = 0; i < n; i++) {
    if (new_str1[i] == new_str2[i]) {
      result += 0;
    } else if (new_str1[i] != new_str2[i]) {
      result = new_str1[i] - new_str2[i];
      break;
    }
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  const unsigned char *new_src = (const unsigned char *)src;
  unsigned char *new_dest = (unsigned char *)dest;
  int b = 0;
  for (s21_size_t i = 0; i < n; i++) {
    new_dest[i] = new_src[i];
    b++;
  }
  return (void *)new_dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *new_str = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    new_str[i] = c;
  }
  return new_str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *dest_ptr = dest;
  while (*dest_ptr) {
    dest_ptr++;
  }
	s21_size_t src_len = s21_strlen(src);
  for (s21_size_t i = 0; i < n; i++) {
    if (i < src_len) {
      *dest_ptr = src[i];
      dest_ptr++;
    }
  }
  return dest;
}



char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;
  while (*str != '\0') {
    if (*str == c)
      result = (char *)str;
    str++;
  }
  if (c == '\0')
    result = (char *)str;
  return result;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  while (n > 0) {
    if (*str1 != *str2) {
      result = (unsigned char)*str1 - (unsigned char)*str2;
      break;
    }
    str1++;
    str2++;
    n--;
  }
  return result;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  for (; i < n; i++) {
    dest[i] = '\0';
  }
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t length = 0;
  int check = 0;
  for (int i = 0; str1[i] != '\0' && !check; i++) {
    for (int j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        check = 1;
        break;
      }
    }
    if (!check) {
      length++;
    }
  }
  return length;
}

s21_size_t s21_strlen(const char *src) {
  s21_size_t length = 0;
  if (src) {
    while (src[length] != '\0') {
      length++;
    }
  }
  return length;
}