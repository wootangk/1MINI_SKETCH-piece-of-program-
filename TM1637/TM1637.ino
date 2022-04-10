#define CLK 3
#define DIO 2

#include "TM1637.h"
TM1637 disp(CLK, DIO);

uint32_t Now;
boolean flag;
static byte buff[4] = {_S, _H, _O, _P};

void setup() 
{
  disp.clear();
  disp.brightness(7);  // яркость минимум =0, стандарт=2,  максимум=7)
}

void loop() 
{
  running_text();
  scrolling_text();
  scrolling_text();
  rotation_all_sign();
  rotation_one_sign();
  blinking_text();

  normClock();
  twistClock();
  scrollClock();
}

void running_text()
{
  byte buf[] = { _S,_H,_O,_P,_P,_I,_N,_G,0,0,_i,_n,0,0,_t,_h,_E,0,0,_S,_t,_o,_r,_E,0,0,_d,_u,_i,_n,_o,0,_r,_u,0,0,_A,_r,_d,_u,_i,_n,_o,\
  0,_N,_A,_N,_O,0,0,_A,_r,_d,_u,_i,_n,_o,0,_U,_N,_O,0,0,_A,_r,_d,_u,_i,_n,_o,0,0,_S,_E,_N,_S,_O,RG,_S,0,0,_A,_L,_L,0,0,_F,_o,_r,0,0,\
  _A,_r,_d,_u,_i,_n,_o,0,0,_b,_o,_A,_r,_d,_S,0,0,_degree,_o,_degree,_o,_degree,_o,_degree,_o,_degree,_o,_degree,_o};
  disp.runningString(buf, sizeof(buf), 200);  // время в мс
}  

void scrolling_text() // скролинг текста вниз
{                     
 disp.clear();
  disp.scrollByte(buff, 100);
  delay(1000);
}

void rotation_all_sign()  // вращение по часовой стрелке всех символов
{
  disp.clear();
  disp.twistByte(buff, 100);
  delay(1000);
}  

void rotation_one_sign()  // вращение символов по очереди слева на право
{
  for (uint8_t i = 0; i < 4; i++) 
    {
      disp.twistByte(i, buff[i], 70);
      delay(100);
    }
}  
  
void blinking_text() //играем с яркостью
{
   disp.brightness(0);
   delay(500);
    for (uint8_t i = 0; i < 5; i++) 
    {
      disp.brightness(2);
      delay(120);
      disp.brightness(7);
      delay(120);
      disp.brightness(0);
      delay(500);
    }
 disp.brightness(7);
}

void twistClock()  //часы с вращающимися цифрам
{
  byte hrs = 19, mins = 53;
  uint32_t tmr;
  Now = millis();
  while (millis () - Now < 10000) {   // каждые 10 секунд
    if (millis() - tmr > 500) {       // каждые полсекунды
      tmr = millis();
      flag = !flag;
      disp.point(flag);   // выкл/выкл точки

      if (flag) 
      {
        // ***** часы! ****
        mins ++;
        if (mins > 59) 
        {
          mins = 0;
          hrs++;
          if (hrs > 24) hrs = 0;
        }
        // ***** часы! ****
        disp.displayClockTwist(hrs, mins, 35);    // показываем часы
      }
    }
  }
  disp.point(0);   // выключить разделитель :
}


void scrollClock() //часы со скролингом цифр
{
  byte hrs = 19, mins = 54;
  uint32_t tmr;
  Now = millis();
  while (millis () - Now < 10000) {   // каждые 10 секунд
    if (millis() - tmr > 500) {       // каждые полсекунды
      tmr = millis();
      flag = !flag;
      disp.point(flag);   // выкл/выкл разделитель:

      if (flag) 
      {
        mins ++;
        if (mins > 59) 
        {
          mins = 0;
          hrs++;
          if (hrs > 24) hrs = 0;
        }
        // ***** выводим часы! ****
        disp.displayClockScroll(hrs, mins, 70);    // показываем часы
      }
    }
  }
  disp.point(0);   // выкл точки
}

void normClock() //обычные часы
{
  byte hrs = 19, mins = 55;
  uint32_t tmr;
  Now = millis();
  while (millis () - Now < 10000) {   // каждые 10 секунд
    if (millis() - tmr > 500) {       // каждые полсекунды
      tmr = millis();
      flag = !flag;
      disp.point(flag);   //выкл/выкл разделитель:

      mins ++;
      if (mins > 59) 
      {
        mins = 0;
        hrs++;
        if (hrs > 24) hrs = 0;
      }
      // ***** выводим часы! ****
      disp.displayClock(hrs, mins);   // выводим время функцией часов
    }
  }
  disp.point(0);   // выкл точки
}

