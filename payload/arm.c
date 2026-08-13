#include "include/arm.h"

unsigned int __aeabi_uidiv(unsigned int n, unsigned int d) {
  unsigned int q = 0;
  while (n >= d)
    n -= d, q++;
  return q;
}

void patch_call(uint32_t addr, void *func, jump_type_t type) {
  int32_t off = (int32_t)(((uintptr_t)func & ~(uintptr_t)1) - (addr + 4));
  uint16_t hi = 0xF000 | ((off >> 12) & 0x7FF);
  uint16_t lo = (type == JUMP_BLX ? 0xE800 : 0xF800) | ((off >> 1) & 0x7FF);

  volatile uint16_t *p = (volatile uint16_t *)(uintptr_t)addr;
  p[0] = hi;
  p[1] = lo;
}

void arch_clean_invalidate_cache_range(uintptr_t start, uintptr_t size) {
  uintptr_t end = start + size;
  start &= ~(CACHE_LINE - 1);

  while (start < end)
    __asm__ volatile("mcr p15, 0, %0, c7, c14, 1\n"
                     "add %0, %0, %[cl]\n"
                     : "+r"(start)
                     : [cl] "r"(CACHE_LINE)
                     : "memory");

  __asm__ volatile("mcr p15, 0, %0, c7, c10, 4" ::"r"(start = 0) : "memory");
}