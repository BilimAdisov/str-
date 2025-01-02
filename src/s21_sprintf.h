#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#define s21_size_t unsigned long long
#include <math.h>
#include <stdarg.h>

typedef struct {
  int space;
  int sign;
  int left_align;
  int width;
  int precision;
  int var_length;
  int size;
  int round_float;
} Settings;

void GetSettings(char** format, Settings* settings, va_list* arg);
void GetFlags(char** format, Settings* settings);
void GetWidth(char** format, Settings* settings, va_list* arg);
void GetPrecision(char** format, Settings* settings, va_list* arg);
void GetLength(char** format, Settings* settings);
char* ParseSpecifiers(char* str, char* src, char** format, Settings* settings,
                      va_list* arg, char* specifiers);
char* SetDecimal(Settings* settings, va_list* arg, char* str);
s21_size_t SetSize(Settings* settings, long int decimal);
void DecimalToString(char* decimal_str, s21_size_t size, long decimal,
                     Settings* settings);
char** FormatShift(char** format, int* spec, va_list* arg, int* round_float);
char* PrintWidth(char* str, Settings* settings, char* decimal_str,
                 s21_size_t size);
char* SetChar(char* str, va_list* arg, Settings* settings);
char* SetString(char* str, va_list* arg, Settings* settings);
char* SetUnsigned(char* str, va_list* arg, Settings* settings);
char* SetFloat(char* str, va_list* arg, Settings* settings);
void GetDecimal(long int decimal, char* buffer, int* size, int* decimal_size);
void GetFract(long double fract, int prec, char* buffer, int* size);
void DefaultFloatPrecision(Settings* settings);
char* PrintFloating(char* str, Settings* settings, int decimal_size, int size,
                    char* buffer);
char* AddSign(int negative, char* str, Settings* settings);

#endif