

#include "TTS.h"

#include <PS2Keyboard.h>

const int DataPin = 8;
const int IRQpin =  2;

PS2Keyboard keyboard;

TTS tts(3);

void setup(void) {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("Keyboard Test:");
  pinMode(13, OUTPUT);
  
}


char line[80];
char bufferstring[80];
int pos = 0;
int bufferIndex = 0;

void loop(void) {

  //keyboard input check
  if (keyboard.available()) {
    
    // read the next key
    char c = keyboard.read();
    
    // check for some of the special keys
    if (c == PS2_ENTER) {
        Serial.println();
        //Serial.println("Successful ENTER");
        digitalWrite(13, HIGH);
        bufferstring[bufferIndex++] = 0;
        if (bufferstring[0] == '+') {
          int p = atoi(bufferstring+1);
          tts.setPitch(p);
        } else {
        //Serial.println("Successful");
        tts.sayText(bufferstring);
        bufferIndex = 0;
        digitalWrite(13, LOW);
    }       
    } else if (c == PS2_TAB) {
      Serial.print("[Tab]");
    } else if (c == PS2_ESC) {
      Serial.print("[ESC]");
    } else if (c == PS2_PAGEDOWN) {
      Serial.print("[PgDn]");
    } else if (c == PS2_PAGEUP) {
      Serial.print("[PgUp]");
    } else if (c == PS2_LEFTARROW) {
      Serial.print("[Left]");
    } else if (c == PS2_RIGHTARROW) {
      Serial.print("[Right]");
    } else if (c == PS2_UPARROW) {
      Serial.print("[Up]");
    } else if (c == PS2_DOWNARROW) {
      Serial.print("[Down]");
    } else if (c == PS2_DELETE) {
      Serial.print("[Del]");
      bufferIndex--;
    } else {
      bufferstring[bufferIndex++] = c;
      // otherwise, just print all normal characters
      Serial.print(c);
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
