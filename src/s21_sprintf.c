#include "s21_string.h"
#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
    char* format_copy = (char*)format;
    char* specifiers = "cdfsu%";
    char* src = str;
    va_list arg;
    va_start(arg, format);
    while (*format_copy) {
        if (*format_copy == '%') {
            Settings settings = {0};
            GetSettings(&format_copy, &settings, &arg);
            str = ParseSpecifiers(str, src, &format_copy, &settings, &arg, specifiers);
        } else {
            *str = *format_copy;
            str++;
            format_copy++;
        }
    }
    *str = '\0';
    return str - src;
}

void GetSettings(char** format, Settings* settings, va_list* arg) {
    GetFlags(format, settings);
    GetWidth(format, settings, arg);
    if (**format == '.') {
        GetPrecision(format, settings, arg);
    }
    GetLength(format, settings);
}

char* ParseSpecifiers(char* str, char* src, char** format, Settings* settings, va_list* arg, char* specifiers)
{
    while(!s21_strchr(specifiers, **format)) (*format)++;
    switch (**format)
    {
    case 'd':
        str = SetDecimal(settings, arg, str);
        break;
    case 'c':
        str = SetChar(str, arg, settings);
        break;
    case 's':
        str = SetString(str, arg, settings);
        break;
    case 'u':
        str = SetUnsigned(str, arg, settings);
        break;
    case 'f':
        str = SetFloat(str, arg, settings);
        break;
    case '%':
        *str++ = '%';
        break;
    default:
        *str++ = **format;
        break;
    }
    src++;
    (*format)++;
    return str;
}

void GetFlags(char** format, Settings* settings) {
    int end = 0;
    while(**format && !end) {
        (*format)++;
        switch (**format)
        {
            case '+':
                settings->sign = 1;
                break;
            case '-':
                settings->left_align = 1;
                break;
            case ' ':
                settings->space = 1;
                break;
            default:
                end = 1;
                break;
        }
    }
    settings->space = (settings->space && !settings->sign);
}

void GetWidth(char** format, Settings* settings, va_list* arg) {
    int is_width = 1;
    format = FormatShift(format, &settings->width, arg, &is_width);
    if (settings->width < 0) {
        settings->left_align = 1;
        settings->width *= -1;
    }
}

void GetPrecision(char** format, Settings* settings, va_list* arg) {
    (*format)++;
    format = FormatShift(format, &settings->precision, arg, &settings->round_float);
}

void GetLength(char** format, Settings* settings) {
    int no_length = 0;
    switch(**format) {
        case 'l':
            settings->var_length = (int)'l';
            break;
        case 'h':
            settings->var_length = (int)'h';
            break;
        default:
            no_length = 1;
            break;
    }
    if (!no_length) (*format)++;
}



char* SetDecimal(Settings* settings, va_list* arg, char* str) {
    long int decimal = va_arg(*arg, long int);
    if (settings->var_length == (int)'h') {
        decimal = (short)decimal;
    } else if (settings->var_length == 0) {
        decimal = (int)decimal;
    }
    s21_size_t size = SetSize(settings, decimal);
    char* decimal_str = (char*)malloc(size * sizeof(char));
    if (!decimal_str) {
        fprintf(stderr, "Memory allocation failed\n");
    } else {
        DecimalToString(decimal_str, size, decimal, settings);
        str = PrintWidth(str, settings, decimal_str, size);
        free(decimal_str);
    }

    return str;
}

char* SetChar(char* str, va_list* arg, Settings* settings){ 
    char c = va_arg(*arg, int);
    char* ptr_c = &c;
    str = PrintWidth(str, settings, ptr_c, 1);
    return str;
}

char* SetString(char* str, va_list* arg, Settings *settings) {
    char* ptr = va_arg(*arg, char*);
    int size = s21_strlen(ptr);
    str = PrintWidth(str, settings, ptr, size);
    return str; 
}

char* SetUnsigned(char* str, va_list* arg, Settings* settings){ 
    long unsigned int unsign_number = va_arg(*arg, long unsigned int);
    if (settings->var_length == (int)'h') {
        unsign_number = (unsigned short int)unsign_number;
    } else if (settings->var_length == 0) {
        unsign_number = (unsigned int)unsign_number;
    }
    s21_size_t size = SetSize(settings, unsign_number);
    char* decimal_str = (char*)malloc(size * sizeof(char));
    if (!decimal_str) {
        fprintf(stderr, "Memory allocation failed\n");
    } else {
        DecimalToString(decimal_str, size, unsign_number, settings);
        str = PrintWidth(str, settings, decimal_str, size);
    }
    free(decimal_str);
    return str;
}

