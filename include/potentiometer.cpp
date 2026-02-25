#include <Arduino.h>

int analogvalue = 0;  // ຕົວແປເກັບຄ່າທີ່ອ່ານໄດ້ຈາກ Potentiometer
int ledvalue = 0;     // ຕົວແປເກັບຄ່າທີ່ແປງແລ້ວສຳລັບ LED

void setup() {
  pinMode(11, OUTPUT); // ກຳນົດ Pin 11 ເປັນ Output (PWM)
  Serial.begin(9600);  // ເປີດ Serial Monitor ເພື່ອເບິ່ງຄ່າ
}

void loop() {
  analogvalue = analogRead(A0); // ອ່ານຄ່າຈາກຂາ Analog A0 (0-1023)
  Serial.print("Analog: ");
  Serial.println(analogvalue);
  
  // ແປງຄ່າຈາກ 0-1023 ໃຫ້ເປັນ 0-255 ເພື່ອໃຊ້ກັບ PWM
  ledvalue = map(analogvalue, 0, 1023, 0, 255);
  Serial.print("LED PWM: ");
  Serial.println(ledvalue);
  
  analogWrite(11, ledvalue); // ສົ່ງຄ່າ PWM ໄປຫາ LED
  delay(10);
}