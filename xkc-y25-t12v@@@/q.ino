// //Pащита от дребезга контактов, например при волнах, когда работает насос.

// // Текущее состояние сенсора
// bool SensorState = false;
// // Время начала смены 
// unsigned long SensorStartChange = 0;
// // Защитный интервал между сменами состояния
// unsigned long TIMEOUT = 3000;
// // Текущее время
// unsigned long CurrentTime = 0;
// #define LED_PIN 13
// #define SENS_PIN 3


// void setup() {
//   // Светодиод это выход
//   pinMode(LED_PIN, OUTPUT);
//   // Вначале не светим
//   digitalWrite(LED_PIN, LOW);
//   // Сенсор это вход
//   pinMode(SENS_PIN, INPUT);
// }

// void loop() {
//   // Устанавливаем текущее время
//   CurrentTime = millis();
//   // считываем сенсор
//   boolean CurrentState = digitalRead(SENS_PIN);
//   // если текущее состояние сенсора отличается считанного
//   if (CurrentState != SensorState) {
//     // если отсчет таймера смены состояния не начат, начинаем
//     if (SensorStartChange == 0) SensorStartChange = CurrentTime;
//     // если новое состояние приняло свое значение за время большее чем время таймаута
//     if (CurrentTime - SensorStartChange > TIMEOUT) {
//         // меняем состояние сенсора
//         SensorState=!SensorState;
//         // сбрасываем время начала смены состояния
//         SensorStartChange = 0;
//         // если текущее состояние сенсора 1, то включаем светодиод
//         if(SensorState){
//           digitalWrite(LED_PIN, HIGH);        
//         // если текущее состояние сенсора 0, то выключаем светодиод
//         }else{
//           digitalWrite(LED_PIN, LOW);     
//         }
//     }
//   // смена состояния не состоялась, сбрасываем таймер
//   }else{
//     SensorStartChange = 0;
//   }
// }