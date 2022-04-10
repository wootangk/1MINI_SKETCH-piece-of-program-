#include <Arduino.h>
#include <TM1637Display.h>
#include "RTClib.h"
// Module connection pins (Digital Pins)
#define CLK 27
#define DIO 26
#include "ClosedCube_TCA9548A.h"
// The amount of time (in milliseconds) between tests
//#define TEST_DELAY   2000

ClosedCube::Wired::TCA9548A tca9548a;

TM1637Display display(CLK, DIO);
RTC_DS3231 rtc;
void TCA9548A(uint8_t bus) //function of TCA9548A
{
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}
void setup()
{
Serial.begin(115200);
 TCA9548A(7);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  Serial.println(displaytime);
 DateTime now = rtc.now();
}

void loop()
{
   int displaytime = (now.hour() * 100) + now.minute();

  Serial.println(displaytime);

  display.showNumberDecEx(displaytime, 0b11100000, true);

  delay(1000);

  display.showNumberDec(displaytime, true);
}