#include "include/fastboot.h"
#include "string.h"

void fastboot_info(const char *reason) {
  ((void (*)(const char *reason))(0x4c42aafc | 1))(reason);
}

void fastboot_fail(const char *reason) {
  ((void (*)(const char *reason))(0x4c42ab7c | 1))(reason);
}

void fastboot_okay(const char *reason) {
  ((void (*)(const char *reason))(0x4c42ad48 | 1))(reason);
}

void fastboot_register(const char *prefix,
                       void (*handle)(const char *arg, void *data, unsigned sz),
                       unsigned char security_enabled) {
  ((void (*)(const char *prefix,
             void (*handle)(const char *arg, void *data, unsigned sz),
             unsigned char security_enabled))(0x4c42a74c | 1))(
      prefix, handle, security_enabled);
}

void fastboot_publish(const char *name, const char *value) {
  ((void (*)(const char *name, const char *value))(0x4c42a788 | 1))(name,
                                                                    value);
}

int fastboot_is_protected_partition(const char *partition) {
  return (strcmp(partition, "boot0") == 0 || strcmp(partition, "boot1") == 0 ||
          strcmp(partition, "boot2") == 0 ||
          strcmp(partition, "preloader") == 0 ||
          strcmp(partition, "preloader_a") == 0 ||
          strcmp(partition, "preloader_b") == 0);
}
