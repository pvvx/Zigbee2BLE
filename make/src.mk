
OUT_DIR += $(SRC_DIR) \
$(SRC_DIR)/custom_zcl \
$(SRC_DIR)/common \
$(SRC_DIR)/patch_sdk

OBJS += \
$(OUT_PATH)$(SRC_DIR)/app_ui.o \
$(OUT_PATH)$(SRC_DIR)/concurrent_main.o \
$(OUT_PATH)$(SRC_DIR)/sampleGateway.o \
$(OUT_PATH)$(SRC_DIR)/sampleGatewayEpCfg.o \
$(OUT_PATH)$(SRC_DIR)/sampleGwBLESlave_8258.o \
$(OUT_PATH)$(SRC_DIR)/zb_afTestCb.o \
$(OUT_PATH)$(SRC_DIR)/zb_appCb.o \
$(OUT_PATH)$(SRC_DIR)/zcl_sampleGatewayCb.o \
$(OUT_PATH)$(SRC_DIR)/custom_zcl/zcl_relative_humidity.o \
$(OUT_PATH)$(SRC_DIR)/common/zigbee_ble_switch.o \
$(OUT_PATH)$(SRC_DIR)/common/factory_reset.o \
$(OUT_PATH)$(SRC_DIR)/patch_sdk/drv_flash.o \
$(OUT_PATH)$(SRC_DIR)/patch_sdk/drv_hw.o \
$(OUT_PATH)$(SRC_DIR)/bthome_beacon.o
 

# Each subdirectory must supply rules for building sources it contributes
$(OUT_PATH)$(SRC_DIR)/%.o: $(PROJECT_PATH)$(SRC_DIR)/%.c
	@echo 'Building file: $<'
	@$(TC32_PATH)tc32-elf-gcc $(GCC_FLAGS) $(INCLUDE_PATHS) -c -o"$@" "$<"