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
    //For some unknown reason, the sounds are not in the order I named them:
    // 1. BotW Get Item
    // 2. OoT Get Item
    // 3. BotW Open Wooden Box
    // 4. OoT Open Treasure Chest
    if(isBotW){
      myDFPlayer.play(3);
      delay(600);
      myDFPlayer.play(1);
      isBotW = false;
      delay(2000);
    }else
    {
      myDFPlayer.play(4);
      delay(7500);
      myDFPlayer.play(2);
      isBotW = true;
      delay(2000);
   }
    chestOpen = true;
    delay(1000);
  }else if(digitalRead(2) == HIGH && chestOpen == true)
  {
    chestOpen = false;
  }
  delay(200);
}