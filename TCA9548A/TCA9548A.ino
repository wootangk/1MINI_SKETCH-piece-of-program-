#include <Wire.h>
#include "ClosedCube_TCA9548A.h"


#define UART_BAUD 115200
#define TCA9548A_I2C_ADDRESS	0x70

ClosedCube::Wired::TCA9548A tca9548a;

void setup()
{
    Wire.begin();
    Serial.begin(UART_BAUD);
    
    Serial.println("ClosedCube TCA9548A Channel Scanner Demo");

    tca9548a.address(TCA9548A_I2C_ADDRESS);

	uint8_t returnCode = 0;
	uint8_t address;
	uint8_t numberOfDevices;

    for( uint8_t channel=0; channel<TCA9548A_MAX_CHANNELS; channel++ ) {
    	Serial.print("Scanning channel #");
    	Serial.print(channel);
    	Serial.println("...");

		returnCode = tca9548a.selectChannel(channel);
		numberOfDevices = 0;

    	if( returnCode == 0 ) {
    		for(address = 0x01; address < 0x7F; address++ ) {
    			Wire.beginTransmission(address);
    			returnCode = Wire.endTransmission();
 
    			if (returnCode == 0) {
      				Serial.print("I2C device = ");
					printAddress(address);
 
      				numberOfDevices++;
    			} else if ( returnCode == 4) {
      				Serial.print("Unknown error at ");
      				printAddress(address);
    			}    
			  }
			  if (numberOfDevices == 0)
			    Serial.println("No I2C devices found\n");
    	} else {
    		Serial.print("Error scan channel (Code:");
    		Serial.print(returnCode);
    		Serial.println(")");
    	}
    }

}

void printAddress(uint8_t address)  {
	Serial.print("0x");
	if (address<0x10) {
		Serial.print("0");
	}
	Serial.println(address,HEX);
}

void loop()
{
	// do nothing here
}