char *SetFloat(char *str, va_list* arg, Settings* settings) {
    DefaultFloatPrecision(settings);
    long double floating = va_arg(*arg, double);
    int negative = floating < 0 ? 1 : 0;
    if(negative) floating *= -1;
    long int decimal = floating;
    if (settings->round_float) {
        decimal = round(floating);
    }
    long double fract = floating - decimal;
    if ((round(fract * pow(10, settings->precision)) / pow(10, settings->precision)) == 1) {
        decimal += 1;
    }
    int size = 0;
    int decimal_size = 0;
    char buffer[1000];
    GetDecimal(decimal, buffer, &size, &decimal_size);
    GetFract(fract, settings->precision, buffer, &size);
    if(settings->precision) size++;
    while((settings->width > size) && !settings->left_align) {
        *str++ = ' ';
        settings->width--;
    }
    str = AddSign(negative, str, settings);
    str = PrintFloating(str, settings, decimal_size, size, buffer);
    return str;
}

void DefaultFloatPrecision(Settings* settings) {
    if(!settings->precision && !settings->round_float) {
        settings->precision = 6;
    }
    if(settings->round_float) {
        settings->precision = 0;
    }
}


void GetDecimal(long int decimal, char *buffer, int *size, int* decimal_size) {
  if (decimal == 0) {
    buffer[*size] = decimal + 48;
    *size += 1;
  }
  while (decimal > 0) {
    buffer[*size] = (decimal % 10) + 48;
    decimal /= 10;
    *size += 1;
  }
  *decimal_size = *size;
}

void GetFract(long double fract, int prec, char *buffer, int *size) {
  int dec = prec;
  long double floating = 0;
  for (int i = 0; i < prec; i++) {
    fract *= 10;
    dec--;
    floating = round(fract * pow(10, dec)) / pow(10, dec);
    buffer[*size] = ((int)floating % 10) + 48;
    int temp = (int)fract;
    fract = fract - temp;
    *size += 1;
  }
}

char* AddSign(int negative, char* str, Settings *settings) {
    if (negative) {
        *str++ = '-';
        settings->width--;
    } else if (settings->space) {
        *str++ = ' ';
    } else if (settings->sign) {
        *str++ = '+';
    } 
    return str;
}


char* PrintFloating(char* str, Settings* settings, int decimal_size, int  size, char* buffer) {
    for (int j = decimal_size - 1; j >= 0; j--) {
      *str++ = buffer[j];
    }
    if (settings->precision != 0) *str++ = '.';
    for (int i = decimal_size; i < size - 1; i++) {
        *str++ = buffer[i];
    }
    while ((settings->width > size) && settings->left_align) {
        *str++ = ' ';
        settings->width--;
    }
    return str;
}


char** FormatShift(char** format, int* spec, va_list* arg, int* round_float) {
    if (**format == '*') {
        *spec = va_arg(*arg, int);
        (*format)++;
    } else if (**format >= '0' && **format <= '9') {
        *spec = (int)**format - (int)'0';
        (*format)++;
    } else {
        if (*round_float != 1) {
            *round_float = 1; 
        }
    }
    return format;
}

s21_size_t SetSize(Settings* settings, long int decimal) {
    s21_size_t size = 0;
    s21_size_t count = decimal < 0 ? -decimal : decimal;
    while (count > 0) {
        count /= 10;
        size++;
    }
    if(settings->space && decimal == 0) size++;
    if((s21_size_t)settings->precision > size) size = settings->precision;
    if(settings->space || settings->sign || decimal < 0) {
        settings->size = 1;
        size++;
    }
    if(size == 0 && !settings->precision && !settings->width && !settings->space) size++;
    int check = decimal < 0 || settings->sign || settings->space;
    if(!settings->precision) settings->precision = check ? size - 1 : size;
    return size;
}

void DecimalToString(char* decimal_str, s21_size_t size, long decimal, Settings* settings) {
    int negative = decimal < 0 ? 1 : 0;
    long int decimal_copy = negative ? -decimal : decimal;
    s21_size_t count = 0;
    int f = 0;
    while(decimal_copy && (++count <= size)) {
        f = decimal_copy % 10;
        decimal_copy /= 10;
        decimal_str[size - count] = (char)(f + (int)'0');
    }
    int zero = settings->precision - count;
    while(zero && (++count <= size)) {
        decimal_str[size - count] = '0';
        zero--;
    }
    if(negative) {
        decimal_str[size - ++count] = '-';
    } else {
        if(settings->sign) decimal_str[size - ++count] = '+';
        else if (settings->space) decimal_str[size - ++count] = ' ';
    }

}

char* PrintWidth(char* str, Settings* settings, char* decimal_str, s21_size_t size)
{
    int space = settings->width - size;
    if(space < 0) space = 0;
    s21_size_t final_width = size + space;
   for (s21_size_t i = 0; i < final_width; i++) {
        if (settings->left_align) {
            if (i < size) {
                *str++ = decimal_str[i];
            } else {
                *str++ = ' ';
            }
        } else {
            if (i < (s21_size_t)space) {
                *str++ = ' ';
            } else {
                *str++ = decimal_str[i - space];
            }
        }
    }
    return str;
}
