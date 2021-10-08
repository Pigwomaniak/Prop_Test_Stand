// 
// 
// 

#include "ADS122u04.h"

void ADS122u04::sendReset()
{
	Serial2.write(ADS_SYNC_HEAD);
	Serial2.write(ADS_RESET_CMD);
	delay(10);
}

void ADS122u04::sendStartSync()
{
	Serial2.write(ADS_SYNC_HEAD);
	Serial2.write(ADS_START_SYNC_CMD);
}

void ADS122u04::sendPowerdown()
{
	Serial2.write(ADS_SYNC_HEAD);
	Serial2.write(ADS_POWERDOWN_CMD);
}

void ADS122u04::sendRDATA()
{
	Serial2.write(ADS_SYNC_HEAD);
	Serial2.write(ADS_RDATA_CMD);
}

void ADS122u04::resetDevice()
{
	// Set conversion mode
	// Set data rate
	sendReset();
	/*
	REGISTER 0: 7 : 4 Input multiplexer(0000 : AINP = AIN0, AINN = AIN1); 3:1 gains(000 : Gain = 128); 0 disable PGA bypas(0 : PGA enabled(default))
	*/
	Serial2.write(ADS_SYNC_HEAD);
	Serial2.write(0b00100000); // reg number
	Serial2.write(0b00001110); // reg value
	/*
	REGISTER 1: 7 : 5 Data rate(000 = 20 SPS); 4 mode(0 : Normal mode(256 - kHz modulator clock, default)); 3 conversion mode(0 : Single - shot conversion mode(default));
	2:1 VREF (01 : External reference selected using the REFP and REFN inputs); 0 temperature sensor (0 : Temperature sensor mode disabled (default))
	*/
	Serial2.write(ADS_SYNC_HEAD);
	Serial2.write(0b00100010); // reg number
	Serial2.write(0b00000010); // reg value
	/*
	REGISTER 2: 
	*/
	Serial2.write(ADS_SYNC_HEAD);
	Serial2.write(0b00100100); // reg number
	Serial2.write(0b00000000); // reg value
	/*
	REGISTER 3:
	*/
	Serial2.write(ADS_SYNC_HEAD);
	Serial2.write(0b00100110); // reg number
	Serial2.write(0b00000000); // reg value
	/*
	REGISTER 4:
	*/
	Serial2.write(ADS_SYNC_HEAD);
	Serial2.write(0b00101000); // reg number
	Serial2.write(0b01001000); // reg value
}

void ADS122u04::sendSetInput(int input)
{
	Serial2.write(ADS_SYNC_HEAD);
	Serial2.write(0b00100000); // reg number
	if (input)
	{
		Serial2.write(0b01101110); // reg value 0110 : AINP = AIN2, AINN = AIN3
	}
	else
	{
		Serial2.write(0b00001110); // reg value 0000 : AINP = AIN0, AINN = AIN1 (default)
	}
	inputNum = input;
}

bool ADS122u04::readData()
{
	PcInt::attachInterrupt(ADS_DRDY_PIN, dataInterrupt, inputBuff, RISING, false);
	sendRDATA();
	unsigned long time = millis();
	while (!isDataReady())
	{
		if (millis() - time > DATA_READ_TIMEOUT)
		{
			Serial.println("Data Read timeout");
			return 0;
		}
		delay(1);
	}
	return 1;
}

bool ADS122u04::isDataReady()
{
	return digitalRead(ADS_DRDY_PIN);
}

float ADS122u04::convertData()
{
	if (!readData())
	{
		return 0.0f;
	}
	unsigned long rawData = 0;
	rawData = ((((rawData + inputBuff[0]) << 8) + inputBuff[1]) << 8) + inputBuff[2];
	float lsb = (2 * ADS_VREF / ADS_GAIN) / pow(2,23);

	return (lsb * rawData);
}

void ADS122u04::init()
{
	pinMode(ADS_DRDY_PIN, INPUT);
	Serial2.begin(19200);
	resetDevice();
	inputNum = 0;

}


ADS122u04 ;

void dataInterrupt(char* buff)
{
	Serial2.readBytes(buff, 3);
	PcInt::detachInterrupt(ADS_DRDY_PIN);
}
