//Pащита от дребезга контактов, например при волнах, когда работает насос.
// Текущее состояние сенсора
bool SensGW = false;
// Время начала смены 
unsigned long SensorStartChangeGW = 0;
// Защитный интервал между сменами состояния
unsigned long TIMEOUTGW = 300;
// Текущее время
unsigned long CurrentTimeGW = 0;
#define GW_PIN 0
#define SensGW_PIN 34

//Pащита от дребезга контактов, например при волнах, когда работает насос.
// Текущее состояние сенсора
bool SensPW = false;
// Время начала смены 
unsigned long SensorStartChangePW = 0;
// Защитный интервал между сменами состояния
unsigned long TIMEOUTPW = 300;
// Текущее время
unsigned long CurrentTimePW = 0;
#define PW_PIN 14
#define SensPW_PIN 35


void setup() {
  // Светодиод это выход
  pinMode(GW_PIN, OUTPUT);
  // Вначале не светим
  digitalWrite(GW_PIN, HIGH);
  // Сенсор это вход
  pinMode(SensGW_PIN, INPUT);

   // Светодиод это выход
  pinMode(PW_PIN, OUTPUT);
  // Вначале не светим
  digitalWrite(PW_PIN, HIGH);
  // Сенсор это вход
  pinMode(SensPW_PIN, INPUT);
}

void loop() {
Serial.begin(115200);  
  // Устанавливаем текущее время
  CurrentTimeGW = millis();
  // считываем сенсор
  boolean CurrentStateGW = digitalRead(SensGW_PIN);
  // если текущее состояние сенсора отличается считанного
  if (CurrentStateGW != SensGW) {
    // если отсчет таймера смены состояния не начат, начинаем
    if (SensorStartChangeGW == 0) SensorStartChangeGW = CurrentTimeGW;
    // если новое состояние приняло свое значение за время большее чем время таймаута
    if (CurrentTimeGW - SensorStartChangeGW > TIMEOUTGW) {
        // меняем состояние сенсора
        SensGW=!SensGW;
        // сбрасываем время начала смены состояния
        SensorStartChangeGW = 0;
        // если текущее состояние сенсора 1, то включаем светодиод
        if(SensGW){
          digitalWrite(GW_PIN, HIGH);        
        // если текущее состояние сенсора 0, то выключаем светодиод
        }else{
          digitalWrite(GW_PIN, LOW);     
        }
    }
  // смена состояния не состоялась, сбрасываем таймер
  }else{
    SensorStartChangeGW = 0;
  };


 // Устанавливаем текущее время
  CurrentTimePW = millis();
  // считываем сенсор
  boolean CurrentStatePW = digitalRead(SensPW_PIN);
  // если текущее состояние сенсора отличается считанного
  if (CurrentStatePW != SensPW) {
    // если отсчет таймера смены состояния не начат, начинаем
    if (SensorStartChangePW == 0) SensorStartChangePW = CurrentTimePW;
    // если новое состояние приняло свое значение за время большее чем время таймаута
    if (CurrentTimePW - SensorStartChangePW > TIMEOUTPW) {
        // меняем состояние сенсора
        SensGW=!SensPW;
        // сбрасываем время начала смены состояния
        SensorStartChangePW = 0;
        // если текущее состояние сенсора 1, то включаем светодиод
        if(SensPW){
          digitalWrite(PW_PIN, HIGH);        
        // если текущее состояние сенсора 0, то выключаем светодиод
        }else{
          digitalWrite(PW_PIN, LOW);     
        }
    }
  // смена состояния не состоялась, сбрасываем таймер
  }else{
    SensorStartChangeGW = 0;
  };
}