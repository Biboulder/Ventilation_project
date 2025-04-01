################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/paho.mqtt.embedded-c/MQTTClient-C/src/MQTTClient.c 

OBJS += \
./src/paho.mqtt.embedded-c/MQTTClient-C/src/MQTTClient.o 

C_DEPS += \
./src/paho.mqtt.embedded-c/MQTTClient-C/src/MQTTClient.d 


# Each subdirectory must supply rules for building sources it contributes
src/paho.mqtt.embedded-c/MQTTClient-C/src/%.o: ../src/paho.mqtt.embedded-c/MQTTClient-C/src/%.c src/paho.mqtt.embedded-c/MQTTClient-C/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -DMQTTCLIENT_PLATFORM_HEADER=MQTT_lpc1549.h -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\lpc_chip_15xx\inc" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\ventilation_project\src\paho.mqtt.embedded-c\MQTTClient-C\src" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\ventilation_project\src\paho.mqtt.embedded-c\MQTTPacket\src" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\ventilation_project\src" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\ventilation_project\src\modbus" -I"C:\Users\MiroT\Documents\MCUXpressoIDE_11.5.1_7266\EmbeddedSystemsProgramming\ventilation_project\src\mqtt" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


