// ADS122u04.h

#ifndef _ADS122u04_h
#define _ADS122u04_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//	Pins
#define ADS_DRDY_PIN 50

// Communication
#define ADS_SYNC_HEAD			0x55
//	Commands
#define ADS_RESET_CMD			0x06 // 0b00000110
#define ADS_START_SYNC_CMD		0x08 // 0b00001001
#define ADS_POWERDOWN_CMD		0x03 // 0b00000010
#define ADS_RDATA_CMD			0x10 // 0b00010000
//#define ADS_RREG_CMD 0b0010 //RRRX next register and last do not matters
//#define ADS_WREG_CMD 0b0100 //RRRXnext register and last do not matters



class ADS122u04
{
 protected:
	 void sendReset();
	 void sendStartSync();
	 void sendPowerdown();
	 void sendRDATA();
	 void resetDevice();
	 void setRegisters();

 public:
	void init();
	double readSingleRAW();

};

extern ADS122u04 ;

#endif

