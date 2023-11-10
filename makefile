
PROJECT_NAME ?= zb2ble

TEL_CHIP := -DMCU_CORE_8258=1 -DCOORDINATOR=1 -DBLE_CONCURRENT_MODE=1 -DMCU_STARTUP_8258 -DBOOT_LOADER_MODE=0 -D__PROJECT_TL_GW__

LIBS := -ldrivers_8258 -lzb_coordinator -lble_8258

PGM_PORT?=COM4

PROJECT_PATH ?= .
SRC_DIR ?= /src
SRC_PATH ?= $(PROJECT_PATH)$(SRC_DIR)
# TEL_PATH:  Telink SDK - tc32/bin/
TEL_PATH ?= .
# SDK_PATH: X:/Telink/tl_zigbee_sdk
SDK_PATH ?= ./SDK
# MAKE_PATH: project all make
MAKE_PATH ?= ./make

LS_FLAGS := ./boot.link

OUT_PATH ?=./out

PYTHON ?= python3

OBJ_SRCS :=
S_SRCS :=
ASM_SRCS :=
C_SRCS :=
S_UPPER_SRCS :=
O_SRCS :=
FLASH_IMAGE :=
ELFS :=
OBJS :=
LST :=
SIZEDUMMY :=
OUT_DIR :=

COMPILEOS = $(shell uname -o)
LINUX_OS = GNU/Linux

ifeq ($(COMPILEOS),$(LINUX_OS))
	TOOLS_PATH := $(TEL_PATH)/tools/linux
	TC32_PATH := $(TOOLS_PATH)/tc32/bin/
	TST_FILE := tc32-elf-ld
	CUR_OS := linux
else
	TOOLS_PATH := $(TEL_PATH)/tools/windows
	TST_FILE := tc32-elf-ld.exe
	CUR_OS := windows
ifeq ($(TOOLS_PATH)tc32/bin/tc32-elf-gcc.exe, $(wildcard $(TOOLS_PATH)tc32/bin/tc32-elf-gcc.exe))
	TC32_PATH := $(TOOLS_PATH)/tc32/bin/
else
	TC32_PATH :=
endif
endif

#LNK_FLAG := -Wl,-nostartfiles -Wl,-nostdlib -Wl,--gc-sections -Wl,-uss_apsmeSwitchKeyReq -fshort-enums -nostartfiles -fno-rtti -fno-exceptions -fno-use-cxa-atexit -fno-threadsafe-statics

LNK_FLAGS := --gc-sections -uss_apsmeSwitchKeyReq -nostartfiles

GCC_FLAGS := \
-O2 \
-ffunction-sections \
-fdata-sections \
-Wall \
-fpack-struct \
-fshort-enums \
-finline-small-functions \
-std=gnu99 \
-funsigned-char \
-fshort-wchar \
-fms-extensions \
-nostartfiles \
-nostdlib

ASM_FLAGS := \
-fomit-frame-pointer \
-fshort-enums \
-Wall \
-Wpacked \
-Wcast-align \
-fdata-sections \
-ffunction-sections \
-fno-use-cxa-atexit \
-fno-rtti \
-fno-threadsafe-statics

INCLUDE_PATHS := -I$(SRC_PATH) -I$(SRC_PATH)/patch_sdk -I$(SRC_PATH)/common -I$(SRC_PATH)/custom_zcl \
-I$(SDK_PATH) \
-I$(SDK_PATH)/platform \
-I$(SDK_PATH)/proj \
-I$(SDK_PATH)/proj/common \
-I$(SDK_PATH)/stack/ble_8258 


GCC_FLAGS += $(TEL_CHIP)

LS_INCLUDE := -L$(SDK_PATH)/platform/lib -L$(SDK_PATH)/stack/ble/lib -L$(SDK_PATH)/stack/zigbee/lib/tc32 -L$(SDK_PATH)/proj -L$(SDK_PATH)/platform -L$(OUT_PATH)

#include Project makefile
-include $(MAKE_PATH)/src.mk
#include SDK makefile
-include $(MAKE_PATH)/platform.mk
-include $(MAKE_PATH)/proj.mk
-include $(MAKE_PATH)/zigbee.mk
-include $(MAKE_PATH)/zbhci.mk

# Add inputs and outputs from these tool invocations to the build variables
LST_FILE := $(OUT_PATH)/$(PROJECT_NAME).lst
BIN_FILE := $(OUT_PATH)/$(PROJECT_NAME).bin
ELF_FILE := $(OUT_PATH)/$(PROJECT_NAME).elf

