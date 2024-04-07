##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [4.3.0-B58] date: [Mon Apr 01 21:20:42 CEST 2024] 
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = misko3-tetris


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Core/Src/main.c \
Core/Src/gpio.c \
Core/Src/adc.c \
Core/Src/crc.c \
Core/Src/dac.c \
Core/Src/fdcan.c \
Core/Src/fmc.c \
Core/Src/i2c.c \
Core/Src/quadspi.c \
Core/Src/spi.c \
Core/Src/tim.c \
Core/Src/usart.c \
Core/Src/tetromino.c \
Core/Src/joystick.c \
Core/Src/stm32g4xx_it.c \
Core/Src/stm32g4xx_hal_msp.c \
Core/Src/tetris_game.c \
USB_Device/App/usb_device.c \
USB_Device/App/usbd_desc.c \
USB_Device/App/usbd_cdc_if.c \
USB_Device/Target/usbd_conf.c \
System/buf.c \
System/kbd.c \
System/LED.c \
System/SCI.c \
Drivers/external/lcd_demo.c \
Drivers/external/lcd_grafika.c \
Drivers/external/lcd_ili9341.c \
Drivers/external/lcd.c \
Drivers/external/ugui.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pcd.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pcd_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ramfunc.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_gpio.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_exti.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_cortex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_adc.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_adc_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_crc.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_crc_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dac.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dac_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_fdcan.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_sram.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_i2c.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_i2c_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_qspi.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_spi.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_spi_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart_ex.c \
Drivers/STM32G4xx_LL_Driver/Src/stm32g4xx_ll_usb.c \
Drivers/STM32G4xx_LL_Driver/Src/stm32g4xx_ll_adc.c \
Drivers/STM32G4xx_LL_Driver/Src/stm32g4xx_ll_fmc.c \
Drivers/STM32G4xx_LL_Driver/Src/stm32g4xx_ll_tim.c \
Drivers/STM32G4xx_LL_Driver/Src/stm32g4xx_ll_dma.c \
Drivers/STM32G4xx_LL_Driver/Src/stm32g4xx_ll_usart.c \
Drivers/STM32G4xx_LL_Driver/Src/stm32g4xx_ll_rcc.c \
Drivers/STM32G4xx_LL_Driver/Src/stm32g4xx_ll_utils.c \
Drivers/STM32G4xx_LL_Driver/Src/stm32g4xx_ll_exti.c \
Drivers/STM32G4xx_LL_Driver/Src/stm32g4xx_ll_gpio.c \
Core/Src/system_stm32g4xx.c \
Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c \
Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c \
Core/Src/sysmem.c \
Core/Src/syscalls.c \
Core/Src/dma.c

# ASM sources
ASM_SOURCES =  \
startup_stm32g474xx.s

# ASM sources
ASMM_SOURCES = 


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_FULL_LL_DRIVER \
-DUSE_HAL_DRIVER \
-DSTM32G474xx


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-ICore/Inc \
-IUSB_Device/App \
-IUSB_Device/Target \
-IDrivers/external \
-ISystem/Include \
-IDrivers/STM32G4xx_HAL_Driver/Inc \
-IDrivers/STM32G4xx_HAL_Driver/Inc/Legacy \
-IDrivers/STM32G4xx_LL_Driver/Inc \
-IMiddlewares/ST/STM32_USB_Device_Library/Core/Inc \
-IMiddlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc \
-IDrivers/CMSIS/Device/ST/STM32G4xx/Include \
-IDrivers/CMSIS/Include \
-IMiddlewares/Third_Party/FreeRTOS/Source/include \
-IMiddlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 \
-IMiddlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32G474QETx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# Color definitions
RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
NC = \033[0m



# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
	@echo "${GREEN}Build sucessful!${NC}" || echo -e "${RED}Build failed!${NC}"


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASMM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASMM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@
$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	@-rm -fR $(BUILD_DIR) && \
	echo "-rm -fR $(BUILD_DIR)" && \
	echo "${BLUE}\nClean sucessful!${NC}"
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***

device = STM32G4XX 

stflash: $(BUILD_DIR)/$(TARGET).bin
	st-flash --reset write $(BUILD_DIR)/$(TARGET).bin 0x08000000 && \
	(echo "${GREEN}\nFlash sucessful!${NC}") || \
	(echo "${RED}\nFlash failed!${NC}")