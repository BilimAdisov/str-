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
    if(new_str1[i] == new_str2[i]) {
      result += 0;
    } else if(new_str1[i] != new_str2[i]) {
      result = new_str1[i] - new_str2[i];
      break;
    }
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    const unsigned char* new_src = (const unsigned char*)src;
    unsigned char* new_dest = (unsigned char*)dest;
    int b = 0;
    for (s21_size_t i = 0; i < n; i++)
    {
        new_dest[i] = new_src[i];
        b++;
    }
    return (void*)new_dest;
}

void* s21_memset(void *str, int c, s21_size_t n) {
    unsigned char* new_str = (unsigned char*)str;
    for (s21_size_t i = 0; i < n; i++)
    {
        new_str[i] = c;
    }
    return new_str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    char* dest_ptr =  dest;
    while (*dest_ptr) {
        dest_ptr++;
    }
    for(s21_size_t i = 0; i < n; i++) {
        if(src[i] != '\0') {
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
            result =  (unsigned char)*str1 - (unsigned char)*str2;
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
        if (*str == c)
            result = (char*)str;
        str++;
    }
    if (c == '\0') result = (char*)str;
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
        "Error 0",
        "Operation not permitted",
        "No such file or directory",
        "No such process",
        "Interrupted function call",
        "Input/output error",
        "No such device or address",
        "Arg list too long",
        "Exec format error",
        "Bad file descriptor",
        "No child processes",
        "Resource deadlock avoided",
        "Cannot allocate memory",
        "Permission denied",
        "Bad address",
        "Not a block device",
        "Resource busy",
        "File exists",
        "Improper link",
        "Operation not supported by device",
        "Not a directory",
        "Is a directory",
        "Invalid argument",
        "Too many open files in system",
        "Too many open files",
        "Inappropriate ioctl for device",
        "Text file busy",
        "File too large",
        "Device out of space",
        "Illegal seek",
        "Read-only file system",
        "Too many links",
        "Broken pipe",
        "Numerical argument out of domain",
        "Numerical result out of range",
        "Resource temporarily unavailable",
        "Operation now in progress",
        "Operation already in progress",
        "Socket operation on non-socket",
        "Destination address required",
        "Message too long",
        "Protocol wrong type for socket",
        "Protocol not available",
        "Protocol not supported",
        "Socket type not supported",
        "Not supported",
        "Protocol family not supported",
        "Address family not supported by protocol family",
        "Address already in use",
        "Cannot assign requested address",
        "Network is down",
        "Network is unreachable",
        "Network dropped connection on reset",
        "Software caused connection abort",
        "Connection reset by peer",
        "No buffer space available",
        "Socket is already connected",
        "Socket is not connected",
        "Cannot send after socket shutdown",
        "Operation timed out",
        "Connection refused",
        "Too many levels of symbolic links",
        "File name too long",
        "Host is down",
        "No route to host",
        "Directory not empty",
        "Too many processes",
        "Too many users",
        "Disc quota exceeded",
        "Stale NFS file handle",
        "Bad RPC struct",
        "RPC version wrong",
        "RPC prog. not avail.",
        "Program version wrong",
        "Bad procedure for program",
        "No locks available",
        "Function not implemented",
        "Inappropriate file type or format",
        "Authentication error",
        "Need authenticator",
        "Device power is off",
        "Device error",
        "Value too large to be stored in data type",
        "Bad executable (or shared library)",
        "Bad CPU type in executable",
        "Shared library version mismatch",
        "Malformed Mach-o file",
        "Operation canceled",
        "Identifier removed",
        "No message of desired type",
        "Illegal byte sequence",
        "No attribute found",
        "Bad message",
        "Reserved",
        "No message available",
        "Reserved",
        "No STREAM resources",
        "Not a STREAM",
        "Protocol error",
        "STREAM ioctl() timeout",
        "Operation not supported on socket",
        "Unknown error"
    };
    static int errors_count = sizeof(errors) / sizeof(errors[0]);

    if (errnum >= 0 && errnum < errors_count) {
        error = errors[errnum];
    }

#elif __APPLE__
    static char *errors[] = {
        "Success",
        "Operation not permitted",
        "No such file or directory",
        "No such process",
        "Interrupted system call",
        "Input/output error",
        "No such device or address",
        "Argument list too long",
        "Exec format error",
        "Bad file descriptor",
        "No child processes",
        "Resource temporarily unavailable",
        "Cannot allocate memory",
        "Permission denied",
        "Bad address",
        "Block device required",
        "Device or resource busy",
        "File exists",
        "Invalid cross-device link",
        "No such device",
        "Not a directory",
        "Is a directory",
        "Invalid argument",
        "Too many open files in system",
        "Too many open files",
        "Inappropriate ioctl for device",
        "Text file busy",
        "File too large",
        "No space left on device",
        "Illegal seek",
        "Read-only file system",
        "Too many links",
        "Broken pipe",
        "Numerical argument out of domain",
        "Numerical result out of range",
        "Resource deadlock avoided",
        "File name too long",
        "No locks available",
        "Function not implemented",
        "Directory not empty",
        "Too many levels of symbolic links",
        "Unknown error 41",
        "No message of desired type",
        "Identifier removed",
        "Channel number out of range",
        "Level 2 not synchronized",
        "Level 3 halted",
        "Level 3 reset",
        "Link number out of range",
        "Protocol driver not attached",
        "No CSI structure available",
        "Level 2 halted",
        "Invalid exchange",
        "Invalid request descriptor",
        "Exchange full",
        "No anode",
        "Invalid request code",
        "Invalid slot",
        "Unknown error 58",
        "Bad font file format",
        "Device not a stream",
        "No data available",
        "Timer expired",
        "Out of streams resources",
        "Machine is not on the network",
        "Package not installed",
        "Object is remote",
        "Link has been severed",
        "Advertise error",
        "Srmount error",
        "Communication error on send",
        "Protocol error",
        "Multihop attempted",
        "RFS specific error",
        "Bad message",
        "Value too large for defined data type",
        "Name not unique on network",
        "File descriptor in bad state",
        "Remote address changed",
        "Can not access a needed shared library",
        "Accessing a corrupted shared library",
        ".lib section in a.out corrupted",
        "Attempting to link in too many shared libraries",
        "Cannot exec a shared library directly",
        "Invalid or incomplete multibyte or wide character",
        "Interrupted system call should be restarted",
        "Streams pipe error",
        "Too many users",
        "Socket operation on non-socket",
        "Destination address required",
        "Message too long",
        "Protocol wrong type for socket",
        "Protocol not available",
        "Protocol not supported",
        "Socket type not supported",
        "Operation not supported",
        "Protocol family not supported",
        "Address family not supported by protocol",
        "Address already in use",
        "Cannot assign requested address",
        "Network is down",
        "Network is unreachable",
        "Network dropped connection on reset",
        "Software caused connection abort",
        "Connection reset by peer",
        "No buffer space available",
        "Transport endpoint is already connected",
        "Transport endpoint is not connected",
        "Cannot send after transport endpoint shutdown",
        "Too many references: cannot splice",
        "Connection timed out",
        "Connection refused",
        "Host is down",
        "No route to host",
        "Operation already in progress",
        "Operation now in progress",
        "Stale file handle",
        "Structure needs cleaning",
        "Not a XENIX named type file",
        "No XENIX semaphores available",
        "Is a named type file",
        "Remote I/O error",
        "Disk quota exceeded",
        "No medium found",
        "Wrong medium type",
        "Operation canceled",
        "Required key not available",
        "Key has expired",
        "Key has been revoked",
        "Key was rejected by service",
        "Owner died",
        "State not recoverable",
        "Operation not possible due to RF-kill",
        "Memory page has hardware error",
        "Unknown error"
    };
    static int errors_count = sizeof(errors) / sizeof(errors[0]);

    if (errnum >= 0 && errnum < errors_count) {
        error = errors[errnum];
    }
#endif

    return error;
}