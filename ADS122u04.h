// ADS122u04.h

#ifndef _ADS122u04_h
#define _ADS122u04_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <YetAnotherPcInt.h>
#include <PinChangeInterruptBoards.h>

//	Pins
#define ADS_DRDY_PIN 50

//	Communication
#define ADS_SYNC_HEAD			0x55
#define DATA_READ_TIMEOUT 100 // ms
//	Commands
#define ADS_RESET_CMD			0x06 // 0b00000110
#define ADS_START_SYNC_CMD		0x08 // 0b00001001
#define ADS_POWERDOWN_CMD		0x03 // 0b00000010
#define ADS_RDATA_CMD			0x10 // 0b00010000

//	Parameters
#define ADS_GAIN 128
#define ADS_VREF 5.0f



void dataInterrupt(char* buff);

class ADS122u04
{
 protected:
	 char inputBuff[3];
	 int inputNum;

	 void sendReset();
	 void sendStartSync();
	 void sendPowerdown();
	 void sendRDATA();
	 void resetDevice();
	 void sendSetInput(int inputNum);
	 bool readData();
	 bool isDataReady();
	 float convertData();
 public:
	void init();


};

extern ADS122u04 ;

#endif

