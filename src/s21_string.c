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
  char *dest_ptr = dest + s21_strlen(dest);
  s21_size_t l = s21_strlen(src);
  if (l < n) n = l;
  for (s21_size_t i = 0; i < n; i++) {
    if (src[i] != '\0') {
      *dest_ptr = src[i];
      dest_ptr++;
    }
  }
  return dest;
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

char *s21_strtok(char *str, const char *delim) {
  char *token = s21_NULL;
  if (delim != s21_NULL) {
    static char *next_token = s21_NULL;

    if (str) next_token = str;

    if (next_token) {
      while (*next_token && s21_strchr(delim, *next_token)) next_token++;

      if (*next_token != '\0') {
        token = next_token;

        while (*next_token && !s21_strchr(delim, *next_token)) next_token++;

        if (*next_token) {
          *next_token++ = '\0';
        } else {
          next_token = s21_NULL;
        }
      }
    }
  }

  return token;
}

char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;
  while (*str != '\0') {
    if (*str == c) result = (char *)str;
    str++;
  }
  if (c == '\0') result = (char *)str;
  return result;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;

  if (haystack != s21_NULL && needle != s21_NULL) {
    for (s21_size_t i = 0; haystack[i] != '\0'; i++) {
      s21_size_t j = 0;
      while (haystack[i + j] == needle[j] && needle[j] != '\0') j++;

      if (needle[j] == '\0') {
        result = (char *)&haystack[i];
        break;
      }
    }
  }

  return result;
}

