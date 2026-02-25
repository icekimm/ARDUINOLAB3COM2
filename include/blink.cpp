#include <Arduino.h>


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     //ຄ່າ default ຂອງ LED_BUILTIN ຢູ່ທີ່ຂາ 13
}



void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // LED ຮຸ່ງ
  delay(1000);                      //ລໍຖ້າ 1 ວິນາທີ
  digitalWrite(LED_BUILTIN, LOW);   // LED ດັບ
  delay(1000);                      //ລໍຖ້າ 1 ວິນາທີ
}