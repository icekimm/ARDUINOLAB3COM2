#include <Arduino.h>

const int ledPins[] = {11,10,9};

void allColors();

void setup(){
  Serial.begin(9600);
  for (int pin : ledPins){
    pinMode(pin, OUTPUT);
  }
}

void loop() {

	while (Serial.available() > 0) {
    // read input from serial monitor
    String input = Serial.readStringUntil('\n'); // Read until newline
    for (int pin : ledPins){
      digitalWrite(pin, LOW);
    }
    delay(10);

    if (input == "on" or input == "rgb" or input == "rbg" or input == "grb" or input == "gbr" or input == "brg" or input == "bgr" ) {
      // turn all LEDs on
      for (int pin : ledPins){
        digitalWrite(pin, HIGH);
      }
    }

    else if (input == "off") {
      // turn all LEDs off
      for (int pin : ledPins){
        digitalWrite(pin, LOW);
      }
    }

    else if (input == "r") {
      digitalWrite(ledPins[0], HIGH);
    }

    else if (input == "g") {
      digitalWrite(ledPins[1], HIGH);
    }

    else if (input == "b") {
      digitalWrite(ledPins[2], HIGH);
    }
    
    else if (input == "rg" or input == "gr") {
      digitalWrite(ledPins[0], HIGH);
      digitalWrite(ledPins[1], HIGH);
    }
    else if (input == "rb" or input == "br") {
      digitalWrite(ledPins[0], HIGH);
      digitalWrite(ledPins[2], HIGH);
    }
    else if (input == "gb" or input == "bg") {
      digitalWrite(ledPins[1], HIGH);
      digitalWrite(ledPins[2], HIGH);
    }
    else {
      allColors();
    }
  }
}
void allColors(){
  //WHITE
  for(int pin : ledPins){
        digitalWrite(pin, HIGH);
  }
  delay(100);
  for(int pin : ledPins){
        digitalWrite(pin, LOW);
  }
  delay(100);

  //RED, GREEN, BLUE
  for(int pin : ledPins){
        digitalWrite(pin, HIGH);
        delay(100);
        digitalWrite(pin, LOW);
        delay(100);
  }

  //RED + GREEN index 0 and index 1
  for(int i = 0; i < 2; i++){
    digitalWrite(ledPins[i], HIGH);
  }
  delay(100);
  for(int i = 0; i < 2; i++){
    digitalWrite(ledPins[i], LOW);
  }
  delay(100);

  //RED BLUE index 0 and index 2
  for(int i = 0; i < 3; i += 2){
    digitalWrite(ledPins[i], HIGH);
  }
  delay(100);
  for(int i = 0; i < 3; i += 2){
    digitalWrite(ledPins[i], LOW);
  }
  delay(100);

  // GREEN + BLUE index 1 and index 2  
  for(int i = 1; i < 3; i++){
    digitalWrite(ledPins[i], HIGH);
  }
  delay(100);

  for(int i = 1; i < 3; i++){
    digitalWrite(ledPins[i], LOW);
  }
  delay(100);
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  }