

  #include <ADS1256.h>
  #include <Arduino.h>
  #include <LiquidCrystal_I2C.h> //Library for I2C lcd
  #include <OneWire.h> //One wire library
  #include <DallasTemperature.h> //Library for DS18B20 Sensor
  #include <math.h>// Library for math function 
  #include <pcf8574_esp.h>

  /*  We need to set up the I2C-bus for the library to use */
  #include <Wire.h>
//Header Declearation End
#define ONE_WIRE_BUS 15 //data pin  DQ pin of DS18B20 connected to digital pin D5
  float Etemp = 22; //convert milli volt to temperature degree Celsius
  float Wtemp = 22;
  //Pin Assignment and declearation Start
  OneWire oneWire(ONE_WIRE_BUS); //Ste up one wire instance
  DallasTemperature sensors(&oneWire); //pass one wire reference to DS18B20 library
  DeviceAddress sensor1 = { 0x28, 0x52, 0x37, 0x14, 0x64, 0x20, 0x1, 0x19 };
  DeviceAddress sensor2 = { 0x28, 0x63, 0xFD, 0x7, 0x64, 0x20, 0x1, 0xEC };



 
 float sensorValue = 0 ;
float tdsValue = 0 ;
  float Voltage ;
  float pHValue ;
  long phTot;   //, temTot
  float phAvg; //, temAvg
  int x;
  const float C = 16.96; //Constant of straight line (Y = mx + C)pH = a*xV + b
  //4,01 = a*(3,04)+b
  //6,86 = a*(2,54)+b
  //Тогда я получаю результат y = -5,7*21338.
  const float m = -4.35; // Slope of straight line (Y = mx + C)
  //Pin Assignment and declearation end


boolean LEDflag = false;
// переменные времени
uint32_t myTimer, myTimer1, myTimer2;
uint32_t myTimer3;

ADS1256 ads;
//Header declearation Start

LiquidCrystal_I2C lcd(0x27,20,4);  //set the LCD address to 0x27 for a 20 chars and 4 line display
  // start for generate custom character
  byte customChar[] = {
    B00100,
    B00100,
    B11111,
    B00100,
    B00100,
    B00000,
    B11111,
    B00000
  };
  //End for generate custom character


// Initialize a PCF8574 at I2C-address 0x20
  PCF857x pcf1(0x22, &Wire);
  PCF857x pcf2(0x24, &Wire);
  //If you had a PCF8575 instead you'd use the below format
  //PCF857x pcf8575(0x20, &Wire, true);
  volatile bool PCFInterruptFlag = false;

  void PCFInterrupt() {
    PCFInterruptFlag = true;
  }


//Setup Function Start 
void setup() {

 
Wire.begin();
 Wire.setClock(100000L);
  pcf1.begin();
  pcf1.resetInterruptPin();
  pcf2.begin();
  pcf2.resetInterruptPin();
//  pcf2.write(0, 1);
lcd.begin(); //initialization the lcd
  lcd.backlight(); 
  sensors.begin(); //Start the DS18B20 Library
  lcd.setCursor(0,0);
  lcd.print("PH and Temperature");
  lcd.setCursor(0,1);
  lcd.print("Meter Using");
  lcd.setCursor(0, 2);
  lcd.print("Arduino");
  delay(3000);
  lcd.clear();
  Serial.begin( 115200 );
  ads.init( 5, 14, 25, 1700000 );
  Serial.println( ads.speedSPI );

// pcf1.write(0, 1);
//   pcf1.write(1, 0);
//   pcf1.write(2, 1);
//   pcf1.write(3, 0);
//   pcf1.write(4, 0);
//   pcf1.write(5, 1);
//   pcf1.write(6, 0);
//   pcf1.write(7, 1);
//     pcf2.write(0, 1);
//       pcf2.write(1, 0);
//       pcf2.write(2, 1);
//       pcf2.write(3, 0);
//       pcf2.write(4, 0);
//       pcf2.write(5, 1);
//       pcf2.write(6, 0);
//       pcf2.write(7, 1);

  

  
  
}
//Setup Function End

