#include <Arduino.h>

//Pin defination
int led[] = {13,12,11};
int rgb[] = {10,9,8};
int bz = 7;
int pot = A2;
int bn = 2;
int potValue = 0;
//melody 
int melody[] = { 262, 330, 392, 523 }; // C E G C
int noteDuration = 300;

void ringDoorbell();
void setUnavailable();
void setIdle();
void setRinging();
void setColor(int r, int g, int b);
void randomColorShow();

void setup(){
  pinMode(bz, OUTPUT);
  pinMode(bn, INPUT_PULLUP);
  pinMode(pot, INPUT);
  for (int i = 0; i<3; i++){
    pinMode(led[i],OUTPUT);
    pinMode(rgb[i],OUTPUT);
  }
  Serial.begin(9600);
  
}
void loop(){
  
  int potValue = analogRead(pot);
  Serial.println(potValue);
  delay(100);

    if (potValue < 400){
    	setUnavailable();
  	} else {
    	setIdle();
      	if (digitalRead(bn) == LOW ){
   	 		ringDoorbell();
    		delay(5000);
  		} 
  	}
  
}
//-------------------function----------------------------
void ringDoorbell() {
  
  //int volume = analogRead(pot);
  //int pwmVolume = map(volume, 0, 1023, 0, 255);
  // Serial.println(volume);
  for (int i = 0; i < 4; i++) {
    // /analogWrite(bz, pwmVolume); // volume control
    tone(bz, melody[i], noteDuration);
    delay(noteDuration);
    noTone(bz);
    delay(100);
  }
  
  //If pressed button show random color
  setRinging();
  delay(500);
}
void setUnavailable(){
  
    digitalWrite(led[1], LOW);//Green
  	digitalWrite(led[2], HIGH);//Blue
    digitalWrite(led[0], LOW);//Red
    setColor(0,0,255); //Blue
  	//Serial.println("Unavailable");
  
}
void setIdle() {
  digitalWrite(led[0], LOW);//Red
  digitalWrite(led[2], LOW);//Blue
  digitalWrite(led[1], HIGH);//Green
  setColor(0, 255, 0); // Green
  // Serial.println("Normal Status");
}
void setRinging() {
  for (int i=0; i<3; i++){
    digitalWrite(led[i], HIGH);
    delay(100);
    digitalWrite(led[i], LOW);
    delay(100);
  }
  randomColorShow();
  // Serial.println("Doorbell ring detected");

  
}
void setColor(int r, int g, int b) {
  analogWrite(rgb[0], r);
  analogWrite(rgb[2], g);
  analogWrite(rgb[1], b);
}

void randomColorShow() {
  unsigned long startTime = millis();

  while (millis() - startTime < 5000) {   // 5 seconds
    int r = random(0, 256);
    int g = random(0, 256);
    int b = random(0, 256);

    setColor(r, g, b);
    delay(200);  // change color every 0.2 sec
  }

  // After 1 minute → set to RED
  digitalWrite(led[0], HIGH);
  setColor(255, 0, 0);
}
