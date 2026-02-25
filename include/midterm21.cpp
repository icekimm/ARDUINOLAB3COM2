#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>
//#include <AccelStepper.h>

const int pot = A0;
const int led = 13;
int speedmotor = 0;
int ledvalue = 0;

#define STEPROTATION 2048
Stepper Steppermotor(STEPROTATION , 8, 10, 9, 11);
//AccelStepper stepper(AccelStepper::FULL4WIRE, 8, 10, 9, 11);

LiquidCrystal_I2C lcd(0x26, 16, 2);

void lcdStatus();
void stopStepper();

void setup()
{
//  stepper.setMaxSpeed(500);
  pinMode(led, OUTPUT);
  pinMode(pot, INPUT);
  
  Steppermotor.setSpeed(0);
  Serial.begin(9600);
  lcd.init();					
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Fan Speed Contrl");
  lcd.setCursor(6,1);
  lcd.print("-kim-");
  delay(3000);
  
  lcd.clear();
  
}
void loop()
{
  int potvalue = analogRead(pot);
  speedmotor = map(potvalue, 0, 1023, 0, 15);
  ledvalue = map(potvalue, 0, 1023, 0,255);
  
  if (potvalue < 50) {
    stopStepper();
//  	stepper.stop();
//    stepper.disableOutputs(); 
  
  }
  if(potvalue != 0){
    analogWrite(led, ledvalue);
    lcdStatus();
    lcd.setCursor(8,0);
    lcd.print("Running");
    Steppermotor.setSpeed(speedmotor);
    
    if(speedmotor < 10 && speedmotor > 0){
      lcd.clear();
      lcdStatus();
      lcd.setCursor(8,0);
      lcd.print("Running");
      Steppermotor.setSpeed(speedmotor);
      delay(3000);
  	}
  }
  
  
  if(potvalue == 0){
    lcd.clear();
    lcdStatus();
    lcd.setCursor(11,0);
    lcd.print("STOP");
   delay(3000);
  }
 
}

void lcdStatus(){
  lcd.setCursor(0,0);
  lcd.print("Status:");
    
   lcd.setCursor(0,1);
   lcd.print("Speed:");
   lcd.setCursor(8,1);
   lcd.print(speedmotor);
   lcd.setCursor(12,1);
   lcd.print("RPM");
}
void stopStepper() {
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

