# SPDX-FileCopyrightText: 2026 Ralfs K. Vētra
#
# SPDX-License-Identifier: MIT

TARGET      := anchor8

MCU         ?= STM8S103
FAMILY      ?= stm8s

SRC_DIR     := ./src
SOC_DIR     := ./soc
BIN_DIR     := ./bin
BUILD_DIR   := ./build
DRIVERS_DIR := ./drivers
MODULES_DIR := ./modules
INCLUDE_DIR := ./include

MAP_FILE    := $(BIN_DIR)/$(TARGET).map
EXE_FILE    := $(BIN_DIR)/$(TARGET).sm8
HEX_FILE    := $(BIN_DIR)/$(TARGET).ihx

SRCS_C      =
SRCS_S      =
LDSCRIPT    =

include $(SRC_DIR)/Makefile
include $(DRIVERS_DIR)/Makefile
include $(SOC_DIR)/$(FAMILY)/Makefile

OBJS := $(SRCS_C:%.c=$(BUILD_DIR)/%.o) $(SRCS_S:%.s=$(BUILD_DIR)/%.o)

CC      = wine cxstm8
LD      = wine clnk
OBJCOPY = wine chex

CFLAGS       = +mods -pc99 -l -d$(MCU)
CFLAGS       += -co$(@D) -cl$(@D) -ce$(@D)
CFLAGS       += -i$(INCLUDE_DIR) -i$(MODULES_DIR)/$(FAMILY) -i$(SOC_DIR)/$(FAMILY)
LDFLAGS      = -sl -m$(MAP_FILE)
OBJCOPYFLAGS = -fi

.PHONY: all
all: init $(HEX_FILE)

$(HEX_FILE): $(EXE_FILE)
	$(OBJCOPY) -o $@ $(OBJCOPYFLAGS) $<

$(EXE_FILE): $(OBJS)
	$(LD) -o$@ $(LDFLAGS) $(LDSCRIPT)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $<

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $<

.PHONY: init
init:
	@mkdir -p $(BIN_DIR) $(BUILD_DIR)

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
