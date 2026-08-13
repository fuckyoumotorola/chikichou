#include "include/arm.h"
#include "include/common.h"

void chokichou() {
  late_init();
  int ret = app();

  while (1) {
    __asm__("wfi");
  }
}

__attribute__((section(".text.start"))) int main(void) {
  patch_call(0x4c42794c, (void *)chokichou, JUMP_BL);
  early_init();
  platform_init();

  return 0;
}