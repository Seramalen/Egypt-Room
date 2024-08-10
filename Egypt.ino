
#include "SD.h"
#define SD_ChipSelectPin 4
#include "TMRpcm.h"
#include "SPI.h"
//MOSI: pin 11
//MISO: pin 12
//CLK: pin 13
//CS: depends, set to 4 here

TMRpcm player;
int doorButton = 8;
int xylophoneButton = 7;
int magLock = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(doorButton, INPUT_PULLUP);
  pinMode(xylophoneButton, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  digitalWrite(magLock, LOW);
  player.speakerPin = 9; //Pin for the audio jack
  Serial.begin(9600);
  //Check to make sure the reader could find the sd card
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD Fail");
    return;    
    }
    //Setup player
    player.setVolume(4);
    //must set quality to 1 to avoid horrible noises
    player.quality(1);
    player.loop(1);
    player.play("slow.wav");
}

void loop() {
  // put your main code here, to run repeatedly

  //Check if the door buttons were pressed
  if(digitalRead(doorButton) == LOW){
    delay(300);
    //Quick check for non-human presses 
    if(digitalRead(doorButton) == LOW)
    {
    digitalWrite(magLock, HIGH);
    player.pause();
    //slow music is quieter, and also they dont have to communicate as well anymore
    player.setVolume(5);
    delay(100);
    player.play("fast.wav");
      }    
    }

  //Check if the xylophone button was pressed
  if(digitalRead(xylophoneButton)==LOW){
    delay(300);
    if(digitalRead(xylophoneButton) == LOW)
    {
          //Pause player, turn off the loop so we can tell how long the file is playing for
    player.pause();
    player.loop(0);
    //Play the xylophone noise
    player.play("xylo.wav");
    //While the xylophone is playing, we do nothing
    delay(1000);
    while(player.isPlaying()==1){      
      }
    //Once it's done, we pause again, turn on the loop, and then play the music again
    player.pause();
    player.loop(1);
    player.play("fast.wav");
      }
    }
}
