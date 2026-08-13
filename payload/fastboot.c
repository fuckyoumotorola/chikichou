#include "include/fastboot.h"
#include "string.h"

#define FB(addr, type, ...) ((type)(addr | 1))(__VA_ARGS__)

void fastboot_info(const char *reason) {
  FB(0x4c42aafc, void (*)(const char *), reason);
}

void fastboot_fail(const char *reason) {
  FB(0x4c42ab7c, void (*)(const char *), reason);
}

void fastboot_okay(const char *reason) {
  FB(0x4c42ad48, void (*)(const char *), reason);
}

void fastboot_register(const char *prefix,
                       void (*handle)(const char *, void *, unsigned),
                       unsigned char security_enabled) {
  FB(0x4c42a74c,
     void (*)(const char *, void (*)(const char *, void *, unsigned), unsigned char),
     prefix, handle, security_enabled);
}

void fastboot_publish(const char *name, const char *value) {
  FB(0x4c42a788, void (*)(const char *, const char *), name, value);
}

int fastboot_is_protected_partition(const char *p) {
  return !strcmp(p, "boot0") || !strcmp(p, "boot1") ||
         !strcmp(p, "boot2") || !strcmp(p, "preloader") ||
         !strcmp(p, "preloader_a") || !strcmp(p, "preloader_b");
}