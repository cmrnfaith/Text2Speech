#include <SD.h>
#define SD_ChipSelectPin 3
#include <TMRpcm.h>
#include <SPI.h>

TMRpcm tmrpcm;

void setup(){
tmrpcm.speakerPin = 9;
Serial.begin(9600);
if (!SD.begin(SD_ChipSelectPin)) {
Serial.println("SD fail");
return;
}

tmrpcm.setVolume(15);
tmrpcm.play("aa.wav");
tmrpcm.play("f.wav");


}

void loop(){ tmrpcm.play("aa.wav");
delay(1500);
 }
