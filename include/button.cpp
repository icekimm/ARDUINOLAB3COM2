#include <Arduino.h>

int buttonstate = 0;   // ຕົວແປເກັບສະຖານະປຸ່ມ
int bled = 13;         // LED pin

void setup() {
  pinMode(2, INPUT);       // ກຳນົດ pin 2 ເປັນ Input
  pinMode(bled, OUTPUT);   // ກຳນົດ pin 13 ເປັນ Output
  Serial.begin(9600);      // ເປີດ Serial Monitor
}

void loop() {
  buttonstate = digitalRead(2);   // ອ່ານຄ່າຈາກ Button

  if (buttonstate == HIGH) {
    Serial.println("Button HIGH");
    digitalWrite(bled, HIGH);     // LED ຕິດ
  } else {
    Serial.println("Button LOW");
    digitalWrite(bled, LOW);      // LED ດັບ
  }
  delay(10);
}
