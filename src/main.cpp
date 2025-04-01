/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
 */

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include <cstdio>
#include <cstring>
#include "systick.h"
#include "LpcUart.h"
#include "esp8266_socket.h"
#include "retarget_uart.h"
#include "ModbusMaster.h"
#include "ModbusRegister.h"
#include "MQTTClient.h"
#include "DigitalIoPin.h"
#include "LiquidCrystal.h"
#include "I2C.h"



#define SSID	    "SmartIotMQTT"
#define PASSWORD    "SmartIot"
#define BROKER_IP   "192.168.1.254"
#define BROKER_PORT  1883


#if defined(BOARD_NXP_LPCXPRESSO_1549)
/** 7-bit I2C addresses of Temperature Sensor */
#define I2C_PRESSURE_ADDR_7BIT  (0x40)
#endif

#define ALTITUDE_CORRECTION 0.95
#define SCALE_FACTOR 230
#define RUNNING_AVERAGE_COUNT 10.0

enum Mode { manual, automatic, debug };

// TODO: insert other definitions and declarations here
static volatile int counter;
static volatile uint32_t systicks;

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	systicks++;
	if(counter > 0) counter--;
}

uint32_t get_ticks(void)
{
	return systicks;
}

#ifdef __cplusplus
}
#endif

void Sleep(int ms)
{
	counter = ms;
	while(counter > 0) {
		__WFI();
	}
}

/* this function is required by the modbus library */
uint32_t millis() {
	return systicks;
}

char* renderBar(int value, int maxValue, int length) {
	// We use malloc to allocate the string on the heap
	char* bars = (char*)malloc((length+1)*sizeof(char));
	int i = 0;
	for(i = 0; i < length; i++) bars[i] = '_';
	bars[i] = '\0';

	if(value <= 0 || maxValue <= 0) return bars;

	int barCount = ((float)value / (float)maxValue) * length;

	for(i = 0; i < length; i++) {
		if(i < barCount) bars[i] = '\xff';
	}
	bars[i] = '\0';

	return bars;
}

bool blockingBtnRead(DigitalIoPin* btn, int debounce_ms, int max_debounces) {
	if(btn->read()) {
		for(int i = 0; i < max_debounces && btn->read(); i++) {
			Sleep(debounce_ms);
		}
		return true;
	}
	return false;
}

void clampFanSpeed(int* fanSpeed) {
	if(*fanSpeed < 0) *fanSpeed = 0;
	if(*fanSpeed > 1000) *fanSpeed = 1000;
}

