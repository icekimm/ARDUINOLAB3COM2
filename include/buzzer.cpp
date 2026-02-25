#include <Arduino.h>

#define BTN  2
#define BZ  10
#define FQ  50

int startFQ = FQ;
int endFQ = 4000;
int btnstate = 0;


void setup()
{
    pinMode(BZ, OUTPUT);
    pinMode(BTN, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}


void loop()
{
    btnstate = digitalRead(BTN);
    Serial.println(btnstate);

    if (btnstate == HIGH) {
        delay(500);
        digitalWrite(LED_BUILTIN, 1);
        for(startFQ ; startFQ < endFQ; startFQ +=100){
            tone(BZ, startFQ);
            delay(100);
        }
        digitalWrite(LED_BUILTIN, 0);
        delay(100);
    } 

    if (startFQ > endFQ){
        noTone(BZ);
        startFQ = FQ;
    }//Reset starting frequency
    
}