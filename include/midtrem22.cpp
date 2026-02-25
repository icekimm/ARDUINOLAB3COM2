#include <Wire.h>
#include<Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define BUZZER_PIN 11
#define BUTTON_PIN 8
#define LED_PIN    13
#define SERVO_PIN  12

LiquidCrystal lcd(2,3,4,5,6,7);
Servo lidServo;
void playMusic();
void setRGB(int red, int green, int blue);
#define RGB_RED    1
#define RGB_GREEN  9
#define RGB_BLUE   10



// Note definitions
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0

// Change this to make the song slower or faster
int tempo = 180;

// 🎵 Hedwig's Theme from Harry Potter
int melody[] = {
  REST, 2, NOTE_D4, 4,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_C5, -2, 
  NOTE_A4, -2,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_F4, 2, NOTE_GS4, 4,
  NOTE_D4, -1, 
  NOTE_D4, 4,

  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_F5, 2, NOTE_E5, 4,
  NOTE_DS5, 2, NOTE_B4, 4,
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_B4, 4,
  NOTE_G4, -1,
  NOTE_AS4, 4,
     
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_DS5, 2, NOTE_D5, 4,
  NOTE_CS5, 2, NOTE_A4, 4,
  NOTE_AS4, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_D4, 4,
  NOTE_D5, -1, 
  REST, 4, NOTE_AS4, 4,  

  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_F5, 2, NOTE_E5, 4,
  NOTE_DS5, 2, NOTE_B4, 4,
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_AS4, 4,
  NOTE_G4, -1, 
};

// Calculate number of notes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// Calculate the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

bool isPlaying = false;
bool usePurple = true; // Flag to alternate between purple and blue

// Set to true if you have a common anode RGB LED, false for common cathode
bool commonAnode = true;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_GREEN, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);
  
  // Turn off RGB LED initially
  setRGB(0, 0, 0);
  
  lidServo.attach(SERVO_PIN);
  lidServo.write(0); 
  
  lcd.begin(16, 2);
  lcd.setCursor(2,0);
  lcd.print("Harry Potter");
  lcd.setCursor(2,1);
  lcd.print("Press Button");
  
  randomSeed(analogRead(A0));
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW && !isPlaying) {
    delay(50); // debounce
    if (digitalRead(BUTTON_PIN) == LOW) {
      playMusic();
    }
  }
}

// Helper function to set RGB color (handles common anode vs cathode)
void setRGB(int red, int green, int blue) {
  if (commonAnode) {
    analogWrite(RGB_RED, 255 - red);
    analogWrite(RGB_GREEN, 255 - green);
    analogWrite(RGB_BLUE, 255 - blue);
  } else {
    analogWrite(RGB_RED, red);
    analogWrite(RGB_GREEN, green);
    analogWrite(RGB_BLUE, blue);
  }
}

void playMusic() {
  isPlaying = true;
  usePurple = true; // Start with purple
  lidServo.write(90); 
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Playing Hedwig");
  lcd.setCursor(0,1);
  lcd.print("Theme...");
  
  // Iterate over the notes of the melody
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // Alternate between purple and blue
    int redValue, greenValue, blueValue;
    if (usePurple) {
      // Purple: High red, low green, high blue
      redValue = 200;
      greenValue = 0;
      blueValue = 200;
    } else {
      // Blue: Low red, low green, high blue
      redValue = 0;
      greenValue = 0;
      blueValue = 255;
    }

    // Calculate the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }

    // Play the note and blink LED/RGB with it
    if (melody[thisNote] != REST) {
      // Turn ON LED and RGB with purple or blue
      digitalWrite(LED_PIN, HIGH);
      setRGB(redValue, greenValue, blueValue);
      
      tone(BUZZER_PIN, melody[thisNote], noteDuration * 0.9);
      
      // Toggle color for next note
      usePurple = !usePurple;
    } else {
      // For REST notes, turn everything off
      digitalWrite(LED_PIN, LOW);
      setRGB(0, 0, 0);
    }

    // Visual feedback on LCD (progress bar)
    if (thisNote % 8 == 0 && thisNote / 8 < 16) {
      lcd.setCursor(thisNote / 8, 1);
      lcd.print((char)0xFF);
    }

    // Wait for 90% of note duration with LED/RGB on
    delay(noteDuration * 0.9);
    
    // Turn off LED and RGB for the gap between notes (10%)
    digitalWrite(LED_PIN, LOW);
    setRGB(0, 0, 0);
    noTone(BUZZER_PIN);
    
    // Brief pause between notes
    delay(noteDuration * 0.1);
  }
  
  // Ensure everything is off
  digitalWrite(LED_PIN, LOW);
  setRGB(0, 0, 0);
  
  lidServo.write(0);
  
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Magical!");
  lcd.setCursor(3,1);
  lcd.print("Good Spell");
  
  isPlaying = false;
}