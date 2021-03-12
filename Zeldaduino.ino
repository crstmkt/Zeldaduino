#include <Adafruit_SleepyDog.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"


SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
bool chestOpen = true; // To just play the sounds once the chest is open and not as long as it is open
bool isBotW = true; // Because the Ocarina of Time Sound is also awesome, I want them both alternating

void setup() {
  mySoftwareSerial.begin(9600);
  Serial.begin(57600);
  
  pinMode(2, INPUT); //Why D2? Because R2D2
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); // Show we're awake

  Serial.println();
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

    if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30 (Max)
}

void loop() {
  if(digitalRead(2) == LOW && chestOpen == false)
  {
    if(isBotW){
      myDFPlayer.play(1);
      delay(6000);
      isBotW = false;
    }else
    {
      myDFPlayer.play(2);
      delay(12500);
      isBotW = true;
   }
    chestOpen = true;
    delay(1000);
  }else if(digitalRead(2) == HIGH && chestOpen == true)
  {
    chestOpen = false;
  }
  delay(200);
}