char *s21_strrchr(const char *str, int c) {
  if (str == s21_NULL) {
    return s21_NULL;
  }
  const char *result = s21_NULL;

  for (int i = s21_strlen(str) - 1; i >= 0; i--) {
    if (str[i] == (char)c) {
      result = &str[i];
      break;
    }
  }
  return (char *)result;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;

  if (str1 != s21_NULL && str2 != s21_NULL) {
    for (s21_size_t i = 0; str1[i] != '\0'; i++) {
      for (s21_size_t j = 0; str2[j] != '\0'; j++) {
        if (str1[i] == str2[j]) {
          result = (char *)&str1[i];
          return result;
        }
      }
    }
  }
  return result;
}
char *s21_strerror(int errnum) {
  char *error = "Unknown error";

#ifdef __linux__
  static char *errors[] = {
      "Success",                                            // 0
      "Operation not permitted",                            // 1
      "No such file or directory",                          // 2
      "No such process",                                    // 3
      "Interrupted system call",                            // 4
      "Input/output error",                                 // 5
      "No such device or address",                          // 6
      "Argument list too long",                             // 7
      "Exec format error",                                  // 8
      "Bad file descriptor",                                // 9
      "No child processes",                                 // 10
      "Resource temporarily unavailable",                   // 11
      "Cannot allocate memory",                             // 12
      "Permission denied",                                  // 13
      "Bad address",                                        // 14
      "Block device required",                              // 15
      "Device or resource busy",                            // 16
      "File exists",                                        // 17
      "Invalid cross-device link",                          // 18
      "No such device",                                     // 19
      "Not a directory",                                    // 20
      "Is a directory",                                     // 21
      "Invalid argument",                                   // 22
      "Too many open files in system",                      // 23
      "Too many open files",                                // 24
      "Inappropriate ioctl for device",                     // 25
      "Text file busy",                                     // 26
      "File too large",                                     // 27
      "No space left on device",                            // 28
      "Illegal seek",                                       // 29
      "Read-only file system",                              // 30
      "Too many links",                                     // 31
      "Broken pipe",                                        // 32
      "Numerical argument out of domain",                   // 33
      "Numerical result out of range",                      // 34
      "Resource deadlock avoided",                          // 35
      "File name too long",                                 // 36
      "No locks available",                                 // 37
      "Function not implemented",                           // 38
      "Directory not empty",                                // 39
      "Too many levels of symbolic links",                  // 40
      "Unknown error 41",                                   // 41
      "No message of desired type",                         // 42
      "Identifier removed",                                 // 43
      "Channel number out of range",                        // 44
      "Level 2 not synchronized",                           // 45
      "Level 3 halted",                                     // 46
      "Level 3 reset",                                      // 47
      "Link number out of range",                           // 48
      "Protocol driver not attached",                       // 49
      "No CSI structure available",                         // 50
      "Level 2 halted",                                     // 51
      "Invalid exchange",                                   // 52
      "Invalid request descriptor",                         // 53
      "Exchange full",                                      // 54
      "No anode",                                           // 55
      "Invalid request code",                               // 56
      "Invalid slot",                                       // 57
      "Unknown error 58",                                   // 58
      "Bad font file format",                               // 59
      "Device not a stream",                                // 60
      "No data available",                                  // 61
      "Timer expired",                                      // 62
      "Out of streams resources",                           // 63
      "Machine is not on the network",                      // 64
      "Package not installed",                              // 65
      "Object is remote",                                   // 66
      "Link has been severed",                              // 67
      "Advertise error",                                    // 68
      "Srmount error",                                      // 69
      "Communication error on send",                        // 70
      "Protocol error",                                     // 71
      "Multihop attempted",                                 // 72
      "RFS specific error",                                 // 73
      "Bad message",                                        // 74
      "Value too large for defined data type",              // 75
      "Name not unique on network",                         // 76
      "File descriptor in bad state",                       // 77
      "Remote address changed",                             // 78
      "Can not access a needed shared library",             // 79
      "Accessing a corrupted shared library",               // 80
      ".lib section in a.out corrupted",                    // 81
      "Attempting to link in too many shared libraries",    // 82
      "Cannot exec a shared library directly",              // 83
      "Invalid or incomplete multibyte or wide character",  // 84
      "Interrupted system call should be restarted",        // 85
      "Streams pipe error",                                 // 86
      "Too many users",                                     // 87
      "Socket operation on non-socket",                     // 88
      "Destination address required",                       // 89
      "Message too long",                                   // 90
      "Protocol wrong type for socket",                     // 91
      "Protocol not available",                             // 92
      "Protocol not supported",                             // 93
      "Socket type not supported",                          // 94
      "Operation not supported",                            // 95
      "Protocol family not supported",                      // 96
      "Address family not supported by protocol",           // 97
      "Address already in use",                             // 98
      "Cannot assign requested address",                    // 99
      "Network is down"                                     // 100
  };
  static int errors_count = sizeof(errors) / sizeof(errors[0]);

  if (errnum >= 0 && errnum < errors_count) {
    error = errors[errnum];
  }
#elif __APPLE__
  static char *errors[] = {
      "Undefined error: 0",                               // 0
      "Operation not permitted",                          // 1
      "No such file or directory",                        // 2
      "No such process",                                  // 3
      "Interrupted system call",                          // 4
      "Input/output error",                               // 5
      "Device not configured",                            // 6
      "Argument list too long",                           // 7
      "Exec format error",                                // 8
      "Bad file descriptor",                              // 9
      "No child processes",                               // 10
      "Resource deadlock avoided",                        // 11
      "Cannot allocate memory",                           // 12
      "Permission denied",                                // 13
      "Bad address",                                      // 14
      "Block device required",                            // 15
      "Resource busy",                                    // 16
      "File exists",                                      // 17
      "Cross-device link",                                // 18
      "Operation not supported by device",                // 19
      "Not a directory",                                  // 20
      "Is a directory",                                   // 21
      "Invalid argument",                                 // 22
      "Too many open files in system",                    // 23
      "Too many open files",                              // 24
      "Inappropriate ioctl for device",                   // 25
      "Text file busy",                                   // 26
      "File too large",                                   // 27
      "No space left on device",                          // 28
      "Illegal seek",                                     // 29
      "Read-only file system",                            // 30
      "Too many links",                                   // 31
      "Broken pipe",                                      // 32
      "Numerical argument out of domain",                 // 33
      "Result too large",                                 // 34
      "Resource temporarily unavailable",                 // 35
      "Operation now in progress",                        // 36
      "Operation already in progress",                    // 37
      "Socket operation on non-socket",                   // 38
      "Destination address required",                     // 39
      "Message too long",                                 // 40
      "Protocol wrong type for socket",                   // 41
      "Protocol not available",                           // 42
      "Protocol not supported",                           // 43
      "Socket type not supported",                        // 44
      "Operation not supported",                          // 45
      "Protocol family not supported",                    // 46
      "Address family not supported by protocol family",  // 47
      "Address already in use",                           // 48
      "Can't assign requested address",                   // 49
      "Network is down",                                  // 50
      "Network is unreachable",                           // 51
      "Network dropped connection on reset",              // 52
      "Software caused connection abort",                 // 53
      "Connection reset by peer",                         // 54
      "No buffer space available",                        // 55
      "Socket is already connected",                      // 56
      "Socket is not connected",                          // 57
      "Can't send after socket shutdown",                 // 58
      "Too many references: can't splice",                // 59
      "Operation timed out",                              // 60
      "Connection refused",                               // 61
      "Too many levels of symbolic links",                // 62
      "File name too long",                               // 63
      "Host is down",                                     // 64
      "No route to host",                                 // 65
      "Directory not empty",                              // 66
      "Too many processes",                               // 67
      "Too many users",                                   // 68
      "Disc quota exceeded",                              // 69
      "Stale NFS file handle",                            // 70
      "Too many levels of remote in path",                // 71
      "RPC struct is bad",                                // 72
      "RPC version wrong",                                // 73
      "RPC prog. not avail",                              // 74
      "Program version wrong",                            // 75
      "Bad procedure for program",                        // 76
      "No locks available",                               // 77
      "Function not implemented",                         // 78
      "Inappropriate file type or format",                // 79
      "Authentication error",                             // 80
      "Need authenticator",                               // 81
      "Device power is off",                              // 82
      "Device error",                                     // 83
      "Value too large to be stored in data type",        // 84
      "Bad executable (or shared library)",               // 85
      "Bad CPU type in executable",                       // 86
      "Shared library version mismatch",                  // 87
      "Malformed Mach-o file",                            // 88
      "Operation canceled",                               // 89
      "Identifier removed",                               // 90
      "No message of desired type",                       // 91
      "Illegal byte sequence",                            // 92
      "Attribute not found",                              // 93
      "Bad message",                                      // 94
      "EMULTIHOP (Reserved)",                             // 95
      "No message available on STREAM",                   // 96
      "ENOLINK (Reserved)",                               // 97
      "No STREAM resources",                              // 98
      "Not a STREAM",                                     // 99
      "Protocol error"                                    // 100
  };
  static int errors_count = sizeof(errors) / sizeof(errors[0]);

  if (errnum >= 0 && errnum < errors_count) {
    error = errors[errnum];
  }
#endif

  return error;
}
