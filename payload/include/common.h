#pragma once

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define VERSION "0.0.1"

int app();
void platform_init();
void early_init();
void late_init();