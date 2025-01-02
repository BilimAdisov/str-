
#include "s21_string.h"
void *s21_trim(const char *src, const char *trim_chars) {
  char *new_src = s21_NULL;
  if (src != s21_NULL) {
    s21_size_t len = s21_strlen(src);
    new_src = malloc(sizeof(char) * (len + 1));
    if (new_src == s21_NULL) {
      return s21_NULL;
    }
    s21_strncpy(new_src, src, len);
    new_src[len] = '\0';
    char *new_start = new_src;
    char *new_end = new_src + len - 1;
    if (trim_chars) {
      char *res;
      do {
        if (*new_start != '\0') {
          res = s21_strchr(trim_chars, *new_start);
          if (res) {
            new_start++;
          }
        } else {
          break;
        }
      } while (res);
      do {
        if (new_end > new_start && *new_end) {
          res = s21_strchr(trim_chars, *new_end);
          if (res) {
            new_end--;
          }
        } else {
          break;
        }
      } while (res);
    } else {
      while (isspace(*new_start)) {
        new_start++;
      }
      while (isspace(*new_end) && new_end >= new_start) {
        new_end--;
      }
    }
    if (new_start > new_end) {
      new_src[0] = '\0';
    } else {
      s21_size_t new_len = new_end - new_start + 1;
      s21_memcpy(new_src, new_start, new_len);
      new_src[new_len] = '\0';
    }
  }
  return new_src;
}