#include <LiquidCrystal.h>

#include "TTS.h"

#include <PS2Keyboard.h>

const int DataPin = 8;
const int IRQpin =  2;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

PS2Keyboard keyboard;

TTS tts(3);

void setup(void) {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("Keyboard Test:");
  pinMode(13, OUTPUT);
  pinMode(3, INPUT_PULLUP);

  //LCD
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  
  lcd.setCursor(0, 0);
  
}


char line[128];
char bufferstring[128];
int pos = 0;
int cursorIndex = 0;
int bufferIndex = 0;
int deleteCounter = 1;

void loop(void) {
  
  //keyboard input check
  if (keyboard.available()) {
        // read the next key
    char c = keyboard.read();
    
    // check for some of the special keys
    if (c == PS2_ENTER) {
        Serial.println();
        lcd.setCursor(0, 0);
        digitalWrite(13, HIGH);
        lcd.noAutoscroll();
        
        //lcd.print(bufferstring);
               
        if (bufferstring[0] == '+') {
          int p = atoi(bufferstring+1);
          tts.setPitch(p);
        } else {
        bufferstring[bufferIndex++] = 0;
        
        tts.sayText(bufferstring);
        bufferIndex = 0;
        cursorIndex = 0;
        lcd.clear();
        digitalWrite(13, LOW);
    }       
    } else if (c == PS2_TAB) {
      Serial.print("[Tab]");

      lcd.setCursor(0, 0);
        lcd.print("I am Groot");
        digitalWrite(13, HIGH);
        lcd.noAutoscroll();               
        if (bufferstring[0] == '+') {
          int p = atoi(bufferstring+1);
          tts.setPitch(p);
        } else {
        bufferstring[bufferIndex++] = 0;
        
        tts.sayText("I am groot");
        bufferIndex = 0;
        cursorIndex = 0;
        lcd.clear();
        digitalWrite(13, LOW);
        }
    } else if (c == PS2_ESC) {
      Serial.print("[ESC]");
    } else if (c == PS2_PAGEDOWN) {
      Serial.print("[PgDn]");

      lcd.setCursor(0, 0);
        lcd.print("ALPHA Team");
        digitalWrite(13, HIGH);
        lcd.noAutoscroll();               
        if (bufferstring[0] == '+') {
          int p = atoi(bufferstring+1);
          tts.setPitch(p);
        } else {
        bufferstring[bufferIndex++] = 0;
        
        tts.sayText("ALPHA Team");
        bufferIndex = 0;
        cursorIndex = 0;
        lcd.clear();
        digitalWrite(13, LOW);
        }
    } else if (c == PS2_PAGEUP) {
      Serial.print("[PgUp]");

      lcd.setCursor(0, 0);
        lcd.print("My name is T2S");
        digitalWrite(13, HIGH);
        lcd.noAutoscroll();               
        if (bufferstring[0] == '+') {
          int p = atoi(bufferstring+1);
          tts.setPitch(p);
        } else {
        bufferstring[bufferIndex++] = 0;
        
        tts.sayText("My name is Tee 2 esS");
        bufferIndex = 0;
        cursorIndex = 0;
        lcd.clear();
        digitalWrite(13, LOW);
        }
    } else if (c == PS2_LEFTARROW) {
      Serial.print("[Left]");

      lcd.setCursor(0, 0);
        lcd.print("I am hungry");
        digitalWrite(13, HIGH);
        lcd.noAutoscroll();               
        if (bufferstring[0] == '+') {
          int p = atoi(bufferstring+1);
          tts.setPitch(p);
        } else {
        bufferstring[bufferIndex++] = 0;
        
        tts.sayText("I am hungry");
        bufferIndex = 0;
        cursorIndex = 0;
        lcd.clear();
        digitalWrite(13, LOW);
        }
    } else if (c == PS2_RIGHTARROW) {
      Serial.print("[Right]");

      lcd.setCursor(0, 0);
        lcd.print("Bathroom");
        digitalWrite(13, HIGH);
        lcd.noAutoscroll();               
        if (bufferstring[0] == '+') {
          int p = atoi(bufferstring+1);
          tts.setPitch(p);
        } else {
        bufferstring[bufferIndex++] = 0;
        
        tts.sayText("Bathroom");
        bufferIndex = 0;
        cursorIndex = 0;
        lcd.clear();
        digitalWrite(13, LOW);
        }
    } else if (c == PS2_UPARROW) {
      Serial.print("[Up]");

      lcd.setCursor(0, 0);
        lcd.print("I need water");
        digitalWrite(13, HIGH);
        lcd.noAutoscroll();               
        if (bufferstring[0] == '+') {
          int p = atoi(bufferstring+1);
          tts.setPitch(p);
        } else {
        bufferstring[bufferIndex++] = 0;
        
        tts.sayText("I need water");
        bufferIndex = 0;
        cursorIndex = 0;
        lcd.clear();
        digitalWrite(13, LOW);
        }
    } else if (c == PS2_DOWNARROW) {
      Serial.print("[Down]");

      lcd.setCursor(0, 0);
        lcd.print("Uncomfortable");
        digitalWrite(13, HIGH);
        lcd.noAutoscroll();               
        if (bufferstring[0] == '+') {
          int p = atoi(bufferstring+1);
          tts.setPitch(p);
        } else {
        bufferstring[bufferIndex++] = 0;
        
        tts.sayText("Uncomfortable");
        bufferIndex = 0;
        cursorIndex = 0;
        lcd.clear();
        digitalWrite(13, LOW);
        }
    } else if (c == PS2_DELETE) {
      Serial.print("[Del]");
      bufferIndex--;
      if(cursorIndex > 0){
        cursorIndex--;
      }
      lcd.noAutoscroll();
      deleteCounter++;
      lcd.setCursor(cursorIndex,0);
      lcd.print(' ');
      lcd.setCursor(cursorIndex,0);
      bufferstring[bufferIndex] = 0;
      
    } else {
      bufferstring[bufferIndex++] = c;
      // otherwise, just print all normal characters
      Serial.print(c);

      if(cursorIndex > 15 && --deleteCounter <= 0)
      {
        deleteCounter = 1;
        lcd.autoscroll();
      }  
      lcd.print(c);
      cursorIndex++;
      lcd.setCursor(cursorIndex,0);
    }
  }
  //For the output
  if (Serial.available() > 0) {
    char c = (char)Serial.read();
    if (c == '\n') {
      digitalWrite(13, HIGH);
      line[pos++] = 0;
      if (line[0] == '+') {
        int p = atoi(line+1);
        tts.setPitch(p);
      } else {
        Serial.println(line);
        tts.sayText(line);
      }
      pos = 0;
      digitalWrite(13, LOW);
    } else
      line[pos++] = c;
  }
}