SIZEDUMMY := sizedummy

# All Target
all: pre-build main-build

# Main-build Target
main-build: $(ELF_FILE) secondary-outputs

OBJ_LIST := $(OBJS) $(USER_OBJS)
# Tool invocations
$(ELF_FILE): $(OBJ_LIST)
	@echo 'Building Standard target: $@'
	@$(TC32_PATH)tc32-elf-ld $(LNK_FLAGS) $(LS_INCLUDE) -T$(LS_FLAGS) -o $(ELF_FILE) $(OBJ_LIST) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

$(LST_FILE): $(ELF_FILE)
	@echo 'Invoking: TC32 Create Extended Listing'
	@$(TC32_PATH)tc32-elf-objdump -x -D -l -S  $(ELF_FILE)  > $(LST_FILE)
	@echo 'Finished building: $@'
	@echo ' '

$(BIN_FILE): $(ELF_FILE)
	@echo 'Create Flash image (binary format)'
	@echo ' '
	@$(TC32_PATH)tc32-elf-objcopy -v -O binary $(ELF_FILE) $(BIN_FILE)
	@echo ' '
	@$(PYTHON) $(MAKE_PATH)/tl_check_fw.py $(BIN_FILE)
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: $(ELF_FILE)
	@$(PYTHON) $(MAKE_PATH)/TlsrMemInfo.py -t $(TC32_PATH)tc32-elf-nm $(ELF_FILE)
	@echo ' '

clean:
	@$(RM) $(FLASH_IMAGE) $(ELFS) $(OBJS) $(LST) $(SIZEDUMMY) $(ELF_FILE) $(BIN_FILE) $(LST_FILE)
	@echo 'Clean ...'
	@echo ' '

pre-build:
ifneq ($(SDK_PATH)/stack/zigbee, $(wildcard $(SDK_PATH)/stack/zigbee))
	$(error "Please check SDK_PATH")
endif
	@mkdir -p $(foreach s,$(OUT_DIR),$(OUT_PATH)$(s))
	@echo ' '


secondary-outputs: $(BIN_FILE) $(LST_FILE) $(SIZEDUMMY)


flash: $(BIN_FILE)
	@$(PYTHON) $(MAKE_PATH)/TlsrPgm.py -p$(PGM_PORT) -t50 -a500 -s fsw 0
	@$(PYTHON) $(MAKE_PATH)/TlsrPgm.py -p$(PGM_PORT) we 0 $(BIN_FILE)
	@$(PYTHON) $(MAKE_PATH)/TlsrPgm.py -p$(PGM_PORT) -w -m i

reset:
	@$(PYTHON) $(MAKE_PATH)/TlsrPgm.py -p$(PGM_PORT) -t50 -a500 -m -w i

erase:
	@$(PYTHON) $(MAKE_PATH)/TlsrPgm.py -p$(PGM_PORT) -t50 -a500 -s ea

info:
	@$(PYTHON) $(MAKE_PATH)/TlsrPgm.py -p$(PGM_PORT) -z11 i

stop:
	@$(PYTHON) $(MAKE_PATH)/TlsrPgm.py -p$(PGM_PORT) -a500 -s i

go:
	@$(PYTHON) $(MAKE_PATH)/TlsrPgm.py -p$(PGM_PORT) -w -m

TADDR?=0x08425e0
TLEN?=128
test_damp:
	@$(PYTHON) $(MAKE_PATH)/TlsrPgm.py -p$(PGM_PORT) -z10 -c -g ds $(TADDR) $(TLEN)

get_mac:
	@$(PYTHON) $(MAKE_PATH)/TlsrPgm.py -p$(PGM_PORT) -z10 -c -g df 0x76000 16

install: $(TC32_PATH)$(TST_FILE)
	@echo "SDK & TC32 installed. Use: make all"


$(TC32_PATH)$(TST_FILE): $(TOOLS_PATH)
ifneq ($(TC32_PATH)$(TST_FILE), $(wildcard $(TC32_PATH)$(TST_FILE)))
	git clone https://github.com/devbis/tc32.git -b $(CUR_OS) $(TOOLS_PATH)/tc32
endif

$(TOOLS_PATH):
	mkdir -p $(TOOLS_PATH)


.PHONY: all clean
.SECONDARY: main-build