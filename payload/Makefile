CC := arm-none-eabi-gcc
AS := arm-none-eabi-as
LD := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy

BUILD_DIR := build
TARGET := $(BUILD_DIR)/payload

SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCES))

CFLAGS := -std=gnu99 -Os -mthumb -mcpu=cortex-a9 -fno-builtin-printf -fno-strict-aliasing
CFLAGS += -fno-builtin-memcpy -mno-unaligned-access -DPRINTF_DISABLE_SUPPORT_FLOAT=1 -fPIE
LDFLAGS := -T linker.x -nodefaultlibs -nostdlib

ifeq ($(DEBUG),1)
$(warning Debug mode enabled)
CFLAGS += -DDEBUG
endif

all: $(TARGET).bin

$(TARGET).bin: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $(TARGET).elf $(OBJECTS)
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean