#include "include/commands.h"
#include "include/common.h"
#include "include/fastboot.h"

void original_flash(const char *arg, void *data, unsigned sz) {
  ((void (*)(const char *arg, void *data, unsigned sz))(0x4c439728 | 1))(
      arg, data, sz);
}

void original_erase(const char *arg, void *data, unsigned sz) {
  ((void (*)(const char *arg, void *data, unsigned sz))(0x4c439309 | 1))(
      arg, data, sz);
}

void original_download(const char *arg, void *data, unsigned sz) {
  ((void (*)(const char *arg, void *data, unsigned sz))(0x4c439c9c | 1))(
      arg, data, sz);
}

void cmd_download(const char *arg, void *data, unsigned sz) {
  if (arg && *arg) {
    original_download(arg, data, sz);
  } else {
    fastboot_fail("Usage: oem download <size_in_hex>");
  }
}

void cmd_help(const char *arg, void *data, unsigned sz) {
  fastboot_info("");
  fastboot_info("Available commands:");
  fastboot_info("");
  fastboot_info("flash:");
  fastboot_info("download:");
  fastboot_info("erase:");
  fastboot_info("getvar:");
  fastboot_info("reboot:");
  fastboot_info("reboot-bootloader:");
  fastboot_info("reboot-recovery:");
  fastboot_info("continue:");
  fastboot_info("set-active:");
  fastboot_info("boot:");
  fastboot_info("");
  fastboot_info("oem help");
  fastboot_info("oem is-partition-protected <partition>");
  fastboot_info("oem lks");
  fastboot_info("oem key");
  fastboot_info("oem p2u");
  fastboot_info("oem dump_pllk_log");
  fastboot_info("oem off-mode-charge");
  fastboot_info("oem printk-ratelimit");
  fastboot_info("oem get_socid");
  fastboot_info("oem scp_status <0|1>");
  fastboot_info("oem scp_log_thru_ap_uart");
  fastboot_info("oem usb2jtag <0|1>");
  fastboot_info("oem ultraflash");
  fastboot_info("oem ultraflash_en <0|1>");
  fastboot_info("oem keepalive");
  fastboot_info("oem cid");
  fastboot_info("oem cid digest");
  fastboot_info("oem md5");
  fastboot_info("oem sha256");
  fastboot_info("oem flashinfo");
  fastboot_info("oem fac get");
  fastboot_info("oem config fac");
  fastboot_info("oem batterysn get");
  fastboot_info("oem config batterysn");
  fastboot_info("oem carrier get");
  fastboot_info("oem config carrier <string>");
  fastboot_info("oem dualsim get");
  fastboot_info("oem config dualsim <0|1>");
  fastboot_info("oem wallpaper get");
  fastboot_info("oem config wallpaper <number>");
  fastboot_info("oem set_active");
  fastboot_info("oem continue");
  fastboot_info("oem shutdown");
  fastboot_info("oem efuse enable");
  fastboot_info("oem ssm enable-thinkshield");
  fastboot_info("oem ssm enable-zerotouch");
  fastboot_info("oem ssm disable-thinkshield");
  fastboot_info("oem ssm disable-zerotouch");
  fastboot_info("oem download <size_in_hex>");
  fastboot_okay("");
}

void cmd_flash(const char *arg, void *data, unsigned sz) {
  if (!arg || *arg == '\0') {
    fastboot_fail("Invalid argument!");
    return;
  }

  if (fastboot_is_protected_partition(arg)) {
    fastboot_fail("Partition is protected");
    return;
  }

  original_flash(arg, data, sz);
}

void cmd_erase(const char *arg, void *data, unsigned sz) {
  if (!arg || *arg == '\0') {
    fastboot_fail("Invalid argument!");
    return;
  }

  if (fastboot_is_protected_partition(arg)) {
    fastboot_fail("Partition is protected");
    return;
  }

  original_erase(arg, data, sz);
}

void cmd_flashing_unlock(const char *arg, void *data, unsigned sz) {
  fastboot_fail("This command has been disabled for security reasons");
}

void cmd_flashing_lock(const char *arg, void *data, unsigned sz) {
  fastboot_info("");
  fastboot_info("To lock the bootloader, you need to flash");
  fastboot_info("stock firmare first");
  fastboot_info("");
  fastboot_fail("");
}

void cmd_ssm_enable_thinkshield(const char *arg, void *data, unsigned sz) {
  int ret = ((int (*)(int))(0x4c437934 | 1))(1);
  if (ret) {
    fastboot_fail("Enable thinkshield failed");
    return;
  }
  fastboot_okay("");
}

void cmd_ssm_enable_zerotouch(const char *arg, void *data, unsigned sz) {
  int ret = ((int (*)(int))(0x4c4379ac | 1))(1);
  if (ret) {
    fastboot_fail("Enable zerotouch failed");
    return;
  }
  fastboot_okay("");
}

void cmd_is_partition_protected(const char *arg, void *data, unsigned sz) {
  if (!arg || !*arg) {
    fastboot_fail("Missing partition name");
    return;
  }

  while (*arg == ' ')
    arg++;
  if (!*arg) {
    fastboot_fail("Missing partition name");
    return;
  }

  const char *p = arg;
  while (*p && *p != ' ')
    p++;
  if (*p) {
    fastboot_fail("Invalid partition name");
    return;
  }

  if (fastboot_is_protected_partition(arg)) {
    fastboot_info("Partition is protected");
    return;
  };
  fastboot_info("Partition is not protected");
}

void register_commands() {
  fastboot_publish("membase", "0x4C400000");
  fastboot_publish("chokichou-version", VERSION);

  fastboot_register("oem help", cmd_help, 1);
  fastboot_register("oem ssm enable-thinkshield", cmd_ssm_enable_thinkshield, 1);
  fastboot_register("oem ssm enable-zerotouch", cmd_ssm_enable_zerotouch, 1);
  fastboot_register("flash:", cmd_flash, 1);
  fastboot_register("erase:", cmd_erase, 1);
  fastboot_register("flashing lock", cmd_flashing_lock, 1);
  fastboot_register("flashing unlock", cmd_flashing_unlock, 1);
  fastboot_register("oem download", cmd_download, 1);
  fastboot_register("oem is-partition-protected", cmd_is_partition_protected, 1);
}