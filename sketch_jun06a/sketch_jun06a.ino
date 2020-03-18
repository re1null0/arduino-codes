int cnt = 0;    // счетчик
 
void setup() {
   Serial.begin(9600);   // инициализация порта
}
 
void loop() {
   cnt++;
   Serial.print("Hello BB from Arduino! Counter:");  // выводим надпись
   Serial.println(cnt);    // выводим значение счетчика и переводим на новую строку
   delay(1000);   // ждем 1 секунду
}
