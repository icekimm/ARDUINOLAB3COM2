#include <Arduino.h>
#include <Stepper.h>

#define STEPROTATION 2048


Stepper Steppermotor(STEPROTATION , 8, 10, 9, 11);    //(1)

void setup() {    //(2)
}

void loop() {
  Steppermotor.setSpeed(5);
  Steppermotor.step(STEPROTATION );
  delay(500);

  Steppermotor.setSpeed(1);
  Steppermotor.step(-STEPROTATION /4);
  delay(500);
}