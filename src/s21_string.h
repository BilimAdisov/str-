#ifndef S21_STRING_H
#define S21_STRING_H

#define s21_size_t unsigned long long
#define s21_NULL (void *)0
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
  int space;
  int sign;
  int left_align;
  int width;
  int precision;
  int var_length;
  int size;
} Settings;

void* s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void* s21_memcpy(void *dest, const void *src, s21_size_t n);
void* s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
s21_size_t s21_strlen(const char *src);
char *s21_strerror(int errnum);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int symbol);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

#endif