#include <Servo.h>
#include <Arduino.h>

Servo myservo; // ສ້າງ Object ເພື່ອຄວບຄຸມ Servo

void setup() {
  Serial.begin(9600);
  myservo.attach(9); // ເຊື່ອມຕໍ່ຂາສັນຍານ Servo ເຂົ້າກັບ Pin 9
}

void loop() {
  // ໝູນຈາກ 0 ຫາ 180 ອົງສາ
  for (int i=0; i<=180; i++){
    myservo.write(i);
    Serial.println(i);
    delay(35); // ຖ້າໃຫ້ Servo ໝູນໄປຮອດຕຳແໜ່ງ
  }
  delay(500);
  
  // ໝູນກັບຈາກ 180 ຫາ 0 ອົງສາ
  for(int i = 180; i>= 0; i--){
    myservo.write(i);
    Serial.println(i);
    delay(35);
  }
  delay(500);
}