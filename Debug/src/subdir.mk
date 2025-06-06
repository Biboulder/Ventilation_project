################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DigitalIoPin.cpp \
../src/I2C.cpp \
../src/LiquidCrystal.cpp \
../src/LpcUart.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc15xx.cpp \
../src/main.cpp \
../src/retarget_uart.cpp 

C_SRCS += \
../src/crp.c \
../src/sysinit.c 

OBJS += \
./src/DigitalIoPin.o \
./src/I2C.o \
./src/LiquidCrystal.o \
./src/LpcUart.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc15xx.o \
./src/crp.o \
./src/main.o \
./src/retarget_uart.o \
./src/sysinit.o 

CPP_DEPS += \
./src/DigitalIoPin.d \
./src/I2C.d \
./src/LiquidCrystal.d \
./src/LpcUart.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc15xx.d \
./src/main.d \
./src/retarget_uart.d 

C_DEPS += \
./src/crp.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -DMQTTCLIENT_PLATFORM_HEADER=MQTT_lpc1549.h -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\lpc_chip_15xx\inc" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\ventilation_project\src\paho.mqtt.embedded-c\MQTTClient-C\src" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\ventilation_project\src\paho.mqtt.embedded-c\MQTTPacket\src" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\ventilation_project\src" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\ventilation_project\src\modbus" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\ventilation_project\src\mqtt" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -DMQTTCLIENT_PLATFORM_HEADER=MQTT_lpc1549.h -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\lpc_chip_15xx\inc" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\ventilation_project\src\paho.mqtt.embedded-c\MQTTClient-C\src" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\ventilation_project\src\paho.mqtt.embedded-c\MQTTPacket\src" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\ventilation_project\src" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\ventilation_project\src\modbus" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\ventilation_project\src\mqtt" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


