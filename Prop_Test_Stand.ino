// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Prop_Test_Stand.ino
    Created:	07.10.2021 15:09:58
    Author:     DESKTOP-SSQPK6R\mpods
*/

// Define User Types below here or use a .h file
//

#include <YetAnotherPcInt.h>
#include <PinChangeInterruptBoards.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include "ADS122u04.h"



// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//
ADS122u04 ads;

// The setup() function runs once each time the micro-controller starts
void setup()
{
    Serial.begin(19200);
    ads.init();
}

// Add the main program code into the continuous loop() function
void loop()
{
    Serial.println(ads.getInputVoltage(0), 9);
    delay(500);

}
