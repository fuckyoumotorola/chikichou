#include "include/common.h"
#include "include/arm.h"
#include "include/commands.h"

int app() { return ((int (*)(void))(0x4c42a0dc | 1))(); }

void platform_init() { ((void (*)(void))(0x4c4039b4 | 1))(); }

void late_init() {
  register_commands();

  // Hide the orange unlocked-bootloader state indicator
  volatile uint16_t *x = (volatile uint16_t *)0x4c45079c;
  x[0] = 0x2000;
  x[1] = 0x4770;
  arch_clean_invalidate_cache_range((uint32_t)0x4c45079c, 2);

  ((int (*)(int, int))(0x4c434e14 | 1))(0, 0);
}

void early_init() {
  __asm__("mcr p15, 0, %0, c7, c5, 0" : : "r"(0));

  volatile uint16_t *x = (volatile uint16_t *)0x4c42b264; // register cmd_flash
  x[0] = 0x46c0;
  x[1] = 0x46c0;
  arch_clean_invalidate_cache_range((uint32_t)0x4c42b264, 2);

  x = (volatile uint16_t *)0x4c42b4be; // register cmd_flashing_lock
  x[0] = 0x46c0;
  x[1] = 0x46c0;
  arch_clean_invalidate_cache_range((uint32_t)0x4c42b4be, 2);

  x = (volatile uint16_t *)0x4c42b4aa; // register cmd_flashing_unlock
  x[0] = 0x46c0;
  x[1] = 0x46c0;
  arch_clean_invalidate_cache_range((uint32_t)0x4c42b4aa, 2);

  x = (volatile uint16_t *)0x4c42b278; // register cmd_erase
  x[0] = 0x46c0;
  x[1] = 0x46c0;
  arch_clean_invalidate_cache_range((uint32_t)0x4c42b278, 2);

  x = (volatile uint16_t *)0x4c437430; // tinno_commercial_device_force_lock
  x[0] = 0x2000;
  x[1] = 0x4770;
  x[2] = 0x46c0;
  arch_clean_invalidate_cache_range((uint32_t)0x4c437430, 3);

  x = (volatile uint16_t *)0x4c482a54; // efuse lock
  x[0] = 0x2000;
  x[1] = 0x4770;
  arch_clean_invalidate_cache_range((uint32_t)0x4c482a54, 2);

  x = (volatile uint16_t *)0x4c434ea0; // tinno_facmode_init
  x[0] = 0x2000;
  x[1] = 0x4770;
  arch_clean_invalidate_cache_range((uint32_t)0x4c434ea0, 2);

  x = (volatile uint16_t
           *)0x4c437898; // bypass oem ssm subcommands restrictions
  x[0] = 0x2001;
  x[1] = 0x4770;
  arch_clean_invalidate_cache_range((uint32_t)0x4c437898, 2);
}