int main(void) {
	SystemCoreClockUpdate();
	Board_Init();
	Board_LED_Set(0, true);

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(SystemCoreClock / 1000);

	I2C_config cfg;
	I2C i2c(cfg);

	/* Disable the interrupt for the I2C */
	NVIC_DisableIRQ(I2C0_IRQn);

	printf("\nBoot\n");

	DigitalIoPin *rs = new DigitalIoPin(0, 29, DigitalIoPin::output);
	DigitalIoPin *en = new DigitalIoPin(0, 9, DigitalIoPin::output);
	DigitalIoPin *d4 = new DigitalIoPin(0, 10, DigitalIoPin::output);
	DigitalIoPin *d5 = new DigitalIoPin(0, 16, DigitalIoPin::output);
	DigitalIoPin *d6 = new DigitalIoPin(1, 3, DigitalIoPin::output);
	DigitalIoPin *d7 = new DigitalIoPin(0, 0, DigitalIoPin::output);
	LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

	DigitalIoPin modeBtn(0, 7, DigitalIoPin::pullup, true);
	DigitalIoPin leftBtn(1, 8, DigitalIoPin::pullup, true);
	DigitalIoPin rightBtn(0, 5, DigitalIoPin::pullup, true);

	// configure display geometry
	lcd.begin(16, 2);
	// set the cursor to column 0, line 1
	// (note: line 1 is the second row, since counting begins with 0):
	lcd.setCursor(0, 0);
	// Print a message to the LCD.
	lcd.print(SSID);
	lcd.setCursor(0, 1);
	lcd.print(BROKER_IP);


	ModbusMaster fanNode(1);
	ModbusMaster co2Node(240);
	ModbusMaster tempAndHumidNode(241);

	fanNode.begin(9600);
	co2Node.begin(9600);
	tempAndHumidNode.begin(9600);

	ModbusRegister fanBus(&fanNode, 0);
	ModbusRegister temperatureBus(&tempAndHumidNode, 257, true);
	ModbusRegister co2Bus(&co2Node, 256, true);
	ModbusRegister humidityBus(&tempAndHumidNode, 256, true);

	lcd.clear();

	int targetPascals = 120;
	int fanSpeed = 0;

	Mode mode = debug;

	unsigned long long i = 0;

	uint16_t temperature = 0;
	uint16_t co2 = 0;
	uint16_t humidity = 0;

	float pressure_avg = 0;
	bool pressure_avg_init = false;

	while(true) {

		//Sleep between modbus reads, totaling 20ms
		temperature = temperatureBus.read()/10;
		Sleep(7);
		co2 = co2Bus.read();
		Sleep(7);
		humidity = humidityBus.read()/10;
		Sleep(6);

		struct pressureData {
			uint8_t data[2];
			uint8_t crc;
		} pressureData;

		uint8_t press_r_cmd = 0xf1;
		i2c.transaction(I2C_PRESSURE_ADDR_7BIT, &press_r_cmd, 1, (uint8_t*)&pressureData, 3);
		int16_t pressure = (pressureData.data[0] << 8) + pressureData.data[1];
		pressure = pressure * ALTITUDE_CORRECTION / SCALE_FACTOR;

		char lcdLine1[17] = "";
		char lcdLine2[17] = "";

		if(blockingBtnRead(&modeBtn, 10, 10000)) {
			if(mode == manual) mode = automatic;
			else if(mode == automatic) mode = debug;
			else if(mode == debug) mode = manual;
		}

		if(!pressure_avg_init) {
			pressure_avg = pressure;
			pressure_avg_init = true;
		}

		pressure_avg -= (float)pressure_avg / RUNNING_AVERAGE_COUNT;
		pressure_avg += (float)pressure / RUNNING_AVERAGE_COUNT;

		if(mode == automatic) {
			if(blockingBtnRead(&leftBtn, 10, 10)) targetPascals--;
			if(blockingBtnRead(&rightBtn, 10, 10)) targetPascals++;
			if(targetPascals < 0) targetPascals = 0;
			if(targetPascals > 120) targetPascals = 120;

			// If the delta is large we change the fan speed by a lot
			// Else we change it by less
			// This allows the system to be both responsive and stable
			int delta = targetPascals - pressure;
			int fanChange = delta/7;
			if(fanChange == 0  && delta != 0) {
				if(delta < 0) fanChange = -1;
				if(delta > 0) fanChange = +1;
			}
			fanSpeed += fanChange;

			if(targetPascals <= 0) fanSpeed = 0;

			clampFanSpeed(&fanSpeed);

			char* bars = renderBar(targetPascals, 120, 14);
			snprintf(lcdLine1, 17, "%s:A", bars);
			snprintf(lcdLine2, 17, "%3.0fPa Goal:%3dPa", pressure_avg, targetPascals);
			free(bars);
		}
		else if (mode == manual) {
			if(blockingBtnRead(&leftBtn, 10, 10)) fanSpeed-=10;
			if(blockingBtnRead(&rightBtn, 10, 10)) fanSpeed+=10;

			clampFanSpeed(&fanSpeed);

			char* bars = renderBar(fanSpeed, 1000, 14);
			snprintf(lcdLine1, 17, "%s:M", bars);
			snprintf(lcdLine2, 17, "%3d%%rpm %3.0fPa", fanSpeed/10, pressure_avg);
			free(bars);
		}
		else if (mode == debug) {
			snprintf(lcdLine1, 17, "%3d\xdf""C %3d%%RH       ", temperature, humidity);
			snprintf(lcdLine1, 17, "%.15sD", lcdLine1);
			snprintf(lcdLine2, 17, "%4dppm %3dPa", co2, pressure);
		}


		fanBus.write(fanSpeed);

		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(lcdLine1);
		lcd.setCursor(0, 1);
		lcd.print(lcdLine2);

		i++;
	}


	// Enter an infinite loop, just incrementing a counter
	while(1) {
		// "Dummy" NOP to allow source level single
		// stepping of tight while() loop
		__asm volatile ("nop");
	}
	return 0 ;

}
