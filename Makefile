# SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
#
# SPDX-License-Identifier: MIT

TARGET := anchor8

# Target hardware and programmer config
MCU        ?= STM8S103
FAMILY     ?= stm8s
PROGRAMMER ?= stlinkv2
PROG_MCU   ?= stm8s103k3

SRC_DIR        := ./src
SOC_DIR        := ./soc
BIN_DIR        := ./bin
BUILD_DIR      := ./build
DRIVERS_DIR    := ./drivers
MODULES_DIR    := ./modules
INCLUDE_DIR    := ./include
SOC_FAMILY_DIR := $(SOC_DIR)/$(FAMILY)
MOD_FAMILY_DIR := $(MODULES_DIR)/$(FAMILY)

MAP_FILE             := $(BIN_DIR)/$(TARGET).map
EXE_FILE             := $(BIN_DIR)/$(TARGET).sm8
HEX_FILE             := $(BIN_DIR)/$(TARGET).ihx
BIN_OPT_RESET_FILE   := $(BIN_DIR)/opt_reset.bin
BIN_OPT_UBC_FILE     := $(BIN_DIR)/opt_ubc.bin
BIN_OPT_READ_FILE    := $(BIN_DIR)/opt_read.bin
BIN_EEPROM_READ_FILE := $(BIN_DIR)/eeprom_read.bin
BIN_FLASH_READ_FILE  := $(BIN_DIR)/flash_read.bin

# Verbosity control
ifeq ($(V),1)
Q :=
else
Q := @
endif

# Toolchain abstraction
WINE    ?= wine
CC      := $(WINE) cxstm8
LD      := $(WINE) clnk
OBJCOPY := $(WINE) chex
OBJDUMP := $(WINE) cobj

CFLAGS       = +mods0 -pc99 -l -d$(MCU)
CFLAGS       += -co$(@D) -cl$(@D) -ce$(@D)
CFLAGS       += -i$(INCLUDE_DIR) -i$(MOD_FAMILY_DIR) -i$(SOC_FAMILY_DIR)
LDFLAGS      := -sl -m$(MAP_FILE)
OBJCOPYFLAGS := -fi

SRCS_C        :=
LDSCRIPT      :=
HEX_OPT_UBC   :=
HEX_OPT_RESET :=

include $(SRC_DIR)/Makefile
include $(DRIVERS_DIR)/Makefile
include $(SOC_FAMILY_DIR)/Makefile

# Ensure vector table is linked first
ALL_OBJS := $(SRCS_C:%.c=$(BUILD_DIR)/%.o)
OBJS     := $(filter %vector.o, $(ALL_OBJS)) $(filter-out %vector.o, $(ALL_OBJS))

.PHONY: all
all: init $(HEX_FILE)

$(HEX_FILE): $(EXE_FILE)
	$(Q)$(OBJCOPY) -o $@ $(OBJCOPYFLAGS) $<

$(EXE_FILE): $(OBJS)
	$(Q)$(LD) -o$@ $(LDFLAGS) $(LDSCRIPT) $^

$(BUILD_DIR)/%.o: %.c
	$(Q)mkdir -p $(@D)
	$(Q)$(CC) $(CFLAGS) $<

$(BIN_OPT_RESET_FILE):
	$(Q)echo $(HEX_OPT_RESET) | xxd -r > $@

$(BIN_OPT_UBC_FILE):
	$(Q)echo $(HEX_OPT_UBC) | xxd -r > $@

# User commands
.PHONY: flash
flash:
	$(Q)stm8flash -c $(PROGRAMMER) -p $(PROG_MCU) -w $(HEX_FILE)

.PHONY: opt-reset
opt-reset: init $(BIN_OPT_RESET_FILE)
	$(Q)stm8flash -c $(PROGRAMMER) -p $(PROG_MCU) -s opt -w $(BIN_OPT_RESET_FILE)

.PHONY: opt-ubc
opt-ubc: init $(BIN_OPT_UBC_FILE)
	$(Q)stm8flash -c $(PROGRAMMER) -p $(PROG_MCU) -s opt -w $(BIN_OPT_UBC_FILE)

.PHONY: opt-read
opt-read: init
	$(Q)stm8flash -c $(PROGRAMMER) -p $(PROG_MCU) -s opt -r $(BIN_OPT_READ_FILE)

.PHONY: eeprom-read
eeprom-read: init
	$(Q)stm8flash -c $(PROGRAMMER) -p $(PROG_MCU) -s eeprom -r $(BIN_EEPROM_READ_FILE)

.PHONY: flash-read
flash-read: init
	$(Q)stm8flash -c $(PROGRAMMER) -p $(PROG_MCU) -s flash -r $(BIN_FLASH_READ_FILE)

.PHONY: inspect
inspect:
	$(Q)$(OBJDUMP) $(EXE_FILE)

.PHONY: size
size:
	$(Q)size $(HEX_FILE)

.PHONY: init
init:
	$(Q)mkdir -p $(BIN_DIR) $(BUILD_DIR)

.PHONY: clean
clean:
	$(Q)rm -rf $(BIN_DIR) $(BUILD_DIR)
