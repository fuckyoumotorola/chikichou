#include "include/string.h"
#include <stddef.h>
#include <stdint.h>

char *strchr(const char *s, int c) {
  for (; *s != (char)c; ++s)
    if (*s == '\0')
      return NULL;
  return (char *)s;
}

int strcmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  return *(unsigned char *)s1 - *(unsigned char *)s2;
}

size_t strlen(const char *str) {
  if (!str) {
    return 0;
  }

  volatile const char *p = str;
  size_t len = 0;

  while (len < 1024) {
    if (((uintptr_t)p) & 0xFFFFFFFC) {
      if (*p == '\0')
        return len;
      p++;
      len++;
    } else {
      return len;
    }
  }

  return len;
}

int strncmp(const char *cs, const char *ct, size_t count) {
  signed char res = 0;
  while (count) {
    if ((res = *cs - *ct++) != 0 || !*cs++)
      break;
    count--;
  }
  return res;
}

size_t strspn(const char *s, const char *accept) {
  const char *p;
  const char *a;
  size_t count = 0;

  for (p = s; *p != '\0'; ++p) {
    for (a = accept; *a != '\0'; ++a) {
      if (*p == *a)
        break;
    }
    if (*a == '\0')
      return count;
    ++count;
  }

  return count;
}

size_t strcspn(const char *str, const char *reject) {
  const char *p;
  const char *r;
  size_t count = 0;

  for (p = str; *p != '\0'; ++p) {
    for (r = reject; *r != '\0'; ++r) {
      if (*p == *r) {
        return count;
      }
    }
    ++count;
  }
  return count;
}