//Main function Start
void loop() {
 
 // каждую секунду
  if (millis() - myTimer >= 1000) {
    //myTimer = millis(); // сбросить таймер
    digitalWrite(13, LEDflag); // вкл/выкл
    LEDflag = !LEDflag; // инвертировать флаг
    // lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Env.Tmp.");
    lcd.setCursor(12,0);
    lcd.print("Wat.Tmp.");
    lcd.setCursor(1,1);
    lcd.print(Etemp);
    lcd.setCursor(6,1);
    lcd.write(B11011111);
    lcd.setCursor(7,1);
    lcd.print("C");
    lcd.setCursor(13,1);
    lcd.print(Wtemp);
    lcd.setCursor(18,1);
    lcd.write(B11011111);
    lcd.setCursor(19,1);
    lcd.print("C");
    lcd.setCursor(0,2);
    lcd.print("PH Value of Solution");
    lcd.setCursor(0,3);
    lcd.print(pHValue, 3);
    lcd.setCursor(6,3);
    lcd.print("PH");
    lcd.setCursor(14,3);
    lcd.print(tdsValue, 0);
    lcd.setCursor(17,3);
    lcd.print("Ppm");


  };
  // 3 раза в секунду
 if (millis() - myTimer1 >= 333) {
    //myTimer1 = millis(); // сбросить таймер
    // Serial.println("timer 1");
     Serial.print("PHv");
Serial.println(ads.adcValues[0] * 5 / 8.388608 / 1000000, 5);

   Serial.print("Ppmv");
  Serial.println(ads.adcValues[1] * 5 / 8.388608 / 1000000, 5);  // Raw ADC integer value +/- 23 bits
  //   Serial.print( "      " );

  // Serial.println();



  Serial.print("TDS Value = ");
  Serial.print(tdsValue);
  Serial.println(" ppm");
  // Serial.println(pcf1.read(0));
  // Serial.println(pcf1.read(1));
  // Serial.println(pcf1.read(2));
  // Serial.println(pcf1.read(3));
  // Serial.println(pcf1.read(4));
  // Serial.println(pcf1.read(5));
  // Serial.println(pcf1.read(6));
  // Serial.println(pcf1.read(7));

  // Serial.println(pcf2.read(0));
  // Serial.println(pcf2.read(1));
  // Serial.println(pcf2.read(2));
  // Serial.println(pcf2.read(3));
  // Serial.println(pcf2.read(4));
  // Serial.println(pcf2.read(5));
  // Serial.println(pcf2.read(6));
  // Serial.println(pcf2.read(7));
  };
  // каждые 2 секунды
  if (millis() - myTimer2 >= 2000) {
 //   myTimer2 = millis(); // сбросить таймер
    // Serial.println("timer 2");
  };
  // каждые 5 секунд
  if (millis() - myTimer3 >= 5000) {
  //  myTimer3 = millis(); // сбросить таймер
    // Serial.println("timer 3");
     
  };

  
ads.readInputToAdcValuesArray();
  phTot ;
 // temTot = 0;
  phAvg ;
// temAvg = 0;

//taking 10 sample and adding with 10 milli second delay
  for(x=0; x<10 ; x++)
    {
        phTot += ads.adcValues[ 0 ];
    //    temTot += ads.adcValues[ 1 ];
   
    };
   // float temAvg = temTot/1000000;
    float phAvg = phTot/10000000;
    // float temVoltage = temAvg * 5 / 8.388608 ; //convert sensor reading into milli volt
    float phVoltage =  phAvg * 5 / 8.388608 ;//convert sensor reading into milli volt
    sensors.requestTemperatures(); // Send the command to get temperatures
    float Etemp = sensors.getTempC(sensor1); //convert milli volt to temperature degree Celsius
    float pHValue = phVoltage*m+C;
    float Wtemp = sensors.getTempC(sensor2);
    float TempDif = fabs(Etemp-Wtemp); //calculating the absolute value of floating
    float   sensorValue = ads.adcValues[ 2 ];
    Voltage = sensorValue * 5 / 8.388608  / 1000000; //Convert analog reading to Voltage
    tdsValue=(133.42/Voltage*Voltage*Voltage - 255.86*Voltage*Voltage + 857.39*Voltage)*0.5; //Convert voltage value to TDS value
  




}
